//
//  NativeOps.cpp
//  run_native_op: a JSON list of ops executed straight through the SDK (no scripting engine).
//  Runs on the main thread inside the job's ScriptDialogGuard + UndoEventScope (ScriptRunner.cpp).
//
//  Ops: call (generic ISDK dispatch), clearHandles, layer, viewport, delete, move, rotate,
//  clearLayer, duplicate, group, rect, oval, rrect, line, locus, text, polygon.
//

#include "NativeOps.h"

#include <unordered_map>

namespace VwMcp
{
#include "IsdkDispatch.inc"

static void FinishCreatedObject( MCObjectHandle h, const nlohmann::json& op, nlohmann::json& item )
{
	if ( !h ) { item["created"] = false; return; }

	if ( op.contains("class") && op["class"].is_string() )
	{
		InternalIndex ci = 0;
		if ( gSDK->NameToInternalIndexN( TXString( op["class"].get<std::string>().c_str() ), ci ) )
			gSDK->SetObjectClass( h, ci );
	}
	if ( op.contains("name") && op["name"].is_string() )
		gSDK->SetObjectName( h, TXString( op["name"].get<std::string>().c_str() ) );

	// Line weight in mils (thousandths of an inch).
	if ( op.contains("weight") && op["weight"].is_number() )
		gSDK->SetLineWeight( h, (short)op["weight"].get<int>() );

	// Fill / pen color as RGB arrays [r,g,b], each 0-255. We read the current colors first
	// so we only override the requested channel, then map RGB (0-65535) -> palette ColorRef.
	if ( ( op.contains("fillColor") && op["fillColor"].is_array() ) ||
	     ( op.contains("penColor")  && op["penColor"].is_array() ) )
	{
		ObjectColorType colors;
		gSDK->GetColor( h, colors );
		auto toColorRef = [&]( const nlohmann::json& a ) -> ColorRef {
			RGBColor rgb;
			rgb.red   = (unsigned short)( ( a.size() > 0 ? a[0].get<int>() : 0 ) * 257 );
			rgb.green = (unsigned short)( ( a.size() > 1 ? a[1].get<int>() : 0 ) * 257 );
			rgb.blue  = (unsigned short)( ( a.size() > 2 ? a[2].get<int>() : 0 ) * 257 );
			ColorRef cr = 0;
			gSDK->RGBToColorIndex( rgb, cr );
			return cr;
		};
		if ( op.contains("fillColor") && op["fillColor"].is_array() )
			colors.fillFore = toColorRef( op["fillColor"] );
		if ( op.contains("penColor") && op["penColor"].is_array() )
			colors.penFore = toColorRef( op["penColor"] );
		gSDK->SetColor( h, colors );
	}

	// Fill pattern index: 0 = none/empty, 1 = solid, 2+ = pattern/hatch resource index.
	if ( op.contains("fillPattern") && op["fillPattern"].is_number_integer() )
		gSDK->SetFillPat( h, (InternalIndex)op["fillPattern"].get<int>() );

	gSDK->ResetObject( h );

	if ( op.contains("layer") && op["layer"].is_string() )
	{
		MCObjectHandle container = gSDK->GetNamedLayer( TXString( op["layer"].get<std::string>().c_str() ) );
		if ( container )
		{
			gSDK->AddObjectToContainer( h, container );
			gSDK->ResetObject( container );
		}
		else
		{
			item["layerNotFound"] = op["layer"];
		}
	}

	gSDK->AddAfterSwapObject( h );   // register for undo
	item["created"] = true;
}

// TODO(#11): replace with an ISDK safety table; this only covers the calls that crashed before the ctx engine.
static bool IsBlockedIsdkCall( const std::string& fn )
{
	return fn.rfind( "BuildResourceList", 0 ) == 0 || fn == "GetResourceFromList" ||
	       fn.rfind( "CreateWorksheet", 0 ) == 0;
}

nlohmann::json RunNativeOps( const std::string& opsJson )
{
	nlohmann::json result;
	nlohmann::json ops;
	try { ops = nlohmann::json::parse( opsJson ); }
	catch ( const std::exception& e )
	{
		result["ok"]    = false;
		result["error"] = std::string( "ops JSON parse error: " ) + e.what();
		return result;
	}
	if ( !ops.is_array() )
	{
		result["ok"]    = false;
		result["error"] = "ops must be a JSON array of { op, ... } objects";
		return result;
	}

	nlohmann::json created = nlohmann::json::array();
	{

		for ( const auto& op : ops )
		{
			if ( !op.is_object() || !op.contains("op") || !op["op"].is_string() )
				continue;
			const std::string kind = op["op"].get<std::string>();

			nlohmann::json item;
			item["op"] = kind;

			// Generic ISDK call: {"op":"call","fn":"Name","args":[...],"as":<id>}.
			// Handle args: {"$h":id} (registry), {"$name":"X"} or {"$layer":"X"} (lookup).
			// A handle return registers under "as" (or an auto id) for later reference.
			if ( kind == "call" )
			{
				std::string    fn   = op.value( "fn", std::string( "" ) );
				int            asId = ( op.contains("as") && op["as"].is_number_integer() )
				                      ? op["as"].get<int>() : -1;
				nlohmann::json args = op.contains("args") ? op["args"] : nlohmann::json::array();
				if ( IsBlockedIsdkCall( fn ) )
				{
					item["fn"]    = fn;
					item["ok"]    = false;
					item["error"] = "Refused: " + fn + " is on the native-op blocklist";
					created.push_back( item );
					continue;
				}
				created.push_back( DispatchIsdkCall( fn, args, asId ) );
				continue;
			}

			// Drop all registered handles (start a fresh referencing session).
			if ( kind == "clearHandles" )
			{
				gHandleReg.clear();
				item["ok"] = true;
				created.push_back( item );
				continue;
			}

			// Layer creation is its own thing (not a drawing object; no container/class).
			if ( kind == "layer" )
			{
				std::string lname  = op.value( "name", std::string( "" ) );
				bool        isSheet = ( op.value( "kind", std::string( "design" ) ) == "sheet" );
				short       ltype   = isSheet ? 2 : 1;
				MCObjectHandle lh = gSDK->CreateLayer( TXString( lname.c_str() ), ltype );
				item["created"] = ( lh != nullptr );
				if ( lh )
				{
					gSDK->AddAfterSwapObject( lh );
					// Optional sheet sizing (INCHES; ARCH D = 36x24). Sets paper + drawing area.
					if ( isSheet && op.contains("width") && op.contains("height") &&
					     op["width"].is_number() && op["height"].is_number() )
					{
						double w = op["width"].get<double>(), hgt = op["height"].get<double>();
						gSDK->SetObjectVariable( lh, ovLayerSheetPaperWidth,  TVariableBlock( w )   );
						gSDK->SetObjectVariable( lh, ovLayerSheetPaperHeight, TVariableBlock( hgt ) );
						gSDK->SetObjectVariable( lh, ovLayerSheetWidth,       TVariableBlock( w )   );
						gSDK->SetObjectVariable( lh, ovLayerSheetHeight,      TVariableBlock( hgt ) );
						gSDK->ResetObject( lh );
					}
				}
				created.push_back( item );
				continue;
			}

			// Viewport lives ON a sheet layer (parent), not the active layer. Its source is
			// the design layers (shown by default), so a bare viewport already renders them.
			if ( kind == "viewport" )
			{
				std::string sheetName = op.value( "sheet", std::string( "" ) );
				MCObjectHandle sheetH  = gSDK->GetNamedLayer( TXString( sheetName.c_str() ) );
				if ( !sheetH )
				{
					item["created"] = false;
					item["error"]   = "sheet layer not found";
					item["sheet"]   = sheetName;
					created.push_back( item );
					continue;
				}
				MCObjectHandle vp = gSDK->CreateViewport( sheetH );
				if ( vp )
				{
					if ( op.contains("scale") && op["scale"].is_number() )
						gSDK->SetObjectVariable( vp, ovViewportScale, TVariableBlock( (Real64)op["scale"].get<double>() ) );
					if ( op.contains("name") && op["name"].is_string() )
						gSDK->SetObjectName( vp, TXString( op["name"].get<std::string>().c_str() ) );
					gSDK->ResetObject( vp );

					// Optional crop: a rectangle that clips what the viewport shows. The crop
					// object's coordinate space is what we're probing here (diagnostics below
					// report where VW actually placed it relative to the viewport footprint).
					if ( op.contains("crop") && op["crop"].is_object() )
					{
						const auto& c = op["crop"];
						WorldRect cr;
						cr.Set( WorldPt( c.value("x1", 0.0), c.value("y1", 0.0) ),
						        WorldPt( c.value("x2", 0.0), c.value("y2", 0.0) ) );
						MCObjectHandle cropH = gSDK->CreateRectangle( cr );
						if ( cropH )
						{
							gSDK->SetViewportCropObject( vp, cropH );
							gSDK->SetObjectVariable( vp, ovViewportCropVisible, TVariableBlock( (Boolean)true ) );
						}
						item["cropCreated"] = ( cropH != nullptr );
					}

					// Optional reposition on the sheet (page mm). The viewport + its crop move
					// together, so this re-centers the cropped result on the page.
					if ( op.contains("dx") || op.contains("dy") )
					{
						gSDK->AddBeforeSwapObject( vp );
						gSDK->MoveObject( vp, op.value("dx", 0.0), op.value("dy", 0.0) );
						gSDK->AddAfterSwapObject( vp );
					}

					gSDK->UpdateViewport( vp );
					gSDK->ResetObject( vp );
					gSDK->AddAfterSwapObject( vp );

					// Diagnostics: page position, the scale VW actually stored, the viewport's
					// on-page footprint, and the crop object's bounds. One run of this tells us
					// the world->page transform + scale convention so the rest is pure data.
					Real64 rv;
					TVariableBlock vb;
					if ( gSDK->GetObjectVariable( vp, ovViewportXPosition, vb ) && vb.GetReal64( rv ) ) item["xpos"]  = rv;
					if ( gSDK->GetObjectVariable( vp, ovViewportYPosition, vb ) && vb.GetReal64( rv ) ) item["ypos"]  = rv;
					if ( gSDK->GetObjectVariable( vp, ovViewportScale,     vb ) && vb.GetReal64( rv ) ) item["scaleReadback"] = rv;
					WorldRect vbnd;
					if ( gSDK->GetObjectBounds( vp, vbnd ) )
						item["vpBounds"] = { {"l",vbnd.left},{"t",vbnd.top},{"r",vbnd.right},{"b",vbnd.bottom} };
					MCObjectHandle gotCrop = gSDK->GetViewportCropObject( vp );
					if ( gotCrop )
					{
						WorldRect cbnd;
						if ( gSDK->GetObjectBounds( gotCrop, cbnd ) )
							item["cropBounds"] = { {"l",cbnd.left},{"t",cbnd.top},{"r",cbnd.right},{"b",cbnd.bottom} };
					}
				}
				item["created"] = ( vp != nullptr );
				created.push_back( item );
				continue;
			}

			// ---- Edit ops on an existing NAMED object: delete / move / rotate ----
			if ( kind == "delete" || kind == "move" || kind == "rotate" )
			{
				std::string oname = op.value( "name", std::string( "" ) );
				MCObjectHandle obj = gSDK->GetNamedObject( TXString( oname.c_str() ) );
				if ( !obj )
				{
					item["ok"]    = false;
					item["error"] = "named object not found";
					item["name"]  = oname;
					created.push_back( item );
					continue;
				}
				if ( kind == "delete" )
				{
					gSDK->AddBeforeSwapObject( obj );        // required before DeleteObject(h, true)
					gSDK->DeleteObject( obj, true );
				}
				else if ( kind == "move" )
				{
					gSDK->AddBeforeSwapObject( obj );
					gSDK->MoveObject( obj, op.value( "dx", 0.0 ), op.value( "dy", 0.0 ) );  // mm
					gSDK->AddAfterSwapObject( obj );
					gSDK->ResetObject( obj );
				}
				else // rotate (degrees, about cx/cy or the object's bbox center)
				{
					WorldPt center;
					if ( op.contains( "cx" ) && op.contains( "cy" ) )
						center = WorldPt( op.value( "cx", 0.0 ), op.value( "cy", 0.0 ) );
					else
					{
						WorldRect b;
						gSDK->GetObjectBounds( obj, b );
						center = WorldPt( ( b.left + b.right ) / 2.0, ( b.top + b.bottom ) / 2.0 );
					}
					gSDK->AddBeforeSwapObject( obj );
					gSDK->RotateObjectN( obj, center, op.value( "angle", 0.0 ) );
					gSDK->AddAfterSwapObject( obj );
					gSDK->ResetObject( obj );
				}
				item["ok"] = true;
				created.push_back( item );
				continue;
			}

			// ---- Clear a whole layer (delete every object on it) ----
			if ( kind == "clearLayer" )
			{
				std::string lname  = op.value( "layer", std::string( "" ) );
				MCObjectHandle layerH = gSDK->GetNamedLayer( TXString( lname.c_str() ) );
				if ( !layerH )
				{
					item["ok"]    = false;
					item["error"] = "layer not found";
					item["layer"] = lname;
					created.push_back( item );
					continue;
				}
				// Collect first (deleting while iterating the list would invalidate it).
				std::vector<MCObjectHandle> toDelete;
				gSDK->ForEachObjectInListN( gSDK->FirstMemberObj( layerH ),
				                            [&]( MCObjectHandle o ) { toDelete.push_back( o ); } );
				for ( MCObjectHandle o : toDelete )
				{
					gSDK->AddBeforeSwapObject( o );   // required before DeleteObject(h, true): without it undo silently rolls back
					gSDK->DeleteObject( o, true );
				}
				item["ok"]           = true;
				item["deletedCount"] = (int)toDelete.size();
				created.push_back( item );
				continue;
			}

			// ---- Duplicate a named object (optional offset / new name / target layer) ----
			if ( kind == "duplicate" )
			{
				std::string oname = op.value( "name", std::string( "" ) );
				MCObjectHandle src = gSDK->GetNamedObject( TXString( oname.c_str() ) );
				if ( !src )
				{
					item["ok"]    = false;
					item["error"] = "named object not found";
					item["name"]  = oname;
					created.push_back( item );
					continue;
				}
				MCObjectHandle dup = gSDK->DuplicateObject( src );
				if ( dup )
				{
					if ( op.contains("dx") || op.contains("dy") )
						gSDK->MoveObject( dup, op.value( "dx", 0.0 ), op.value( "dy", 0.0 ) );
					if ( op.contains("newName") && op["newName"].is_string() )
						gSDK->SetObjectName( dup, TXString( op["newName"].get<std::string>().c_str() ) );
					if ( op.contains("layer") && op["layer"].is_string() )
					{
						MCObjectHandle container = gSDK->GetNamedLayer( TXString( op["layer"].get<std::string>().c_str() ) );
						if ( container ) gSDK->AddObjectToContainer( dup, container );
					}
					gSDK->ResetObject( dup );
					gSDK->AddAfterSwapObject( dup );
				}
				item["ok"] = ( dup != nullptr );
				created.push_back( item );
				continue;
			}

			// ---- Group named objects into a new group (optional name / target layer) ----
			if ( kind == "group" )
			{
				MCObjectHandle g = gSDK->CreateGroup();
				int n = 0;
				if ( g && op.contains("members") && op["members"].is_array() )
				{
					for ( const auto& m : op["members"] )
					{
						if ( !m.is_string() ) continue;
						MCObjectHandle mh = gSDK->GetNamedObject( TXString( m.get<std::string>().c_str() ) );
						if ( mh ) { gSDK->AddObjectToContainer( mh, g ); ++n; }
					}
				}
				if ( g )
				{
					if ( op.contains("name") && op["name"].is_string() )
						gSDK->SetObjectName( g, TXString( op["name"].get<std::string>().c_str() ) );
					if ( op.contains("layer") && op["layer"].is_string() )
					{
						MCObjectHandle container = gSDK->GetNamedLayer( TXString( op["layer"].get<std::string>().c_str() ) );
						if ( container ) gSDK->AddObjectToContainer( g, container );
					}
					gSDK->ResetObject( g );
					gSDK->AddAfterSwapObject( g );
				}
				item["ok"]      = ( g != nullptr );
				item["grouped"] = n;
				created.push_back( item );
				continue;
			}

			MCObjectHandle h = nullptr;

			if ( kind == "rect" || kind == "oval" || kind == "rrect" )
			{
				WorldRect wr;
				wr.Set( WorldPt( op.value("x1", 0.0), op.value("y1", 0.0) ),
				        WorldPt( op.value("x2", 0.0), op.value("y2", 0.0) ) );
				if      ( kind == "rect" )  h = gSDK->CreateRectangle( wr );
				else if ( kind == "oval" )  h = gSDK->CreateOval( wr );
				else                        h = gSDK->CreateRRectangle( wr, op.value("rx", 0.0), op.value("ry", 0.0) );
			}
			else if ( kind == "line" )
			{
				h = gSDK->CreateLine( WorldPt( op.value("x1", 0.0), op.value("y1", 0.0) ),
				                      WorldPt( op.value("x2", 0.0), op.value("y2", 0.0) ) );
			}
			else if ( kind == "locus" )
			{
				h = gSDK->CreateLocus( WorldPt( op.value("x", 0.0), op.value("y", 0.0) ) );
			}
			else if ( kind == "text" )
			{
				TXString txt( op.value("text", std::string("")).c_str() );
				h = gSDK->CreateTextBlock( txt, WorldPt( op.value("x", 0.0), op.value("y", 0.0) ),
				                           false, op.value("width", 0.0) );
			}
			else if ( kind == "polygon" )
			{
				// Closed 2D polygon from a vertex list: [[x,y],[x,y],...] (mm). Empty shape,
				// then add corner vertices; FinishCreatedObject's ResetObject recalcs bounds.
				h = gSDK->CreatePolyshape();
				if ( h && op.contains("points") && op["points"].is_array() )
				{
					int added = 0;
					for ( const auto& pt : op["points"] )
					{
						if ( pt.is_array() && pt.size() >= 2 && pt[0].is_number() && pt[1].is_number() )
						{
							gSDK->AddVertex( h, WorldPt( pt[0].get<double>(), pt[1].get<double>() ),
							                 nullptr /*editContext*/, vtCorner, 0, false );
							++added;
						}
					}
					item["vertices"] = added;
				}
			}
			else
			{
				item["created"] = false;
				item["error"]   = "unsupported op (have: rect, oval, rrect, line, locus, text, polygon)";
				created.push_back( item );
				continue;
			}

			FinishCreatedObject( h, op, item );
			created.push_back( item );
		}
	}

	result["ok"]      = true;
	result["lang"]    = "ops";
	result["created"] = created;
	return result;
}

}

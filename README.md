# vw-mcp

MCP server for Vectorworks: lets AI assistants script Vectorworks safely.

> **Status: work in progress.** This repo is a scaffold. The safety layer, sweep harness and relay are here; the
> headless plug-in builds but does nothing yet beyond logging at launch. Not usable end to end. First target:
> macOS, Vectorworks 2027.

## Architecture

1. **Plug-in** (`plugin/`): a headless `vw-mcp.vwlibrary`. An `IObjUpdateSupport` provider starts at Vectorworks launch.
2. **Bridge** (in the plug-in, [#6](https://github.com/stevenmorgan94/vw-mcp/issues/6)): a local HTTP server on `127.0.0.1` queues jobs and runs them on the main thread.
3. **Relay** (`relay/`): a Node MCP server (`npx -y vw-mcp`) that MCP clients talk to; it forwards jobs to the plug-in.
4. **Safety** (`safety/`): every `vs.*` call is checked in the engine against a class table built by testing each function.
5. **Sweep** (`sweep/`): the harness that builds that table by running every function against a throwaway document.

## Layout

| Path | What |
|---|---|
| `plugin/` | Xcode project (`VW_YEAR`, default 2027), sources in `src/{bridge,nativeops,safety}` |
| `relay/` | The MCP server (Node) |
| `safety/` | `vwguard.py` (in-engine guard), `build_table.py`, `vs-safety-table.json`, `functions.csv` |
| `sweep/` | The sweep harness and derive step |
| `docs/` | [Hardening spec](docs/MCP_HARDENING_SPEC.md), [glossary](docs/GLOSSARY.md), [sweep results](docs/sweep/README.md) |
| `tools/` | Build and deploy scripts, ISDK dispatch generator (stub) |

## Building the plug-in (macOS)

Needs Xcode and the Vectorworks SDK for the target year (from Vectorworks' developer program; not included).

```sh
VW_SDK_DIR=/path/to/VectorworksSDK/SDK2027 tools/build-plugin.sh 2027 Debug   # -> build/2027/Debug/vw-mcp.vwlibrary
tools/deploy-plugin.sh 2027 Debug                                            # copies it into the VW 2027 Plug-ins folder
```

`VW_SDK_DIR` defaults to `../VectorworksSDK/SDK<year>` next to this checkout. For builds from the Xcode app, copy
`plugin/Config/Local.xcconfig.example` to `plugin/Config/Local.xcconfig` and set it there.

Rebuild the safety table and its generated C++ include after a sweep: `python3 safety/build_table.py`.

## Trademark

Vectorworks is a trademark of Vectorworks, Inc. This project is not affiliated with, endorsed by or sponsored by
Vectorworks, Inc.

## Licence

MIT. See [LICENSE](LICENSE). The Vectorworks SDK is licensed separately by Vectorworks, Inc. and is not part of this repo.

Provenance: split out of the bridge in the author's SolotechSuite plug-in.

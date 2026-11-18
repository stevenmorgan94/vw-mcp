# vw-mcp

MCP server for Vectorworks. It lets AI assistants (Claude, Cursor, VS Code and others) run Python inside Vectorworks, with every call safety-checked: calls that crash, hang or open dialogs are refused before they run, handle arguments are checked for the right kind of object, and each job is one undo step.

> **Beta.** macOS, Vectorworks 2027. Test on copies of your drawings.

## Quick start

1. **Download** `vw-mcp-<version>-vw2027-mac.zip` from the [latest release](https://github.com/stevenmorgan94/vw-mcp/releases/latest) and unzip it (double-click). You get `vw-mcp.vwlibrary` in Downloads.
2. **Clear the download flag** (the plug-in isn't notarized, so macOS won't let Vectorworks load it otherwise). Open Terminal and paste:
   ```sh
   xattr -dr com.apple.quarantine ~/Downloads/vw-mcp.vwlibrary
   ```
   Skip this and Vectorworks lists vw-mcp as incompatible ("Compiled for Version: Unknown") and won't load it.
3. **Install the plug-in:** move `vw-mcp.vwlibrary` into
   `~/Library/Application Support/Vectorworks/2027/Plug-ins/`
   (in Finder: Go › Go to Folder…, paste the path). Then start Vectorworks, open **Tools › Plug-ins › Plug-in Manager… › Third-party Plug-ins**, turn on **vw-mcp**, and restart Vectorworks.
4. **Connect your AI app** (see below).
5. **Check:** in Vectorworks, **Help › vw-mcp Status…** opens the status palette. Its light turns green once your AI app has connected. The **Connect AI** tab has the same setup snippets as below, with copy buttons.

### Connect your AI app

| App | Setup |
|---|---|
| **Claude Desktop** | Download `vw-mcp.mcpb` from the [latest release](https://github.com/stevenmorgan94/vw-mcp/releases/latest) and double-click it. Then quit Claude fully (⌘Q) and reopen it. No Node.js needed. |
| **Claude Code** | In Terminal on this Mac: `claude mcp add vw-mcp -- npx -y vw-mcp`, then start a new session (needs [Node.js](https://nodejs.org) 20+). |
| **Cursor, VS Code, others** | Add an MCP server: `{ "mcpServers": { "vw-mcp": { "command": "npx", "args": ["-y", "vw-mcp"] } } }` (needs [Node.js](https://nodejs.org) 20+). |

**Use a chat or session running on the Mac with Vectorworks.** Cloud and web sessions (claude.ai in a browser, remote Code sessions) can't reach it.

The server sends these house rules to your AI when it connects. If your app ignores server instructions, paste them in yourself (they're also on the palette's Connect AI tab):

```text
You can control Vectorworks through the vw-mcp tools.
- Call vw_bridge_status first. If documentOpen is false, ask me to open a drawing.
- Run Python with execute_script (the vs module is available). print() JSON to return data.
- Every vs.* call is safety-checked. A refusal comes back as an error with a reason and advice. Don't retry a refused call; use the alternative it names.
- Use vw_lookup_function before calling an unfamiliar vs.* function.
- Plug-in objects (Stage Deck, lighting devices, …) that a job creates or changes are rebuilt automatically when it finishes (autoReset in the result), so their 2D/3D shows the new attributes and parameters. A vs.ResetObject inside the creating script does nothing; check the result in a new call.
- Create plug-in objects with vs.CreateCustomObjectN(name, pt, rot, False): False skips the Object Preferences dialog.
- A solid fill (vs.SetFPat(h, 1)) paints with the background colour: set vs.SetFillBack as well as vs.SetFillFore.
- Only set allowUnclassified or allowDocumentLevel if I ask you to.
- Each job is one undo step in Vectorworks.
```

## Tools

| Tool | What it does |
|---|---|
| `vw_bridge_status` | Connection, Vectorworks build, document open, dialog blocking, paused, safety table, last refusal. |
| `execute_script` | Runs Python in the open document. Options: `timeoutSec` (default 30, max 300), `allowUnclassified`, `allowDocumentLevel`. |
| `run_native_op` | Changes the document through native SDK calls (rect, line, text, layer, viewport, move, … and a generic `call`). |
| `vw_lookup_function` | A `vs.*` function's safety class, argument checks, signature and alternative. |

A refused call returns an error with `{refused, function, class, reason, alternative, partialChanges, advice}`. If earlier calls in the same job already changed the drawing, **Edit › Undo** reverts the whole job.

## The status palette

**Help › vw-mcp Status…** has four tabs:

- **Status:** the bridge, connected AI apps, the open drawing and versions.
- **Connect AI:** setup snippets and the house rules, with copy buttons.
- **Activity:** the last 50 jobs. Click one to see the code it ran (the last 20 are kept in memory until Vectorworks quits).
- **Utility:**
  - **Pause AI** refuses every new job until you turn it off; your AI is told to wait for you.
  - **Save the drawing before AI changes it** saves each drawing once, before the first AI job on it since Vectorworks started. Untitled drawings and project files are skipped.
  - **Save as script** keeps a Python job your AI ran: it goes into a *vw-mcp Scripts* script palette in the drawing's Resource Manager, where a double-click runs it again. Saved scripts run as ordinary Vectorworks scripts, without vw-mcp's safety checks. Plug-in objects they create or change can keep their old 2D look: run **Tools › Utilities › Reset All Plug-Ins** afterwards.
  - **Copy diagnostics** copies versions, status and recent errors for a bug report.

## Troubleshooting

| Symptom | Fix |
|---|---|
| "Vectorworks with the vw-mcp plug-in is not running" | Start Vectorworks. If it's running, check the plug-in is in the Plug-ins folder and enabled (*Tools › Plug-ins › Plug-in Manager › Third-party Plug-ins*), then restart Vectorworks. |
| Your AI says it has no Vectorworks tools | It's a cloud or web session: use one running on this Mac. For Claude Desktop, quit it fully (⌘Q) and reopen after installing. |
| The MCP server won't start in Cursor, VS Code or another app | The app can't find Node (common when Node is installed with nvm). Replace `"npx"` with the full path that `which npx` prints in Terminal. |
| No **Help › vw-mcp Status…** item | The plug-in isn't loaded: same fix as above. |
| Status says "Bridge not running" | Ports 47823–47830 are all in use. Quit whatever uses them and restart Vectorworks. |
| "AI jobs are paused in Vectorworks" | Turn off **Pause AI** on the palette's Utility tab. |
| "Vectorworks is busy (a dialog is open)" | Close the open dialog in Vectorworks, then retry. |
| "No document is open" | Open or create a drawing. |
| A version warning in `vw_bridge_status` | The plug-in and the relay come from different releases. Install both from the same release. |
| vw-mcp is in the *Incompatible Plug-ins Report* with version "Unknown", or the plug-in file disappears | The download flag wasn't cleared (step 2). Download the zip again, run the `xattr` line on the unzipped plug-in and reinstall. Vectorworks switches a plug-in off after it fails to load, so turn **vw-mcp** back on in *Plug-in Manager › Third-party Plug-ins*, then restart Vectorworks. |

## How it works

1. **Plug-in** (`plugin/`): a headless `vw-mcp.vwlibrary`. It starts with Vectorworks, serves a local HTTP endpoint on `127.0.0.1` (token-protected, browsers refused), and runs each job on the main thread. **Help › vw-mcp Status…** shows its state.
2. **Relay** (`relay/`, `npx -y vw-mcp`): the MCP server your AI app launches. It finds the plug-in through a discovery file and forwards jobs.
3. **Safety** (`safety/`): every `vs.*` call is checked in the engine against a table built by running each of ~2,800 functions against a throwaway document ([results](docs/sweep/README.md), [spec](docs/MCP_HARDENING_SPEC.md)).
4. **Sweep** (`sweep/`): the harness that builds that table.

## Building from source (macOS)

Needs Xcode and the Vectorworks SDK for the target year (from Vectorworks' developer program; not included).

```sh
VW_SDK_DIR=/path/to/VectorworksSDK/SDK2027 tools/build-plugin.sh 2027 Debug   # -> build/2027/Debug/vw-mcp.vwlibrary
tools/deploy-plugin.sh 2027 Debug                                            # copies it into the VW 2027 Plug-ins folder
cd relay && npm ci && node server.mjs                                         # the relay over stdio
```

`VW_SDK_DIR` defaults to `../VectorworksSDK/SDK<year>` next to this checkout. For builds from the Xcode app, copy `plugin/Config/Local.xcconfig.example` to `plugin/Config/Local.xcconfig` and set it there. After a sweep, rebuild the safety table with `python3 safety/build_table.py`; after editing `plugin/palette/index.html`, run `python3 tools/embed_palette.py`.

## Trademark

Vectorworks is a trademark of Vectorworks, Inc. This project is not affiliated with, endorsed by or sponsored by Vectorworks, Inc.

## Licence

MIT. See [LICENSE](LICENSE). The Vectorworks SDK is licensed separately by Vectorworks, Inc. and is not part of this repo.

Provenance: split out of the bridge in the author's SolotechSuite plug-in.

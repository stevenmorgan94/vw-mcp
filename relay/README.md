# vw-mcp

MCP server for Vectorworks. It lets AI assistants (Claude, Cursor, VS Code and others) run Python inside Vectorworks 2027 on macOS through the **vw-mcp plug-in**, with every call safety-checked: calls that crash, hang or open dialogs are refused before they run, and each job is one undo step.

**Beta:** test on copies of your drawings.

This package is the relay that AI apps launch. It needs the plug-in, which you install separately: see the [quick start](https://github.com/stevenmorgan94/vw-mcp#quick-start).

```sh
claude mcp add vw-mcp -- npx -y vw-mcp     # Claude Code
```

Other apps: add `{ "command": "npx", "args": ["-y", "vw-mcp"] }` as an MCP server. Claude Desktop users can install `vw-mcp.mcpb` from the [release page](https://github.com/stevenmorgan94/vw-mcp/releases) instead.

Not affiliated with Vectorworks, Inc. MIT licence.

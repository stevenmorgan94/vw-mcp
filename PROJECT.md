---
name: vw-mcp
status: active
context: solotech
next_action: "Reclassify the 4 never-reproduced sweep crashers (#31), then build the propose_script hand-off (#30)"
tracker_note: vw-mcp
---
# Where I left off

Execution runs off the wayfinder map, issue #1 (tickets are child issues). Last session: 2026-11-18 on mac-1.

## Current state

- main at f0aec67: plug-in + relay, safety table enforced, auto-reset of PIOs (#26), status palette with the Utility tab (#28).
- #29 (jobs inside a real menu command) is closed: **no difference**. Write-up, harness and raw results are on branch
  `research/menu-context` (pushed, never merged): `docs/research/29-menu-context/README.md`.
- The VW 2027 plug-in installed on mac-1 is still the **research build** from that branch (adds a hidden
  "vw-mcp Run Job (internal)" menu command). Rebuild and deploy from main before real use
  (`tools/build-plugin.sh`, `tools/deploy-plugin.sh`).
- The research command was added to the "Steven 4K" workspace for the test; it can be removed.

## Next steps

1. #31: reclassify DisplayLayerScaleDialog, DisplayOrganizationDialog (→ interactive), SetTexSpaceEndCap,
   RetrieveOpenGLPrefs (→ safe?). They never crashed in 3 runs; sweep v2 saw each once.
2. #30: `propose_script` hand-off. "Run in Vectorworks" = a normal bridge job started by the user's palette click;
   never offer crasher/hang; follow-up reset job for PIOs.
3. #19 live-check script, #20 release.sh + CI, #22 cut v0.1.0 (needs npm account). Later: #15 ISDK sweep, #9 Windows, #10.

## Gotchas / decisions

- `DoMenuName` runs nothing (-3) unless the command is in the user's workspace; menu context also behaves exactly like the
  idle timer for every crasher. Don't revisit the menu path.
- A PIO created in a script can't be fixed in the same run (ResetObject or Reset All Plug-Ins); reset in a later job.
- Crash tests: throwaway untitled docs only; unguarded via marker `~/Library/Application Support/Vectorworks/2027/Plug-ins/Data/vw-mcp/SWEEP_MODE` (remove after).
- Relaunch after a crash can stall on "Login Settings" if the license server is unreachable (VPN), and on the
  Incompatible Plug-ins Report.
- Don't send keystrokes/mouse while the user is at the machine; AX button clicks only.

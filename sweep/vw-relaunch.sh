#!/bin/zsh
# Relaunch Vectorworks 2027 with no human: kill it if running, launch, clear the startup
# dialogs, open a blank doc, and wait for the bridge palette to reach the MCP relay.
# Needs Accessibility for the app running this script. Exit 0 = palette connected.
# Assumes the bridge palette was left open AND expanded at the last clean quit.
# TODO(#6): once the plug-in is headless, wait for its /status instead of the palette.
set -u
TIMEOUT=${VW_RELAUNCH_TIMEOUT:-420}
log() { print -r -- "$(date +%H:%M:%S) $*"; }

if pgrep -x Vectorworks >/dev/null; then
  log "killing running Vectorworks"
  pkill -9 -x Vectorworks
  for i in {1..30}; do pgrep -x Vectorworks >/dev/null || break; sleep 1; done
fi
VWLOG=~/Library/Application\ Support/Vectorworks/2027/VW\ User\ Log.txt
homes() { local n; n=$(grep -c "Source = VWLaunch" "$VWLOG" 2>/dev/null); print ${n:-0}; }
homes0=$(homes)   # home-screen opens before this launch
open -a "Vectorworks 2027"
log "launched"

start=$SECONDS; newdoc_sent=0; last=""
while (( SECONDS - start < TIMEOUT )); do
  out=$(osascript <<'EOF' 2>&1
tell application "System Events"
  set acted to ""
  -- macOS crash reporter for the previous run (if it shows up)
  repeat with pn in {"UserNotificationCenter", "Problem Reporter", "CrashReporter"}
    if exists process (pn as text) then
      tell process (pn as text)
        repeat with w in windows
          try
            if exists button "Ignore" of w then
              click button "Ignore" of w
              set acted to acted & "crash-reporter:Ignore "
            else if exists button "OK" of w then
              click button "OK" of w
              set acted to acted & "crash-reporter:OK "
            end if
          end try
        end repeat
      end tell
    end if
  end repeat
  if not (exists process "Vectorworks") then return "noproc " & acted
  tell process "Vectorworks"
    set names to {}
    repeat with w in windows
      try
        set t to name of w
        set end of names to t
        if t is "Login Settings" then
          click button "Login" of w
          set acted to acted & "login "
        else if t is "Incompatible Plug-ins Report" then
          click button "Close" of w
          set acted to acted & "incompatible:Close "
        else if t is "Unknown Developer Plug-ins" then
          click button "Continue" of w
          set acted to acted & "unknown-dev:Continue "
        else if t is "Create Document" then
          click button "OK" of w
          set acted to acted & "create-doc:OK "
        else if (exists button "Don't Send" of w) then
          click button "Don't Send" of w
          set acted to acted & "vw-crash-report:Don't Send "
        end if
      end try
    end repeat
    set AppleScript's text item delimiters to ","
    return "wins[" & (names as text) & "] " & acted
  end tell
end tell
EOF
)
  [[ "$out" == *" "?* && "$out" != "$last" ]] && log "$out"; last=$out
  if curl -s -m 2 http://127.0.0.1:9101/health | grep -q '"paletteConnected":true' \
     && { (( ! ${VW_NEWDOC:-1} )) || [[ "$out" == *Untitled* ]]; }; then
    log "READY: palette connected after $((SECONDS-start))s"; exit 0
  fi
  # Startup finished (home screen up, no document) -> ask for a blank doc once.
  if (( ! newdoc_sent && ${VW_NEWDOC:-1} )) && { (( $(homes) > homes0 )) || curl -s -m 2 http://127.0.0.1:9101/health | grep -q '"paletteConnected":true'; } \
     && [[ "$out" != *Untitled* && "$out" != *"Create Document"* ]]; then
    osascript -e 'tell application "Vectorworks 2027" to activate' -e 'delay 0.5' \
      -e 'tell application "System Events" to tell process "Vectorworks" to keystroke "n" using command down' >/dev/null 2>&1
    newdoc_sent=1; log "sent Cmd-N"
  fi
  sleep 2
done
log "TIMEOUT: palette never connected"; exit 1

#!/bin/zsh
# Overnight sweep: keep the Mac awake, run the sweep, then quit VW and restore the user folder.
# Usage: [TAG=v2] zsh run-overnight.sh <user-folder-backup-dir> [sweep.mjs args, e.g. --v2]
# The log goes to results/run-$TAG.jsonl (TAG defaults to v0).
set -u
HERE=${0:A:h}; TAG=${TAG:-v0}; BACKUP=${1:?backup dir}; shift; LIVE=~/Library/Application\ Support/Vectorworks/2027
[[ -d "$BACKUP" ]] || { echo "no backup at $BACKUP"; exit 1; }
# Sweep mode: the bridge runs the raw engine (no safety guard) so crashers can be classified.
# The marker lives in Plug-ins/, which the restore below excludes, so remove it explicitly.
MARKER="$LIVE/Plug-ins/Data/vw-mcp/SWEEP_MODE"
mkdir -p "${MARKER:h}"
touch "$MARKER"
# The harness talks MCP over HTTP: run the relay in --http mode for the length of the sweep.
node "$HERE/../relay/server.mjs" --http 2>>"$HERE/results/relay-$TAG.log" & RELAY_PID=$!
trap 'rm -f "$MARKER"; kill $RELAY_PID 2>/dev/null' EXIT
caffeinate -dims node "$HERE/sweep.mjs" --log "$HERE/results/run-$TAG.jsonl" "$@"
rc=$?
echo "$(date +%T) sweep exited $rc; quitting VW and restoring the user folder"
pkill -9 -x Vectorworks; sleep 3
rsync -a --delete --exclude 'Plug-ins/' --exclude 'VW User Log*' "$BACKUP/" "$LIVE/"
echo "$(date +%T) restored $LIVE from $BACKUP"
node "$HERE/summarize.mjs" "$HERE/results/run-$TAG.jsonl" > "$HERE/results/run-$TAG-summary.md"
echo "$(date +%T) summary written"

#!/bin/bash
# Copies a built vw-mcp.vwlibrary into the user's Vectorworks Plug-ins folder.
# Run after each native (C++) rebuild, then restart Vectorworks. Each Vectorworks
# version needs its own build, so pass the year you built for.
#
# Always COPIES. Vectorworks' plug-in scanner does not follow symlinks: a linked
# .vwlibrary is silently ignored and never loads.
#
# Usage: tools/deploy-plugin.sh [<year>] [Debug|Release]
#   Default year: 2027 (or $VW_YEAR)   Default config: Debug

set -euo pipefail

YEAR="${VW_YEAR:-2027}"
CONFIG="Debug"
for arg in "$@"; do
  case "$arg" in
    Debug|Release) CONFIG="$arg" ;;
    20[0-9][0-9]) YEAR="$arg" ;;
    *) echo "✗ Unknown argument: $arg"; exit 1 ;;
  esac
done

REPO="$( cd "$( dirname "${BASH_SOURCE[0]}" )/.." && pwd )"
BUILD_OUTPUT="$REPO/build/${YEAR}/${CONFIG}/vw-mcp.vwlibrary"
VW_PLUGINS="${HOME}/Library/Application Support/Vectorworks/${YEAR}/Plug-ins"
DEST="${VW_PLUGINS}/vw-mcp.vwlibrary"

if [ ! -d "$BUILD_OUTPUT" ]; then
  echo "✗ Build output not found: $BUILD_OUTPUT"
  echo "  Build it first: tools/build-plugin.sh $YEAR $CONFIG"
  exit 1
fi

mkdir -p "$VW_PLUGINS"
rm -rf "$DEST"
# -L: dereference any symlink inside the bundle, so the copy is self-contained.
cp -RL "$BUILD_OUTPUT" "$DEST"
echo "✓ Copied: $DEST  ($CONFIG)"
echo "  Restart Vectorworks $YEAR to load the new binary."

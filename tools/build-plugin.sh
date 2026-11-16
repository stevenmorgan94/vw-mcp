#!/bin/bash
# Builds vw-mcp.vwlibrary against one Vectorworks SDK year. Each year needs its own binary
# (Vectorworks rejects a module whose SDK_VERSION doesn't match its own).
# Output: build/<year>/<config>/vw-mcp.vwlibrary
#
# Usage: tools/build-plugin.sh [<year>] [Debug|Release]
#   Default year: 2027 (or $VW_YEAR)   Default config: Debug
#
# The SDK path: $VW_SDK_DIR (the folder holding SDKLib/ for that year).
# Default: <repo>/../VectorworksSDK/SDK<year>, i.e. a VectorworksSDK folder next to this checkout.

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
SDK="${VW_SDK_DIR:-$REPO/../VectorworksSDK/SDK${YEAR}}"

if [ ! -d "$SDK/SDKLib" ]; then
  echo "✗ Vectorworks SDK not found: $SDK"
  echo "  Set VW_SDK_DIR to the SDK folder for $YEAR (the one holding SDKLib/)."
  exit 1
fi

echo "▸ Building $CONFIG for Vectorworks $YEAR (SDK: $SDK)…"
xcodebuild -project "$REPO/plugin/vw-mcp.xcodeproj" -target vw-mcp \
  -configuration "$CONFIG" VW_YEAR="$YEAR" VW_SDK_DIR="$SDK" build -quiet
echo "✓ Built: build/${YEAR}/${CONFIG}/vw-mcp.vwlibrary"

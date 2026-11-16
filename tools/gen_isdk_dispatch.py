#!/usr/bin/env python3
"""Generate the ISDK dispatch table for run_native_op's `call` op.  (STUB: not implemented yet.)

  python3 tools/gen_isdk_dispatch.py --sdk <path to SDK2027> [--out plugin/src/nativeops/IsdkDispatch.generated.inc]

The committed plugin/src/nativeops/IsdkDispatch.inc was generated from the VW 2026 ISDK.h by a script
that was never committed; its 5 entries removed in 2027 were deleted by hand. This generator replaces it.
What it has to do (docs/research/native-ops-split.md, issue #8):

1. Parse the `class DYNAMIC_ATTRIBUTE ISDK : public IVWSingletonUnknown` body of
   <sdk>/SDKLib/Include/Interfaces/VectorWorks/ISDK.h: strip comments, match
   `virtual <ret> [VCOM_CALLTYPE] <Name>(<params>) = 0;` (VCOM_CALLTYPE is optional: 2027's
   ImportImageFile has none), and keep default arguments so trailing defaulted params are optional.
2. Reproduce the existing marshalling rules:
     integer / enum / Boolean          -> JSON number or bool
     double, WorldCoord                -> JSON number
     const TXString&                   -> JSON string
     MCObjectHandle                    -> {"$h": id} / {"$name": ...} / {"$layer": ...}
     WorldPt / WorldPt3 / WorldRect    -> [x,y] / [x,y,z] / [x1,y1,x2,y2]
     non-const scalar, TXString& or point reference -> r["out"][<paramName>]
     MCObjectHandle return             -> registered in the handle registry under `as`, r["as"]; ret = bool
     other returns                     -> r["ret"]
   and add: a null check for every handle parameter, std::vector<TXString> <-> JSON array.
3. Pick one overload per name deterministically, or name the extra ones `Name#2`.
4. Emit only the shim table. The marshal helpers and handle registry move to a hand-written header.
5. Join with the ISDK safety table (#11) and emit the refusal list from it.
6. Stamp the SDK path, SDK_VERSION and method count into the generated header.

The repo ships the generator and its output, never a copy of ISDK.h (Vectorworks-licensed).
"""
import argparse
import sys


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument('--sdk', required=True, help='Vectorworks SDK folder (the one holding SDKLib/)')
    ap.add_argument('--out', default='plugin/src/nativeops/IsdkDispatch.generated.inc')
    ap.parse_args()
    sys.exit('gen_isdk_dispatch.py is a stub: see the docstring and issue #8. Not implemented yet.')


if __name__ == '__main__':
    main()

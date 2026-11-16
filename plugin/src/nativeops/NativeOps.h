//
//  NativeOps.h
//
#pragma once

namespace VwMcp
{
    // `opsJson` is a JSON array of { op, ... } objects. Main thread only, inside a job's undo scope.
    // `opts`: allowUnclassified / allowDocumentLevel, applied to the generic `call` op (#11).
    nlohmann::json RunNativeOps(const std::string& opsJson, const nlohmann::json& opts);
}

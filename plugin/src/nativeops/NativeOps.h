//
//  NativeOps.h
//
#pragma once

namespace VwMcp
{
    // `opsJson` is a JSON array of { op, ... } objects. Main thread only, inside a job's undo scope.
    nlohmann::json RunNativeOps(const std::string& opsJson);
}

#pragma once

#include <optional>

#include "DrawingKwargs.hpp"

namespace parser {
    std::optional<kwargs::DrawingKwargs> Parse(int32_t argc, char *argv[]);
}

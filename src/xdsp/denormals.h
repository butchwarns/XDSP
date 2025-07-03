#pragma once

namespace xdsp::denormals {

#include <cmath>
#include <limits>

/**
 * @brief Replace a (possibly) denormalized value with zero.
 *
 * This function replaces a denormalized input with zero,
 * and leaves normal values untouched.
 *
 * @param val Value to flush
 */
static void flush(double* val) {
  if (abs(*val) < std::numeric_limits<double>::min()) {
    *val = 0.0;
  }
}

}  // namespace xdsp::denormals
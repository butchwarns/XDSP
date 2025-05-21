#include "LinearCongruentialGenerator.h"

#include <xdsp/scaling.h>

#include <cstdint>

namespace xdsp::noise {

LinearCongruentialGenerator::LinearCongruentialGenerator(uint32_t seed)
    : state(seed) {}

double LinearCongruentialGenerator::process() {
  {
    state = state * 196314165 + 907633515;

    const auto unipolar = (double)state / (double)UINT32_MAX;

    return xdsp::scaling::to_bipolar(unipolar);
  }
}

}  // namespace xdsp::noise
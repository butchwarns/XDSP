#ifndef CONST_H
#define CONST_H

#include <cmath>

/**
 * @brief Mathematical and other DSP-related constants
 */
namespace xdsp::constants {

/**
 * @brief @f$ \pi @f$
 */
constexpr double PI =
    3.14159265358979323846264338327950288419716939937510582097494459230781640628620899;

/**
 * @brief @f$ 2\pi @f$
 */
constexpr double TWO_PI = 2.0 * PI;

/**
 * @brief @f$ \frac{\pi}{2} @f$
 */
constexpr double PI_TWO = PI / 2.0;

/**
 * @brief @f$ \sqrt{2} @f$
 */
constexpr double SQRT_2 =
    1.4142135623730950488016887242096980785696718753769480731766797379;

}  // namespace xdsp::constants

#endif  // CONSTANTS_H
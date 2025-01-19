#ifndef CONST_H
#define CONST_H

#include <cmath>

/**
 * @brief Mathematical and other DSP-related constants.
 */
namespace xdsp::consts {

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
 * @brief @f$ \sqrt{2} @f$
 */
constexpr double SQRT_2 =
    1.4142135623730950488016887242096980785696718753769480731766797379;

/**
 * @brief Minimum filter cutoff frequency (approx. lower threshold of human
 * hearing)
 */
constexpr double MIN_FILTER_FREQ = 20.0;

/**
 * @brief Maximum filter cutoff frequency (approx. upper threshold of human
 * hearing)
 */
constexpr double MAX_FILTER_FREQ = 20480.0;

}  // namespace xdsp::consts

#endif  // CONSTS_H
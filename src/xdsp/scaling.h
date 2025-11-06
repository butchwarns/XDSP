#pragma once

#include <xdsp/constants.h>

#include <cmath>

/**
 * @brief A collection of scaling and range conversion functions.
 */
namespace xdsp::scaling {

/**
 * @brief Linearly scales value from [-1.0, 1.0] to a given output range.\n
 *        (The "lo" bound can be higher than the "hi" bound.)
 *
 * @tparam T Numeric type
 * @param in Value to map
 * @param out_lo Lower bound of output range
 * @param out_hi Upper bound of output range
 * @return Mapped value
 */
template <typename T>
inline T lerp_bipolar(const T in, const T out_lo, const T out_hi) {
  return (in + static_cast<T>(1.0)) / static_cast<T>(2.0) * (out_hi - out_lo) +
         out_lo;
}

/**
 * @brief Linearly scales value from [0.0, 1.0] to a given output range.\n
 *        (The "lo" bound can be higher than the "hi" bound.)
 *
 * @tparam T Numeric type
 * @param in Value to map
 * @param out_lo Lower bound of output range
 * @param out_hi Upper bound of output range
 * @return Mapped value
 */
template <typename T>
inline T lerp_unipolar(const T in, const T out_lo, const T out_hi) {
  return in * (out_hi - out_lo) + out_lo;
}

/**
     * @brief Linearly scales value from input range to output range.\n
     *        (The "lo" bounds can be higher than the "hi" bounds.)

     * @tparam T Numeric type
     * @param in Value to map
     * @param in_lo Lower bound of input range
     * @param in_hi Upper bound of input range
     * @param out_lo Lower bound of output range
     * @param out_hi Upper bound of output range
     * @return Scaled value
     */
template <typename T>
inline T lerp(const T val, const T in_lo, const T in_hi, const T out_lo,
              const T out_hi) {
  const T in_norm = (val - in_lo) / (in_hi - in_lo);
  return lerp_unipolar<T>(in_norm, out_lo, out_hi);
}

/**
 * @brief Normalizes a value to [0.0, 1.0].
 *
 * @tparam T Numeric type
 * @param in Value to normalize
 * @param in_lo Lower bound of input value
 * @param in_hi Uppter bound of input value
 * @return Normalised value
 */
template <typename T>
inline T normalize_unipolar(const T in, const T in_lo, const T in_hi) {
  return lerp(in, in_lo, in_hi, static_cast<T>(0.0), static_cast<T>(1.0));
}

/**
 * @brief Normalizes a value to [-1.0, 1.0].
 *
 * @tparam T Numeric type
 * @param in Value to normalize
 * @param in_lo Lower bound of input value
 * @param in_hi Uppter bound of input value
 * @return Normalized value
 */
template <typename T>
inline T normalize_bipolar(const T in, const T in_lo, const T in_hi) {
  return lerp(in, in_lo, in_hi, static_cast<T>(-1.0), static_cast<T>(1.0));
}

/**
 * @brief Linearly scale from unipolar to bipolar range.\n
 *        (E.g., [0.0, 1.0] will be mapped to [-1.0, 1.0].)
 *
 * @tparam T Numeric type
 * @param in Unipolar value
 * @return Mapped bipolar value
 */
template <typename T>
inline T to_bipolar(T unipolar) {
  return lerp_unipolar<T>(unipolar, static_cast<T>(-1.0), static_cast<T>(1.0));
}

/**
 * @brief Linearly scale from bipolar to unipolar range.\n
 *        (E.g., [-1.0, 1.0] will be mapped to [0.0, 1.0].)
 *
 * @tparam T Numeric type
 * @param bipolar Bipolar value
 * @return Unipolar value
 */
template <typename T>
inline T to_unipolar(T bipolar) {
  return lerp<T>(bipolar, static_cast<T>(-1.0), static_cast<T>(1.0),
                 static_cast<T>(0.0), static_cast<T>(1.0));
}

/**
 * @brief Skew the unit interval
 *
 * skew = 1.0 gives a linear map
 * skew in [0.0, 1.0[ gives more resolution in the upper range
 * skew in [1.0, INF[ gives more resolution in the lower range
 *
 * @tparam FloatType (float or double)
 * @param val_norm Value in [0.0, 1.0]
 * @param skew Skew factor
 * @return Skewed value in [0.0, 1.0]
 */

template <typename FloatType>
inline FloatType skew(FloatType val_norm, FloatType skew);

template <>
inline double skew(double val, double skew) {
  return pow(val, 1.0 / skew);
}

template <>
inline float skew(float val, float skew) {
  return powf(val, 1.0f / skew);
}

/**
 * @brief Undo skew on the unit interval
 *
 *  Inverse of skew() function
 *
 * @tparam FloatType (float or double)
 * @param val_norm_skewed Skewed value in [0.0, 1.0]
 * @param skew Skew factor
 * @return Unskewed value in [0.0, 1.0]
 */

template <typename FloatType>
inline FloatType unskew(FloatType val_norm, FloatType skew);

template <>
inline double unskew(double val, double skew) {
  return pow(val, skew);
}

template <>
inline float unskew(float val, float skew) {
  return powf(val, skew);
}

}  // namespace xdsp::scaling

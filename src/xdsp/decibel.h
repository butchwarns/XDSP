#ifndef DECIBEL_H
#define DECIBEL_H

#include <cmath>

/**
 * @brief Decibel conversion functions.
 */
namespace xdsp::decibel {

/**
 * @brief Reference value for all decibel conversions.
 */
constexpr double DB_REF = 1.0;

/**
 * @brief Converts decibel (relative to 1.0) value to linear gain factor.
 *
 * @param db [dB]
 * @return Linear gain factor
 */
inline double to_linear(double db) { return pow(10.0, db / 20.0); }

/**
 * @copydoc to_linear(double)
 */
inline float to_linear(float db) { return powf(10.0f, db / 20.0f); }

/**
 * @brief Converts decibel (relative to 1.0) value to linear gain factor.\n
 *        If value is below given threshold, this function returns 0.
 *
 * @param db [dB] value to convert
 * @param threshold [dB] off-threshold
 * @return Linear gain factor
 */
inline double to_linear_off(double db, double threshold) {
  if (db <= threshold) {
    return 0.0;
  } else {
    return to_linear(db);
  }
}

/**
 * @copydoc to_linear_off(const double, const double)
 */
inline float to_linear_off(float db, double threshold) {
  if (db <= threshold) {
    return 0.0f;
  } else {
    return to_linear(db);
  }
}

/**
 * @brief Converts linear gain factor to decibel (relative to 1.0) value.
 *
 * @param [1] Linear gain factor
 * @return [dB] Decibel value
 */
inline double to_db(double linear) { return 20.0 * log10(linear); }

/**
 * @copydoc linear_to_db(const double)
 */
inline float to_db(float linear) { return 20.0f * log10f(linear); }

/**
 * @brief Apply a decibel gain to a linear signal.
 *
 * @param lin Linear signal
 * @param gain [dB] Gain
 * @return Amplified or attenuated signal
 */
inline double apply(double lin, double gain) { return lin * to_linear(gain); }

/**
 * @copydoc apply(const double, const double)
 */
inline float apply(float lin, float gain) { return lin * to_linear(gain); }

/**
 * @brief Apply a decibel gain to a linear signal, muting if below threshold.
 *
 * @param lin
 * @param gain
 * @param threshold [dB] Off-threshold. Gains below this value will mute the
 * input.
 * @return Amplified or attenuated signal. Zero if gain is below threshold.
 */
inline double apply_off(double lin, double gain, double threshold) {
  return lin * to_linear_off(gain, threshold);
}

/**
 * @copydoc apply_off(double, double)
 */
inline float apply(float lin, float gain, float threshold) {
  return lin * to_linear_off(gain, threshold);
}

}  // namespace xdsp::decibel

#endif  // DECIBEL_H
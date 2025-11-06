#pragma once

#include <xdsp/tuning.h>

/**
 * @brief Control-voltage conversions
 *
 */
namespace xdsp::control_voltage {

/**
 * @brief @f$ 20 \mbox{Hz} @f$ Default minimum filter frequency (approx. lower
 * threshold of human hearing)
 *
 */
constexpr double MIN_FILTER_FREQ_DEFAULT = 20.0;

/**
 * @brief Default tuning
 *
 * Tune @f$ [-5 \mbox{V}, +5 \mbox{V}] @f$ control voltage to @f$ [20
 * \mbox{Hz}, 20.48
 * \mbox{kHz}] @f$ (10 octave range)
 *
 */
const double FREQ_ZERO_VOLT_DEFAULT =
    xdsp::tuning::detune_octave(MIN_FILTER_FREQ_DEFAULT, 5);

/**
 * @brief Volt-per-octave @f$ \leftrightarrow @f$ frequency conversion class
 *
 * @tparam FloatType Floating-point type (float or double)
 */
template <typename FloatType>
class VoltPerOct {
 public:
  /**
   * @brief Construct with default tuning
   *
   */
  VoltPerOct();

  /**
   * @brief Construct with specified tuning
   *
   * @param _freq_zero_volt
   */
  explicit VoltPerOct(FloatType _freq_zero_volt);

  /**
   * @brief Default destructor
   *
   */
  ~VoltPerOct() = default;

  /**
   * @brief Tune the conversion
   *
   * @param _freq_zero_volt [Hz] Frequency at 0V control-voltage
   */
  void tune(FloatType _freq_zero_volt);

  /**
   * @brief Convert control-voltage to frequency
   *
   * @param volt [V] Control-voltage
   * @return FloatType [Hz] Frequency
   */
  FloatType to_freq(FloatType volt) const;

  /**
   * @brief Convert frequency to control-voltage
   *
   * @param freq [Hz] Frequency
   * @return FloatType [V] Control-voltage
   */
  FloatType to_volt(FloatType freq) const;

  /**
   * @brief Convert control-voltage to frequency
   *
   * @param volt [V] Control-voltage
   * @param freq_zero_volt [Hz] Desired frequency at 0V
   * @return float [Hz] Frequency
   */
  static float to_freq(float volt, float freq_zero_volt);

  /**
   * @brief Convert control-voltage to frequency
   *
   * @param volt [V] Control-voltage
   * @param freq_zero_volt [Hz] Desired frequency at 0V
   * @return double [Hz] Frequency
   */
  static double to_freq(double volt, double freq_zero_volt);

  /**
   * @brief Convert frequency to control-voltage
   *
   * @param freq [Hz] Frequency
   * @param freq_zero_volt [Hz] Desired frequency at 0V
   * @return float [V] Control-voltage
   */
  static float to_volt(float freq, float freq_zero_volt);

  /**
   * @brief Convert frequency to control-voltage
   *
   * @param freq [Hz] Frequency
   * @param freq_zero_volt [Hz] Desired frequency at 0V
   * @return double [V] Control-voltage
   */
  static double to_volt(double freq, double freq_zero_volt);

 private:
  /**
   * @brief [Hz] Conversion reference (frequency at 0V control-voltage)
   *
   */
  FloatType freq_zero_volt;
};

}  // namespace xdsp::control_voltage
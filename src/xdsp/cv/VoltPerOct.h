#pragma once

#include "../consts.h"

/**
 * @brief Control-voltage conversions
 *
 */
namespace xdsp::cv {

/**
 * @brief Default tuning
 *
 * +-5V CV / 10 octave range (20Hz to 20.48kHz)
 *
 */
const double FREQ_ZERO_VOLT_DEFAULT = consts::MIN_FILTER_FREQ * pow(2.0, 5.0);

/**
 * @brief Volt-per-octave <-> frequency conversion class
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

}  // namespace xdsp::cv
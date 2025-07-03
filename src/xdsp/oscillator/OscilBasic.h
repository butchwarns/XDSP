#pragma once

/**
 * @brief Oscillators
 *
 */
namespace xdsp::oscillator {

/**
 * @brief Naive implementation of an oscillator without any antialiasing
 *
 */
class OscBasic {
 public:
  OscBasic();
  ~OscBasic();

  /**
   * @brief Reset oscillator, initialize with new sample rate
   *
   * @param sample_rate
   */
  void reset(double sample_rate);

  /**
   * @brief Set oscillator frequency
   *
   * @param freq_hz [Hz] Frequency
   */
  void set_freq(double freq_hz);

  /**
   * @brief Process one sample of the oscillator
   *
   * @return double Next output sample
   */
  double process();

 private:
  /**
   * @brief Sample rate
   *
   */
  double sample_rate;

  /**
   * @brief Output frequency
   *
   */
  double frequency;

  /**
   * @brief Bipolar modulo counter for the oscillator core
   *
   */
  double count;

  /**
   * @brief Counter increment for current frequency
   *
   */
  double inc;
};

}  // namespace xdsp::oscillator
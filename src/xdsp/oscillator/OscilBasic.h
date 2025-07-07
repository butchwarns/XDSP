#pragma once

/**
 * @brief Oscillators
 *
 */
namespace xdsp::oscillator {

enum class OscBasicWaveform {
  SAW,
  SQUARE,
};

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
   * @brief Set oscillator base frequency
   *
   * @param freq_hz [Hz] Frequency
   */
  void set_freq(double freq_hz);

  /**
   * @brief Detune the oscillator by cents
   *
   * @param cents Detune amount in cents, relative to base frequency
   */
  void set_detune(int cents);

  /**
   * @brief Detune the oscillator by octaves
   *
   * @param octave Detune amount in octaves, relative to base frequency
   */
  void set_octave(int octave);

  /**
   * @brief Set output waveform
   *
   * @param waveform Waveform to use
   */
  void set_waveform(OscBasicWaveform waveform);

  /**
   * @brief Process one sample of the oscillator
   *
   * @return double Next output sample
   */
  double process();

 private:
  /**
   * @brief Update output frequency based on base frequency, detune, and octave.
   *
   */
  void update_frequency();

  /**
   * @brief Sample rate
   *
   */
  double sample_rate;

  /**
   * @brief Output frequency, including detune and octave
   *
   */
  double frequency;

  /**
   * @brief Oscillator base frequency
   *
   */
  double frequency_base;

  /**
   * @brief Detune amount in cents
   *
   */
  int detune;

  /**
   * @brief Detune amount in octaves
   *
   */
  int octave;

  /**
   * @brief Current output waveform
   *
   */
  OscBasicWaveform waveform;

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
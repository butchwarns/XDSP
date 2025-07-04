#ifndef TUNING_H
#define TUNING_H

#include <cmath>

/**
 * @brief Everything related to semitones, octaves, cents, MIDI, ..
 */
namespace xdsp::tuning {

/**
 * @brief Convert MIDI note number to frequency in Hz
 *
 * @param midi_note MIDI note number (0-127)
 * @return double [Hz] Frequency
 */
inline double midi_to_freq(int midi_note) {
  return 440.0 * pow(2.0, (midi_note - 69) / 12.0);
}

/**
 * @brief Convert frequency in Hz to MIDI note number
 *
 * @param frequency [Hz] Frequency to convert
 * @return int MIDI note number (0-127)
 */
inline int freq_to_midi(double frequency) {
  return static_cast<int>(round(69 + 12 * log2(frequency / 440.0)));
}

/**
 * @brief Detune a frequency by a given number of cents
 *
 * @param frequency [Hz] Base frequency to detune
 * @param cents [1] Detune amount in cents
 * @return double [Hz] Detuned frequency
 */
inline double detune_cents(double frequency, int cents) {
  return frequency * pow(2.0, cents / 1200.0);
}

/**
 * @brief Detune a frequency by a given number of octaves
 *
 * @param frequency [Hz] Base frequency to detune
 * @param octave [1] Detune amount in octaves
 * @return double [Hz] Detuned frequency
 */
inline double detune_octave(double frequency, int octave) {
  return frequency * pow(2.0, octave);
}
}  // namespace xdsp::tuning

#endif  // TUNING_H
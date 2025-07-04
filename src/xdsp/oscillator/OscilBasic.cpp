#include "OscilBasic.h"

#include <xdsp/tuning.h>

namespace xdsp::oscillator {

OscBasic::OscBasic() : detune(0), octave(0) {}
OscBasic::~OscBasic() {}

void OscBasic::reset(double sample_rate) {
  this->sample_rate = sample_rate;
  count = 0.0;
  inc = 0.0;
}

void OscBasic::set_freq(double freq) {
  frequency_base = freq;
  update_frequency();
}

void OscBasic::set_detune(int cents) {
  detune = cents;
  update_frequency();
}

void OscBasic::set_octave(int _octave) {
  octave = _octave;
  update_frequency();
}

double OscBasic::process() {
  count += inc;
  if (count >= 1.0) count -= 2.0;
  return count;
}

void OscBasic::update_frequency() {
  frequency = frequency_base;
  frequency = xdsp::tuning::detune_cents(frequency, detune);
  frequency = xdsp::tuning::detune_octave(frequency, octave);

  inc = 2.0 * frequency / sample_rate;
}

}  // namespace xdsp::oscillator
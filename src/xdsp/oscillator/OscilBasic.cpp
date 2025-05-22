#include "OscilBasic.h"

namespace xdsp::oscillator {

OscBasic::OscBasic() {}
OscBasic::~OscBasic() {}

void OscBasic::reset(double sample_rate) {
  this->sample_rate = sample_rate;
  count = 0.0;
  inc = 0.0;
}

void OscBasic::set_freq(double freq) {
  frequency = freq;
  inc = 2.0 * frequency / sample_rate;
}

double OscBasic::process() {
  count += inc;
  if (count >= 1.0) count -= 2.0;
  return count;
}

}  // namespace xdsp::oscillator
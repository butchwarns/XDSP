#pragma once

#include "../consts.h"

namespace xdsp::cv {

// Default tune to standard +-5V CV / 10 octave range
const double ZERO_VOLT_FREQ_DEFAULT = consts::MIN_FILTER_FREQ * pow(2.0, 5.0);

template <typename FloatType>
class VoltPerOct {
 public:
  VoltPerOct();
  explicit VoltPerOct(FloatType _zero_volt_freq);
  ~VoltPerOct() = default;

  void tune(FloatType _zero_volt_freq);

  FloatType to_freq(FloatType volt) const;
  FloatType to_volt(FloatType freq) const;

  static float to_freq(float volt, float zero_volt_freq);
  static double to_freq(double volt, double zero_volt_freq);
  static float to_volt(float freq, float zero_volt_freq);
  static double to_volt(double freq, double zero_volt_freq);

 private:
  FloatType zero_volt_freq;
};

}  // namespace xdsp::cv
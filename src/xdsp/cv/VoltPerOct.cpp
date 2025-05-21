#include "VoltPerOct.h"

namespace xdsp::cv {

template <typename FloatType>
VoltPerOct<FloatType>::VoltPerOct()
    : zero_volt_freq((FloatType)ZERO_VOLT_FREQ_DEFAULT) {}

template <typename FloatType>
VoltPerOct<FloatType>::VoltPerOct(FloatType _zero_volt_freq)
    : zero_volt_freq(_zero_volt_freq) {}

template <typename FloatType>
void VoltPerOct<FloatType>::tune(FloatType _zero_volt_freq) {
  zero_volt_freq = _zero_volt_freq;
}

template <>
float VoltPerOct<float>::to_freq(float volt) const {
  return zero_volt_freq * powf(2.0f, volt);
}

template <>
double VoltPerOct<double>::to_freq(double volt) const {
  return zero_volt_freq * pow(2.0, volt);
}

template <>
float VoltPerOct<float>::to_volt(float freq) const {
  return log2f(freq / zero_volt_freq);
}

template <>
double VoltPerOct<double>::to_volt(double freq) const {
  return log2(freq / zero_volt_freq);
}

template <>
float VoltPerOct<float>::to_freq(float volt, float zero_volt_freq) {
  return zero_volt_freq * powf(2.0f, volt);
}

template <>
double VoltPerOct<double>::to_freq(double volt, double zero_volt_freq) {
  return zero_volt_freq * pow(2.0, volt);
}

template <>
float VoltPerOct<float>::to_volt(float freq, float zero_volt_freq) {
  return log2f(freq / zero_volt_freq);
}

template <>
double VoltPerOct<double>::to_volt(double freq, double zero_volt_freq) {
  return log2(freq / zero_volt_freq);
}

template class VoltPerOct<float>;
template class VoltPerOct<double>;

}  // namespace xdsp::cv
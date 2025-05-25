#include "VoltPerOct.h"

namespace xdsp::cv {

template <typename FloatType>
VoltPerOct<FloatType>::VoltPerOct()
    : freq_zero_volt((FloatType)FREQ_ZERO_VOLT_DEFAULT) {}

template <typename FloatType>
VoltPerOct<FloatType>::VoltPerOct(FloatType _freq_zero_volt)
    : freq_zero_volt(_freq_zero_volt) {}

template <typename FloatType>
void VoltPerOct<FloatType>::tune(FloatType _freq_zero_volt) {
  freq_zero_volt = _freq_zero_volt;
}

template <>
float VoltPerOct<float>::to_freq(float volt) const {
  return freq_zero_volt * powf(2.0f, volt);
}

template <>
double VoltPerOct<double>::to_freq(double volt) const {
  return freq_zero_volt * pow(2.0, volt);
}

template <>
float VoltPerOct<float>::to_volt(float freq) const {
  return log2f(freq / freq_zero_volt);
}

template <>
double VoltPerOct<double>::to_volt(double freq) const {
  return log2(freq / freq_zero_volt);
}

template <>
float VoltPerOct<float>::to_freq(float volt, float freq_zero_volt) {
  return freq_zero_volt * powf(2.0f, volt);
}

template <>
double VoltPerOct<double>::to_freq(double volt, double freq_zero_volt) {
  return freq_zero_volt * pow(2.0, volt);
}

template <>
float VoltPerOct<float>::to_volt(float freq, float freq_zero_volt) {
  return log2f(freq / freq_zero_volt);
}

template <>
double VoltPerOct<double>::to_volt(double freq, double freq_zero_volt) {
  return log2(freq / freq_zero_volt);
}

template class VoltPerOct<float>;
template class VoltPerOct<double>;

}  // namespace xdsp::cv
#include <gtest/gtest.h>
#include <xdsp/cv/VoltPerOct.h>

using namespace xdsp;

#define FREQ_ZERO_VOLT 110.0

void assert_values_correct(double freq, double volt, double zero_volt_freq) {
  EXPECT_FLOAT_EQ(freq, zero_volt_freq * pow(2.0, volt));
  EXPECT_FLOAT_EQ(volt, log2(freq / zero_volt_freq));
}

TEST(CV, VoltPerOct_conversions_static) {
  for (int i = 0; i < 5; ++i) {
    // Reference values (one octave apart)
    const auto volt0 = (double)i;
    const auto volt1 = (double)i + 1.0;
    const auto freq0 = FREQ_ZERO_VOLT * pow(2.0, (double)i);
    const auto freq1 = freq0 * 2;

    // Static conversion Volt to Hz
    double freq0_cv =
        xdsp::cv::VoltPerOct<double>::to_freq(volt0, FREQ_ZERO_VOLT);
    double freq1_cv =
        xdsp::cv::VoltPerOct<double>::to_freq(volt1, FREQ_ZERO_VOLT);
    assert_values_correct(freq0_cv, volt0, FREQ_ZERO_VOLT);
    assert_values_correct(freq1_cv, volt1, FREQ_ZERO_VOLT);

    // Static conversion Hz to Volt
    double volt0_cv =
        xdsp::cv::VoltPerOct<double>::to_volt(freq0, FREQ_ZERO_VOLT);
    double volt1_cv =
        xdsp::cv::VoltPerOct<double>::to_volt(freq1, FREQ_ZERO_VOLT);
    assert_values_correct(freq0, volt0_cv, FREQ_ZERO_VOLT);
    assert_values_correct(freq1, volt1_cv, FREQ_ZERO_VOLT);
  }
}

TEST(CV, VoltPerOct_conversions) {
  auto volt_per_oct = xdsp::cv::VoltPerOct<double>(FREQ_ZERO_VOLT);

  for (int i = 0; i < 5; ++i) {
    // Reference values (one octave apart)
    const auto volt0 = (double)i;
    const auto volt1 = (double)i + 1.0;
    const auto freq0 = FREQ_ZERO_VOLT * pow(2.0, (double)i);
    const auto freq1 = freq0 * 2;

    // Conversion Volt to Hz
    double freq0_cv = volt_per_oct.to_freq(volt0, FREQ_ZERO_VOLT);
    double freq1_cv = volt_per_oct.to_freq(volt1, FREQ_ZERO_VOLT);
    assert_values_correct(freq0_cv, volt0, FREQ_ZERO_VOLT);
    assert_values_correct(freq1_cv, volt1, FREQ_ZERO_VOLT);

    // Conversion Hz to Volt
    double volt0_cv = volt_per_oct.to_volt(freq0, FREQ_ZERO_VOLT);
    double volt1_cv = volt_per_oct.to_volt(freq1, FREQ_ZERO_VOLT);
    assert_values_correct(freq0, volt0_cv, FREQ_ZERO_VOLT);
    assert_values_correct(freq1, volt1_cv, FREQ_ZERO_VOLT);
  }
}
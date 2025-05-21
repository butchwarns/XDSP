#include <gtest/gtest.h>
#include <xdsp/cv/VoltPerOct.h>

using namespace xdsp;

void assert_values_correct(double freq, double volt, double freq_zero_volt) {
  EXPECT_FLOAT_EQ(freq, freq_zero_volt * pow(2.0, volt));
  EXPECT_FLOAT_EQ(volt, log2(freq / freq_zero_volt));
}

class CVTest : public ::testing::TestWithParam<double> {
 protected:
  void SetUp() override { freq_zero_volt_ = GetParam(); }
  double freq_zero_volt_;
};

TEST_P(CVTest, VoltPerOct_conversions_static) {
  for (int i = 0; i < 5; ++i) {
    // Reference values (one octave apart)
    const auto volt0 = (double)i;
    const auto volt1 = (double)i + 1.0;
    const auto freq0 = freq_zero_volt_ * pow(2.0, (double)i);
    const auto freq1 = freq0 * 2;

    // Static conversion Volt to Hz
    double freq0_cv =
        xdsp::cv::VoltPerOct<double>::to_freq(volt0, freq_zero_volt_);
    double freq1_cv =
        xdsp::cv::VoltPerOct<double>::to_freq(volt1, freq_zero_volt_);
    assert_values_correct(freq0_cv, volt0, freq_zero_volt_);
    assert_values_correct(freq1_cv, volt1, freq_zero_volt_);

    // Static conversion Hz to Volt
    double volt0_cv =
        xdsp::cv::VoltPerOct<double>::to_volt(freq0, freq_zero_volt_);
    double volt1_cv =
        xdsp::cv::VoltPerOct<double>::to_volt(freq1, freq_zero_volt_);
    assert_values_correct(freq0, volt0_cv, freq_zero_volt_);
    assert_values_correct(freq1, volt1_cv, freq_zero_volt_);
  }
}

TEST_P(CVTest, VoltPerOct_conversions) {
  auto volt_per_oct = xdsp::cv::VoltPerOct<double>(freq_zero_volt_);

  for (int i = 0; i < 5; ++i) {
    // Reference values (one octave apart)
    const auto volt0 = (double)i;
    const auto volt1 = (double)i + 1.0;
    const auto freq0 = freq_zero_volt_ * pow(2.0, (double)i);
    const auto freq1 = freq0 * 2;

    // Conversion Volt to Hz
    double freq0_cv = volt_per_oct.to_freq(volt0, freq_zero_volt_);
    double freq1_cv = volt_per_oct.to_freq(volt1, freq_zero_volt_);
    assert_values_correct(freq0_cv, volt0, freq_zero_volt_);
    assert_values_correct(freq1_cv, volt1, freq_zero_volt_);

    // Conversion Hz to Volt
    double volt0_cv = volt_per_oct.to_volt(freq0, freq_zero_volt_);
    double volt1_cv = volt_per_oct.to_volt(freq1, freq_zero_volt_);
    assert_values_correct(freq0, volt0_cv, freq_zero_volt_);
    assert_values_correct(freq1, volt1_cv, freq_zero_volt_);
  }
}

std::vector<double> get_freqs_zero_volt_() {
  std::vector<double> freqs_zero_volt_;
  for (int i = 0; i < 5; i += 6) {
    const auto freq_ =
        0.2 + 2.0 * (double)i;  // Arbitrary values in a sensible range
    freqs_zero_volt_.push_back(freq_);
  }

  return freqs_zero_volt_;
}
std::vector<double> freqs_zero_volt_ = get_freqs_zero_volt_();

INSTANTIATE_TEST_SUITE_P(CVTestInstance, CVTest,
                         ::testing::ValuesIn(freqs_zero_volt_));

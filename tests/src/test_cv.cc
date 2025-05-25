#include <gtest/gtest.h>
#include <xdsp/cv/VoltPerOct.h>

using namespace xdsp;

template <typename FloatType>
void assert_values_correct(FloatType freq, FloatType volt,
                           FloatType freq_zero_volt);

template <>
void assert_values_correct(float freq, float volt, float freq_zero_volt) {
  EXPECT_FLOAT_EQ(freq, freq_zero_volt * powf(2.0f, volt));
  EXPECT_FLOAT_EQ(volt, log2f(freq / freq_zero_volt));
}

template <>
void assert_values_correct(double freq, double volt, double freq_zero_volt) {
  EXPECT_DOUBLE_EQ(freq, freq_zero_volt * pow(2.0, volt));
  EXPECT_DOUBLE_EQ(volt, log2(freq / freq_zero_volt));
}

class CVTest : public ::testing::TestWithParam<double> {
 protected:
  void SetUp() override { freq_zero_volt_ = GetParam(); }
  double freq_zero_volt_;
};

TEST_P(CVTest, VoltPerOct_conversions_static_double) {
  for (int i = 0; i < 5; ++i) {
    // Reference values (one octave apart)
    const auto volt0 = (double)i;
    const auto volt1 = (double)i + 1.0;
    const auto freq0 = freq_zero_volt_ * pow(2.0, (double)i);
    const auto freq1 = freq0 * 2.0;

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

TEST_P(CVTest, VoltPerOct_conversions_static_float) {
  const float freq_zero_volt_f = static_cast<float>(freq_zero_volt_);

  for (int i = 0; i < 5; ++i) {
    // Reference values (one octave apart)
    const auto volt0 = (float)i;
    const auto volt1 = (float)i + 1.0f;
    const auto freq0 = freq_zero_volt_f * powf(2.0f, (float)i);
    const auto freq1 = freq0 * 2.0f;

    // Static conversion Volt to Hz
    float freq0_cv =
        xdsp::cv::VoltPerOct<float>::to_freq(volt0, freq_zero_volt_f);
    float freq1_cv =
        xdsp::cv::VoltPerOct<float>::to_freq(volt1, freq_zero_volt_f);
    assert_values_correct(freq0_cv, volt0, freq_zero_volt_f);
    assert_values_correct(freq1_cv, volt1, freq_zero_volt_f);

    // Static conversion Hz to Volt
    float volt0_cv =
        xdsp::cv::VoltPerOct<float>::to_volt(freq0, freq_zero_volt_f);
    float volt1_cv =
        xdsp::cv::VoltPerOct<float>::to_volt(freq1, freq_zero_volt_f);
    assert_values_correct(freq0, volt0_cv, freq_zero_volt_f);
    assert_values_correct(freq1, volt1_cv, freq_zero_volt_f);
  }
}

TEST_P(CVTest, VoltPerOct_conversions_double) {
  auto volt_per_oct = xdsp::cv::VoltPerOct<double>(freq_zero_volt_);

  for (int i = 0; i < 5; ++i) {
    // Reference values (one octave apart)
    const auto volt0 = (double)i;
    const auto volt1 = (double)i + 1.0;
    const auto freq0 = freq_zero_volt_ * pow(2.0, (double)i);
    const auto freq1 = freq0 * 2.0;

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

TEST_P(CVTest, VoltPerOct_conversions_float) {
  const float freq_zero_volt_f = static_cast<float>(freq_zero_volt_);

  auto volt_per_oct = xdsp::cv::VoltPerOct<float>(freq_zero_volt_f);

  for (int i = 0; i < 5; ++i) {
    // Reference values (one octave apart)
    const auto volt0 = (float)i;
    const auto volt1 = (float)i + 1.0f;
    const auto freq0 = freq_zero_volt_f * powf(2.0f, (float)i);
    const auto freq1 = freq0 * 2.0f;

    // Conversion Volt to Hz
    float freq0_cv = volt_per_oct.to_freq(volt0, freq_zero_volt_f);
    float freq1_cv = volt_per_oct.to_freq(volt1, freq_zero_volt_f);
    assert_values_correct(freq0_cv, volt0, freq_zero_volt_f);
    assert_values_correct(freq1_cv, volt1, freq_zero_volt_f);

    // Conversion Hz to Volt
    float volt0_cv = volt_per_oct.to_volt(freq0, freq_zero_volt_f);
    float volt1_cv = volt_per_oct.to_volt(freq1, freq_zero_volt_f);
    assert_values_correct(freq0, volt0_cv, freq_zero_volt_f);
    assert_values_correct(freq1, volt1_cv, freq_zero_volt_f);
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

#include <gtest/gtest.h>
#include <xdsp/decibel.h>

using namespace xdsp;

class DecibelTest : public ::testing::TestWithParam<double> {
 protected:
  void SetUp() override { gain_ = GetParam(); }
  double gain_;
  double threshold_ = -68.0;
};

TEST_P(DecibelTest, AmpAttConv) {
  /* Tests conversions, amplification, and attenuation. */

  double y = decibel::apply(decibel::DB_REF, gain_);
  EXPECT_FLOAT_EQ(decibel::to_db(y), gain_);
}

TEST_P(DecibelTest, OffThreshold) {
  /* Tests gains below off-threshold mute. */

  double y = decibel::apply_off(decibel::DB_REF, gain_, threshold_);
  if (gain_ <= threshold_) {
    EXPECT_FLOAT_EQ(y, 0.0);
  } else {
    EXPECT_FLOAT_EQ(decibel::to_db(y), gain_);
  }
}

std::vector<double> get_gains_() {
  std::vector<double> gains_;
  for (int i = 0; i <= 100; i += 6) {
    const auto gain_ = (double)i;
    gains_.push_back(gain_);
    gains_.push_back(-gain_);
  }

  return gains_;
}
std::vector<double> gains_ = get_gains_();

INSTANTIATE_TEST_SUITE_P(DecibelTestInstance, DecibelTest,
                         ::testing::ValuesIn(gains_));

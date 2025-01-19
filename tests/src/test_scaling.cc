#include <gtest/gtest.h>
#include <xdsp/scaling.h>

using namespace xdsp;

constexpr double UNIPOLAR_LO = 0.0;
constexpr double UNIPOLAR_MID = 0.5;
constexpr double UNIPOLAR_HI = 1.0;

constexpr double BIPOLAR_LO = -1;
constexpr double BIPOLAR_MID = 0.0;
constexpr double BIPOLAR_HI = 1.0;

TEST(Scaling, LerpBipolar) {
  const double in_lo = -1.0;
  const double in_mid = 0.0;
  const double in_hi = 1.0;

  const double out_lo = 0.0;
  const double out_mid = 0.5;
  const double out_hi = 1.0;

  EXPECT_FLOAT_EQ(scaling::lerp_bipolar(in_lo, out_lo, out_hi), out_lo);
  EXPECT_FLOAT_EQ(scaling::lerp_bipolar(in_mid, out_lo, out_hi), out_mid);
  EXPECT_FLOAT_EQ(scaling::lerp_bipolar(in_hi, out_lo, out_hi), out_hi);
}

TEST(Scaling, LerpUnipolar) {
  const double in_lo = 0.0;
  const double in_mid = 0.5;
  const double in_hi = 1.0;

  const double out_lo = -10;
  const double out_mid = 0.0;
  const double out_hi = 10.0;

  EXPECT_FLOAT_EQ(scaling::lerp_unipolar(in_lo, out_lo, out_hi), out_lo);
  EXPECT_FLOAT_EQ(scaling::lerp_unipolar(in_mid, out_lo, out_hi), out_mid);
  EXPECT_FLOAT_EQ(scaling::lerp_unipolar(in_hi, out_lo, out_hi), out_hi);
}

TEST(Scaling, Lerp) {
  const double in_lo = 0.0;
  const double in_mid = 0.5;
  const double in_hi = 1.0;

  const double out_lo = -10;
  const double out_mid = 0.0;
  const double out_hi = 10.0;

  EXPECT_FLOAT_EQ(scaling::lerp(in_lo, in_lo, in_hi, out_lo, out_hi), out_lo);
  EXPECT_FLOAT_EQ(scaling::lerp(in_mid, in_lo, in_hi, out_lo, out_hi), out_mid);
  EXPECT_FLOAT_EQ(scaling::lerp(in_hi, in_lo, in_hi, out_lo, out_hi), out_hi);
}

TEST(Scaling, NormalizeUnipolar) {
  const double in_lo = 10.0;
  const double in_mid = 5.0;
  const double in_hi = 0.0;

  EXPECT_FLOAT_EQ(scaling::normalize_unipolar(in_lo, in_lo, in_hi),
                  UNIPOLAR_LO);
  EXPECT_FLOAT_EQ(scaling::normalize_unipolar(in_mid, in_lo, in_hi),
                  UNIPOLAR_MID);
  EXPECT_FLOAT_EQ(scaling::normalize_unipolar(in_hi, in_lo, in_hi),
                  UNIPOLAR_HI);
}

TEST(Scaling, NormalizeBipolar) {
  const double in_lo = 10.0;
  const double in_mid = -5.0;
  const double in_hi = -20.0;

  EXPECT_FLOAT_EQ(scaling::normalize_bipolar(in_lo, in_lo, in_hi), BIPOLAR_LO);
  EXPECT_FLOAT_EQ(scaling::normalize_bipolar(in_mid, in_lo, in_hi),
                  BIPOLAR_MID);
  EXPECT_FLOAT_EQ(scaling::normalize_bipolar(in_hi, in_lo, in_hi), BIPOLAR_HI);
}

TEST(Scaling, UnipolarToBipolar) {
  EXPECT_FLOAT_EQ(scaling::to_bipolar(UNIPOLAR_LO), BIPOLAR_LO);
  EXPECT_FLOAT_EQ(scaling::to_bipolar(UNIPOLAR_MID), BIPOLAR_MID);
  EXPECT_FLOAT_EQ(scaling::to_bipolar(UNIPOLAR_HI), BIPOLAR_HI);
}

TEST(Scaling, BipolarToUnipolar) {
  EXPECT_FLOAT_EQ(scaling::to_unipolar(BIPOLAR_LO), UNIPOLAR_LO);
  EXPECT_FLOAT_EQ(scaling::to_unipolar(BIPOLAR_MID), UNIPOLAR_MID);
  EXPECT_FLOAT_EQ(scaling::to_unipolar(BIPOLAR_HI), UNIPOLAR_HI);
}
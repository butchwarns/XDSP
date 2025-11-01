#include <gtest/gtest.h>
#include <xdsp/MidSide.h>

using namespace xdsp;

#define BUFFER_SIZE 2048

#define TWO_PI (M_PI * 2.0)

TEST(Smoothing, MidSideCorrelated) {
  double left[BUFFER_SIZE];
  double right[BUFFER_SIZE];

  for (int n = 0; n < BUFFER_SIZE; ++n) {
    const double n_norm = (double)n / (double)BUFFER_SIZE;

    left[n] = std::sin(n_norm * 2.0 * M_PI);
    right[n] = std::sin(n_norm * 2.0 * M_PI);
  }

  for (int n = 0; n < BUFFER_SIZE; ++n) {
    double l = left[n];
    double r = right[n];
    double mid = 0.0;
    double side = 0.0;

    MidSide<double>::encode(l, r, mid, side);
    EXPECT_FLOAT_EQ(l, mid / M_SQRT2);
    EXPECT_FLOAT_EQ(side, 0.0);
  }
}
#include <gtest/gtest.h>
#include <xdsp/smoothing/SmoothLin.h>

using namespace xdsp;

#define SAMPLE_RATE 48000.0
#define BUFFER_SIZE 2048

#define TIME_S 0.01  // 10 ms

// Arbitrary small threshold
#define DELTA_THRESHOLD (1.0 / SAMPLE_RATE) * 1.0001

TEST(Smoothing, SmoothLinDouble) {
  smoothing::SmoothLin<double> smoother;

  smoother.reset(SAMPLE_RATE);
  smoother.set_time(1.0);

  smoother.set_target(1.0);

  double out_prev = 0.0;
  for (int n = 0; n < BUFFER_SIZE; ++n) {
    const auto out = smoother.next();

    const auto delta = out - out_prev;

    EXPECT_TRUE(delta >= 0.0);
    EXPECT_TRUE(delta <= DELTA_THRESHOLD);

    out_prev = out;
  }
}

TEST(Smoothing, SmoothLinFloat) {
  smoothing::SmoothLin<float> smoother;

  smoother.reset((float)SAMPLE_RATE);
  smoother.set_time(1.0f);

  smoother.set_target(1.0f);

  double out_prev = 0.0f;
  for (int n = 0; n < BUFFER_SIZE; ++n) {
    const auto out = smoother.next();

    const auto delta = out - out_prev;

    EXPECT_TRUE(delta >= 0.0f);
    EXPECT_TRUE(delta <= (float)DELTA_THRESHOLD)
        << "DELTA: " << delta << " THRESH: " << (float)DELTA_THRESHOLD;

    out_prev = out;
  }
}
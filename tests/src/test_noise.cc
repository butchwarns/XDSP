#include <gtest/gtest.h>
#include <xdsp/noise/LinearCongruentialGenerator.h>

#include <cmath>

using namespace xdsp;

#define NUM_SAMPLES 48000 * 10

TEST(Noise, LinearCongruentialGenerator) {
  noise::LinearCongruentialGenerator noise(1234567);
  double sum = 0.0;

  for (int i = 0; i < NUM_SAMPLES; ++i) {
    auto x = noise.process();
    sum += x;

    EXPECT_TRUE(x >= -1.0);
    EXPECT_TRUE(x <= 1.0);
  }

  // Check average for sanity
  // (not very precise, as generator has small offset)
  const double avg = sum / NUM_SAMPLES;
  EXPECT_TRUE(abs(avg) < 0.1257);  // (measured)
}

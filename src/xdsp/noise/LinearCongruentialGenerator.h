#pragma once

#include <cstdint>

/**
 * @brief Noise sources
 *
 */
namespace xdsp::noise {

/**
 * @brief White noise soruce using linear congruential generator (LCG)
 *
 * As seen in:
 * https://github.com/hollance/synth-recipes/blob/main/recipes/white-noise.markdown
 */
class LinearCongruentialGenerator {
 public:
  /**
   * @brief Construct new seeded source
   *
   * @param seed Seed for pseudo-random number generation
   */
  explicit LinearCongruentialGenerator(uint32_t seed = 1234567);

  /**
   * @brief Generate one sample of white noise
   *
   * @return double Noise sample in range [-1.0, 1.0]
   */
  double process();

 private:
  /**
   * @brief Internal state of the LCG
   *
   */
  uint32_t state;
};

}  // namespace xdsp::noise
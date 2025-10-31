#ifndef SMOOTH_LIN
#define SMOOTH_LIN

namespace xdsp::smoothing {

template <typename FloatType>
class SmoothLin {
 public:
  SmoothLin();
  ~SmoothLin() = default;

  /**
   * @brief Reset state, initialize with new sample rate
   *
   * @param _sample_rate [samples/s] Sample rate
   */
  void reset(FloatType _sample_rate);

  /**
   * @brief Set time constant
   *
   * Time it takes output to reach target
   *
   * @param time_s [s] Time constant
   */
  void set_time(FloatType time_s);

  /**
   * @brief Set target output value
   *
   * @param _target [1] Target output value
   */
  void set_target(FloatType _target);

  /**
   * @brief Calculate next output sample
   *
   * Update internal state and calculate next output sample
   *
   * @return FloatType
   */
  FloatType next();

 private:
  FloatType sample_rate;
  FloatType time_samples;
  FloatType target;
  FloatType state;
  FloatType delta;
};

}  // namespace xdsp::smoothing

#endif  // SMOOTH_LIN
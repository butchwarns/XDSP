#include "SmoothLin.h"

namespace xdsp::smoothing {

template <typename FloatType>
SmoothLin<FloatType>::SmoothLin()
    : sample_rate((FloatType)0.0),
      time_samples((FloatType)0.0),
      target((FloatType)0.0),
      state((FloatType)0.0),
      delta((FloatType)0.0) {}

template <typename FloatType>
void SmoothLin<FloatType>::reset(FloatType _sample_rate) {
  state = (FloatType)0.0;
  delta = (FloatType)0.0;
  target = (FloatType)0.0;
  time_samples = (FloatType)0.0;
  sample_rate = _sample_rate;
}

template <typename FloatType>
void SmoothLin<FloatType>::set_time(FloatType time_s) {
  time_samples = time_s * sample_rate;
}

template <typename FloatType>
void SmoothLin<FloatType>::set_target(FloatType _target) {
  target = _target;

  delta = (target - state) / time_samples;
}

template <typename FloatType>
FloatType SmoothLin<FloatType>::next() {
  state += delta;

  const bool is_rising = delta > 0.0;
  const bool is_falling = delta < 0.0;
  const bool is_over_target = state >= target;
  const bool is_under_target = state <= target;

  const bool is_at_target =
      (is_rising && is_over_target) || (is_falling && is_under_target);

  if (is_at_target) {
    delta = (FloatType)0.0;
    state = target;
  }

  return state;
}

template class SmoothLin<float>;
template class SmoothLin<double>;

}  // namespace xdsp::smoothing
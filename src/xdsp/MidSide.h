#pragma once

#include <xdsp/constants.h>

#include <cmath>

namespace xdsp {

template <typename FloatType>
class MidSide {
 public:
  MidSide() = delete;
  MidSide(const MidSide&) = delete;
  MidSide& operator=(const MidSide&) = delete;
  ~MidSide() = delete;

  static inline void encode(FloatType left, FloatType right, FloatType& mid,
                            FloatType& side) {
    mid = (left + right) / constants::SQRT_2;
    side = (left - right) / constants::SQRT_2;
  }

  static inline void decode(FloatType& left, FloatType& right, FloatType mid,
                            FloatType side) {
    left = (mid + side) / constants::SQRT_2;
    right = (mid - side) / constants::SQRT_2;
  }
};

}  // namespace xdsp
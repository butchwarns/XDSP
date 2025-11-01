#pragma once

#include <xdsp/consts.h>

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
    mid = (left + right) / consts::SQRT_2;
    side = (left - right) / consts::SQRT_2;
  }

  static inline void decode(FloatType& left, FloatType& right, FloatType mid,
                            FloatType side) {
    left = (mid + side) / consts::SQRT_2;
    right = (mid - side) / consts::SQRT_2;
  }
};

}  // namespace xdsp
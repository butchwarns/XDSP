#pragma once

#include <xdsp/denormals.h>
#include <xdsp/scaling.h>

namespace xdsp::envelope {

enum class AdsrState {
  IDLE,
  ATTACK,
  DECAY,
  SUSTAIN,
  RELEASE,
};

class Adsr {
 public:
  Adsr() = default;
  ~Adsr() = default;

  inline void reset(double _sample_rate) {
    sample_rate = _sample_rate;

    counter = 0.0;
    delta = 0.0;
    out_prev = 0.0;
  }

  inline void set_attack(double attack_s) { attack = attack_s; }
  inline void set_decay(double decay_s) { decay = decay_s; }
  inline void set_sustain(double _sustain) { sustain = _sustain; }
  inline void set_release(double release_s) { release = release_s; }

  inline void set_gate(bool _gate) { gate = _gate; }

  inline double process_volt() {
    double output{0.0};
    double counter_inv{0.0};

    switch (state) {
      case AdsrState::IDLE:
        output = 0.0;
        break;

      case AdsrState::ATTACK:
        counter += delta;

        // ATTACK "aims higher" to make the curve more linear.
        // Circuit power is 12V (as given by the Eurorack power specs),
        // envelope output peaks at 8 V.
        output = xdsp::scaling::skew(counter, 1.8);
        output = xdsp::scaling::lerp_unipolar(output, segment_start, VOLT_PSU);
        break;

      case AdsrState::DECAY:
        counter += delta;
        // Skew inverted counter for correct shape of decreasing segment
        counter_inv = 1.0 - counter;
        counter_inv = xdsp::scaling::skew(counter_inv, 0.2);
        counter_inv = 1.0 - counter_inv;
        output = xdsp::scaling::lerp_unipolar(counter_inv, VOLT_OUT_PEAK,
                                              sustain * VOLT_OUT_PEAK);
        break;

      case AdsrState::SUSTAIN:
        output = sustain * VOLT_OUT_PEAK;
        break;

      case AdsrState::RELEASE:
        counter += delta;
        // Skew inverted counter for correct shape of decreasing segment
        counter_inv = 1.0 - counter;
        counter_inv = xdsp::scaling::skew(counter_inv, 0.2);
        counter_inv = 1.0 - counter_inv;
        output = xdsp::scaling::lerp_unipolar(counter_inv, segment_start, 0.0);
        break;
    }

    transition_state();
    out_prev = output;

    return output;  // Return output in [0.0, 8.0] V
  }

  inline double process() {
    double output = process_volt();
    output /= VOLT_OUT_PEAK;  // Normalize to [0.0, 1.0]
    xdsp::denormals::flush(&output);

    return output;
  }

 private:
  double sample_rate{48000.0};

  // Default Parameters
  double attack{0.25};  // [s]
  double decay{0.5};    // [s]
  double sustain{0.4};  // [1]
  double release{1.5};  // [s]

  const double VOLT_OUT_PEAK{8.0};
  const double VOLT_PSU{12.0};
  const double VOLT_MARGIN{0.00001};

  AdsrState state{AdsrState::IDLE};
  bool gate{false};

  double out_prev{0.0};
  double time{0.0};
  double segment_start{0.0};
  double counter{0.0};
  double delta{0.0};

  inline void update_delta() {
    // In ATTACK, adjust time to compensate the curve "aiming higher"
    if (state == AdsrState::ATTACK) {
      time = VOLT_PSU / VOLT_OUT_PEAK * time;
    }

    delta = 1.0 / (time * sample_rate);
  }

  inline void transition_state() {
    switch (state) {
      case AdsrState::IDLE:
        if (gate) {
          state = AdsrState::ATTACK;
          time = attack;
          update_delta();
          counter = 0.0;
          segment_start = 0.0;
        }
        break;

      case AdsrState::ATTACK:
        if (!gate) {
          state = AdsrState::RELEASE;
          time = release;
          update_delta();
          counter = 0.0;
          segment_start = out_prev;
        } else if (out_prev >= (VOLT_OUT_PEAK - VOLT_MARGIN)) {
          state = AdsrState::DECAY;
          time = decay;
          update_delta();
          counter = 0.0;
        }
        break;

      case AdsrState::DECAY:
        if (!gate) {
          state = AdsrState::RELEASE;
          time = release;
          update_delta();
          counter = 0.0;
          segment_start = out_prev;
        } else if (out_prev <= (sustain * VOLT_OUT_PEAK + VOLT_MARGIN)) {
          state = AdsrState::SUSTAIN;
        }
        break;

      case AdsrState::SUSTAIN:
        if (!gate) {
          state = AdsrState::RELEASE;
          time = release;
          update_delta();
          counter = 0.0;
          segment_start = out_prev;
        }
        break;

      case AdsrState::RELEASE:
        if (gate) {
          state = AdsrState::ATTACK;
          time = attack;
          update_delta();
          counter = 0.0;
          segment_start = out_prev;
        } else if (out_prev <= (0.0 + VOLT_MARGIN)) {
          state = AdsrState::IDLE;
        }
        break;
    }
  }
};

}  // namespace xdsp::envelope
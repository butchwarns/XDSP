#pragma once

namespace xdsp::envelope {

enum class AdsrState {
  IDLE,
  ATTACK,
  DECAY,
  SUSTAIN,
  RELEASE,
};

struct AdsrParams {
  AdsrParams() {}

  AdsrParams &operator=(const AdsrParams &parameters) {
    if (this == &parameters) {
      return *this;
    } else {
      attack = parameters.attack;
      decay = parameters.decay;
      sustain = parameters.sustain;
      release = parameters.release;

      return *this;
    }
  }

  // Default Parameters
  double attack{0.25};  // [s]
  double decay{0.5};    // [s]
  double sustain{0.4};  // [1]
  double release{1.5};  // [s]
};

class Adsr {
 public:
  Adsr();
  ~Adsr();

  void reset(double _sampleRate);

  AdsrParams get_params();
  void set_params(const AdsrParams &parameters);

  void set_gate(bool _gate);
  double process();

  double sample_rate{48000.0};

  AdsrParams parameters;

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

  void update_delta();
  void transition_state();
};

}  // namespace xdsp::envelope
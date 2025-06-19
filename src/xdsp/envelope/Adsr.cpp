#include "Adsr.h"

#include <xdsp/scaling.h>

namespace xdsp::envelope {

Adsr::Adsr() {}
Adsr::~Adsr() {}

void Adsr::reset(double _sample_rate) {
  sample_rate = _sample_rate;

  counter = 0.0;
  delta = 0.0;
  out_prev = 0.0;
}

AdsrParams Adsr::get_params() { return parameters; }

void Adsr::set_params(const AdsrParams &_parameters) {
  parameters = _parameters;
}

void Adsr::set_gate(bool _gate) { gate = _gate; }

void Adsr::update_delta() {
  // In ATTACK, adjust time to compensate the curve "aiming higher"
  if (state == AdsrState::ATTACK) {
    time = VOLT_PSU / VOLT_OUT_PEAK * time;
  }

  delta = 1.0 / (time * sample_rate);
}

void Adsr::transition_state() {
  switch (state) {
    case AdsrState::IDLE:
      if (gate) {
        state = AdsrState::ATTACK;
        time = parameters.attack;
        update_delta();
        counter = 0.0;
        segment_start = 0.0;
      }
      break;

    case AdsrState::ATTACK:
      if (!gate) {
        state = AdsrState::RELEASE;
        time = parameters.release;
        update_delta();
        counter = 0.0;
        segment_start = out_prev;
      } else if (out_prev >= (VOLT_OUT_PEAK - VOLT_MARGIN)) {
        state = AdsrState::DECAY;
        time = parameters.decay;
        update_delta();
        counter = 0.0;
      }
      break;

    case AdsrState::DECAY:
      if (!gate) {
        state = AdsrState::RELEASE;
        time = parameters.release;
        update_delta();
        counter = 0.0;
        segment_start = out_prev;
      } else if (out_prev <=
                 (parameters.sustain * VOLT_OUT_PEAK + VOLT_MARGIN)) {
        state = AdsrState::SUSTAIN;
      }
      break;

    case AdsrState::SUSTAIN:
      if (!gate) {
        state = AdsrState::RELEASE;
        time = parameters.release;
        update_delta();
        counter = 0.0;
        segment_start = out_prev;
      }
      break;

    case AdsrState::RELEASE:
      if (gate) {
        state = AdsrState::ATTACK;
        time = parameters.attack;
        update_delta();
        counter = 0.0;
        segment_start = out_prev;
      } else if (out_prev <= (0.0 + VOLT_MARGIN)) {
        state = AdsrState::IDLE;
      }
      break;
  }
}

double Adsr::process() {
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
                                            parameters.sustain * VOLT_OUT_PEAK);
      break;

    case AdsrState::SUSTAIN:
      output = parameters.sustain * VOLT_OUT_PEAK;
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

  return output;
}

}  // namespace xdsp::envelope
#include "SineOscillator.h"
#include <cmath>

namespace {
constexpr float kTwoPi = 6.28318530718f;
}

float SineOscillator::waveform(float phase) const {
	return sinf(phase * kTwoPi);
}

#include "SquareOscillator.h"

float SquareOscillator::waveform(float phase) const {
	return phase < 0.5f ? 1.0f : -1.0f;
}

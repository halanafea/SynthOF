#include "SawOscillator.h"

float SawOscillator::waveform(float phase) const {
	return (2.0f * phase) - 1.0f;
}

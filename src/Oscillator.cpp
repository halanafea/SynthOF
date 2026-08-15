#include "Oscillator.h"

float Oscillator::getNextSample(float sampleRate) {
	float sample = waveform(phase_);

	phase_ += frequency_ / sampleRate;
	if (phase_ >= 1.0f) {
		phase_ -= 1.0f; // wrap back around, avoids unbounded growth
	}

	return sample;
}

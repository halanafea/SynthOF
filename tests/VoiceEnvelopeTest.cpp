#include "Voice.h"
#include <cassert>
#include <cmath>
#include <memory>

namespace {
class ConstantOscillator final : public Oscillator {
protected:
	float waveform(float) const override { return 1.0f; }
};

bool near(float actual, float expected) {
	return std::fabs(actual - expected) < 0.00001f;
}
}

int main() {
	Voice voice(std::make_unique<ConstantOscillator>());
	constexpr float sampleRate = 1000.0f;

	assert(!voice.isActive());
	assert(near(voice.getNextSample(sampleRate), 0.0f));

	voice.noteOn(440.0f);
	assert(voice.isActive());
	assert(near(voice.getNextSample(sampleRate), 0.2f));
	assert(near(voice.getNextSample(sampleRate), 0.4f));
	assert(near(voice.getNextSample(sampleRate), 0.6f));
	assert(near(voice.getNextSample(sampleRate), 0.8f));
	assert(near(voice.getNextSample(sampleRate), 1.0f));
	assert(near(voice.getNextSample(sampleRate), 1.0f));

	voice.noteOff();
	assert(!voice.isActive());
	assert(near(voice.getNextSample(sampleRate), 0.95f));
	for (int sample = 0; sample < 18; ++sample) {
		voice.getNextSample(sampleRate);
	}
	assert(near(voice.getNextSample(sampleRate), 0.0f));
	assert(near(voice.getNextSample(sampleRate), 0.0f));

	voice.noteOn(440.0f);
	assert(near(voice.getNextSample(0.0f), 1.0f));
}

#include "Synthesizer.h"
#include <cassert>
#include <cmath>
#include <memory>

namespace {
class ConstantOscillator final : public Oscillator {
public:
	explicit ConstantOscillator(float value) : value_(value) { }

protected:
	float waveform(float) const override { return value_; }

private:
	float value_;
};

bool near(float actual, float expected) {
	return std::fabs(actual - expected) < 0.00001f;
}
}

int main() {
	Synthesizer synth;
	constexpr float sampleRate = 1000.0f;
	assert(near(synth.getNextSample(sampleRate), 0.0f));

	synth.addVoice('a', std::make_unique<ConstantOscillator>(1.0f), 440.0f);
	synth.addVoice('s', std::make_unique<ConstantOscillator>(1.0f), 493.88f);
	synth.addVoice('d', std::make_unique<ConstantOscillator>(1.0f), 523.25f);
	assert(synth.hasVoice('a') && synth.hasVoice('s') && synth.hasVoice('d'));

	synth.noteOn('a');
	assert(synth.isKeyActive('a'));
	for (int sample = 0; sample < 5; ++sample) {
		synth.getNextSample(sampleRate);
	}
	assert(near(synth.getNextSample(sampleRate), 1.0f / 3.0f));

	synth.noteOn('s');
	synth.noteOn('d');
	for (int sample = 0; sample < 5; ++sample) {
		synth.getNextSample(sampleRate);
	}
	assert(near(synth.getNextSample(sampleRate), 1.0f));

	synth.noteOff('a');
	assert(!synth.isKeyActive('a'));
	for (int sample = 0; sample < 20; ++sample) {
		synth.getNextSample(sampleRate);
	}
	assert(near(synth.getNextSample(sampleRate), 2.0f / 3.0f));

	Synthesizer limited;
	limited.addVoice('a', std::make_unique<ConstantOscillator>(4.0f), 440.0f);
	limited.noteOn('a');
	for (int sample = 0; sample < 5; ++sample) {
		limited.getNextSample(sampleRate);
	}
	assert(near(limited.getNextSample(sampleRate), 1.0f));

	const auto recent = limited.getRecentSamples();
	assert(!recent.empty());
	assert(near(recent.back(), 1.0f));
}

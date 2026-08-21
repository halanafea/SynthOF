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
	assert(near(synth.getNextSample(44100.0f), 0.0f));

	synth.addVoice('a', std::make_unique<ConstantOscillator>(1.0f), 440.0f);
	synth.addVoice('s', std::make_unique<ConstantOscillator>(1.0f), 493.88f);
	synth.addVoice('d', std::make_unique<ConstantOscillator>(1.0f), 523.25f);
	assert(synth.hasVoice('a') && synth.hasVoice('s') && synth.hasVoice('d'));

	synth.noteOn('a');
	assert(synth.isKeyActive('a'));
	assert(near(synth.getNextSample(44100.0f), 1.0f / 3.0f));

	synth.noteOn('s');
	synth.noteOn('d');
	assert(near(synth.getNextSample(44100.0f), 1.0f));

	synth.noteOff('a');
	assert(!synth.isKeyActive('a'));
	assert(near(synth.getNextSample(44100.0f), 2.0f / 3.0f));

	Synthesizer limited;
	limited.addVoice('a', std::make_unique<ConstantOscillator>(4.0f), 440.0f);
	limited.noteOn('a');
	assert(near(limited.getNextSample(44100.0f), 1.0f));

	const auto recent = limited.getRecentSamples();
	assert(!recent.empty());
	assert(near(recent.back(), 1.0f));
}

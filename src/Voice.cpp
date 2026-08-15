#include "Voice.h"

Voice::Voice(std::unique_ptr<Oscillator> oscillator)
	: oscillator_(std::move(oscillator)) {
}

void Voice::noteOn(float frequencyHz) {
	oscillator_->setFrequency(frequencyHz);
	active_ = true;
}

void Voice::noteOff() {
	active_ = false;
}

bool Voice::isActive() const {
	return active_;
}

float Voice::getNextSample(float sampleRate) {
	if (!active_) {
		return 0.0f;
	}
	return oscillator_->getNextSample(sampleRate);
}

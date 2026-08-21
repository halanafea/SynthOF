#include "Voice.h"

Voice::Voice(std::unique_ptr<Oscillator> oscillator)
	: oscillator_(std::move(oscillator)) {
}

void Voice::noteOn(float frequencyHz) {
	frequencyHz_.store(frequencyHz, std::memory_order_relaxed);
	active_.store(true, std::memory_order_release);
}

void Voice::noteOff() {
	active_.store(false, std::memory_order_release);
}

bool Voice::isActive() const {
	return active_.load(std::memory_order_acquire);
}

float Voice::getNextSample(float sampleRate) {
	if (!active_.load(std::memory_order_acquire)) {
		return 0.0f;
	}
	oscillator_->setFrequency(frequencyHz_.load(std::memory_order_relaxed));
	return oscillator_->getNextSample(sampleRate);
}

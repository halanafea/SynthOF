#include "Voice.h"
#include <algorithm>

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
	const bool active = active_.load(std::memory_order_acquire);
	if (!active && envelopeLevel_ <= 0.0f) {
		return 0.0f;
	}

	const float safeSampleRate = std::max(sampleRate, 1.0f);
	if (active) {
		envelopeLevel_ = std::min(
			1.0f, envelopeLevel_ + 1.0f / (kAttackSeconds * safeSampleRate));
	} else {
		envelopeLevel_ = std::max(
			0.0f, envelopeLevel_ - 1.0f / (kReleaseSeconds * safeSampleRate));
	}

	oscillator_->setFrequency(frequencyHz_.load(std::memory_order_relaxed));
	return oscillator_->getNextSample(safeSampleRate) * envelopeLevel_;
}

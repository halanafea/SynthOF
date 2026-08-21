#pragma once
#include "Oscillator.h"
#include <atomic>
#include <memory>

class Voice {
public:
	explicit Voice(std::unique_ptr<Oscillator> oscillator);

	void noteOn(float frequencyHz);
	void noteOff();
	bool isActive() const;
	float getNextSample(float sampleRate);

private:
	static constexpr float kAttackSeconds = 0.005f;
	static constexpr float kReleaseSeconds = 0.02f;

	std::unique_ptr<Oscillator> oscillator_; // Voice owns its oscillator
	std::atomic<float> frequencyHz_ { 0.0f };
	std::atomic<bool> active_ { false };
	float envelopeLevel_ = 0.0f; // Audio-thread-owned attack/release state
};

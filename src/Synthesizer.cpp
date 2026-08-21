#include "Synthesizer.h"

void Synthesizer::addVoice(char key, std::unique_ptr<Oscillator> oscillator, float frequencyHz) {
	auto voice = std::make_unique<Voice>(std::move(oscillator));
	voices_[key] = VoiceEntry { std::move(voice), frequencyHz };
}

void Synthesizer::noteOn(char key) {
	auto it = voices_.find(key);
	if (it != voices_.end()) {
		it->second.voice->noteOn(it->second.frequencyHz);
	}
}

void Synthesizer::noteOff(char key) {
	auto it = voices_.find(key);
	if (it != voices_.end()) {
		it->second.voice->noteOff();
	}
}

float Synthesizer::getNextSample(float sampleRate) {
	float mixed = 0.0f;
	for (auto & [key, entry] : voices_) {
		mixed += entry.voice->getNextSample(sampleRate);
	}

	// If the UI falls behind, drop visualization data rather than blocking the
	// real-time audio callback. Audio generation itself is never interrupted.
	waveformSamples_.push(mixed);

	return mixed;
}

std::vector<float> Synthesizer::getRecentSamples() const {
	float sample = 0.0f;
	while (waveformSamples_.pop(sample)) {
		recentSamples_.push_back(sample);
	}

	if (recentSamples_.size() > kRecentBufferSize) {
		recentSamples_.erase(
			recentSamples_.begin(),
			recentSamples_.end() - kRecentBufferSize);
	}
	return recentSamples_;
}

bool Synthesizer::hasVoice(char key) const {
	return voices_.find(key) != voices_.end();
}

bool Synthesizer::isKeyActive(char key) const {
	auto it = voices_.find(key);
	return it != voices_.end() && it->second.voice->isActive();
}

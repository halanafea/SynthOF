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

	recentSamples_.push_back(mixed);
	if (recentSamples_.size() > kRecentBufferSize) {
		recentSamples_.erase(recentSamples_.begin());
	}

	return mixed;
}

const std::vector<float> & Synthesizer::getRecentSamples() const {
	return recentSamples_;
}

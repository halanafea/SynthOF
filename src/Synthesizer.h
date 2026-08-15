#pragma once
#include "Voice.h"
#include <map>
#include <memory>
#include <vector>
#include <mutex>

class Synthesizer {
public:
	void addVoice(char key, std::unique_ptr<Oscillator> oscillator, float frequencyHz);
	void noteOn(char key);
	void noteOff(char key);

	float getNextSample(float sampleRate);

	// For visualization: the most recent chunk of mixed output
	//const std::vector<float> & getRecentSamples() const;
	std::vector<float> getRecentSamples() const; // now returns a snapshot copy, not a reference

	bool hasVoice(char key) const;
	bool isKeyActive(char key) const;

private:
	struct VoiceEntry {
		std::unique_ptr<Voice> voice;
		float frequencyHz;
	};

	std::map<char, VoiceEntry> voices_; // Synthesizer owns every Voice - composition
	std::vector<float> recentSamples_;
	static constexpr size_t kRecentBufferSize = 512;

	mutable std::mutex sampleMutex_;


};


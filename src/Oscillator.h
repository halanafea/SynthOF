#pragma once

class Oscillator {
public:
	virtual ~Oscillator() = default;

	void setFrequency(float frequencyHz) { frequency_ = frequencyHz; }
	float getNextSample(float sampleRate);

protected:
	// Subclasses define the actual waveform shape.
	// phase_ ranges 0.0 to 1.0 representing one full cycle.
	virtual float waveform(float phase) const = 0;

private:
	float frequency_ = 440.0f;
	float phase_ = 0.0f;
};


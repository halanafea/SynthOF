#pragma once
#include "Oscillator.h"

class SineOscillator : public Oscillator {
protected:
	float waveform(float phase) const override;
};


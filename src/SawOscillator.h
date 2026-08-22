#pragma once
#include "Oscillator.h"

class SawOscillator : public Oscillator {
protected:
	float waveform(float phase) const override;
};

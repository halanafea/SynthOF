#pragma once
#include "Oscillator.h"

class SquareOscillator : public Oscillator {
protected:
	float waveform(float phase) const override;
};

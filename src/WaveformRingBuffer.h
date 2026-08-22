#pragma once

#include <array>
#include <atomic>
#include <cstddef>

// Single-producer/single-consumer queue used to pass waveform samples from the
// audio callback to the drawing thread without locks or allocations.
class WaveformRingBuffer {
public:
	bool push(float sample) noexcept;
	bool pop(float & sample) noexcept;

private:
	static constexpr std::size_t kCapacity = 4096;
	std::array<float, kCapacity> samples_ {};
	std::atomic<std::size_t> readIndex_ { 0 };
	std::atomic<std::size_t> writeIndex_ { 0 };
};

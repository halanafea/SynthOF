#include "WaveformRingBuffer.h"

bool WaveformRingBuffer::push(float sample) noexcept {
	const std::size_t writeIndex = writeIndex_.load(std::memory_order_relaxed);
	const std::size_t nextWriteIndex = (writeIndex + 1) % kCapacity;
	if (nextWriteIndex == readIndex_.load(std::memory_order_acquire)) {
		return false;
	}

	samples_[writeIndex] = sample;
	writeIndex_.store(nextWriteIndex, std::memory_order_release);
	return true;
}

bool WaveformRingBuffer::pop(float & sample) noexcept {
	const std::size_t readIndex = readIndex_.load(std::memory_order_relaxed);
	if (readIndex == writeIndex_.load(std::memory_order_acquire)) {
		return false;
	}

	sample = samples_[readIndex];
	readIndex_.store((readIndex + 1) % kCapacity, std::memory_order_release);
	return true;
}

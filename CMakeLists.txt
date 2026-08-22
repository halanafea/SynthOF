cmake_minimum_required(VERSION 3.16)

project(SynthOFCoreTests LANGUAGES CXX)

include(CTest)

add_library(synthof_core STATIC
	src/Oscillator.cpp
	src/Synthesizer.cpp
	src/Voice.cpp
	src/WaveformRingBuffer.cpp
)
target_include_directories(synthof_core PUBLIC src)
target_compile_features(synthof_core PUBLIC cxx_std_17)

if(MSVC)
	target_compile_options(synthof_core PRIVATE /W4 /WX)
else()
	target_compile_options(synthof_core PRIVATE -Wall -Wextra -Werror -pedantic)
endif()

add_executable(voice_envelope_test tests/VoiceEnvelopeTest.cpp)
target_link_libraries(voice_envelope_test PRIVATE synthof_core)
add_test(NAME voice_envelope COMMAND voice_envelope_test)

add_executable(synthesizer_mix_test tests/SynthesizerMixTest.cpp)
target_link_libraries(synthesizer_mix_test PRIVATE synthof_core)
add_test(NAME synthesizer_mix COMMAND synthesizer_mix_test)

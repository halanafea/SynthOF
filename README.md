# SynthOF

SynthOF is Team Alligator's Project 2 openFrameworks synthesizer. It provides
three playable oscillator voices, keyboard and mouse controls, and a live
waveform display.

## Controls

| Input | Sound | Frequency |
| --- | --- | --- |
| `A` or the A button | Sine | 440 Hz |
| `S` or the S button | Square | 493.88 Hz |
| `D` or the D button | Saw | 523.25 Hz |

Hold a key or on-screen button to play its voice and release it to stop. More
than one voice can be played at the same time.

## Technical highlights

- Object-oriented oscillator hierarchy for sine, square, and saw voices
- Short attack and release envelope to reduce clicks
- Bounded multi-voice mixing
- Thread-safe note state shared between the UI and audio callback
- Non-blocking waveform sample transfer for the visualizer
- Automated framework-independent tests on Linux and Windows

## Build and test

The native application targets openFrameworks 0.12.1. Follow
[`BUILDING.md`](BUILDING.md) for Windows, macOS, and Linux instructions.

The framework-independent core tests can be run with:

```sh
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build --config Release
ctest --test-dir build --build-config Release --output-on-failure
```

See [`TESTING.md`](TESTING.md) for the manual acceptance procedure and
[`docs/TEST-EVIDENCE.md`](docs/TEST-EVIDENCE.md) for the recorded verification
results.

## Repository status

The integrated team work was merged into `master` through pull request #8.
The GitHub Actions core-test workflow passed on the resulting merge commit.

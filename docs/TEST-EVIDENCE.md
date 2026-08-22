# Test evidence

## Verified revision

- Repository: `halanafea/SynthOF`
- Branch: `master`
- Merge commit: `e4229bf05b9dfa70d3aef797416d40cb1f638f4c`
- Pull request: #8, merged 22 August 2026

## Automated verification

The framework-independent test suite was run from a clean checkout on
22 August 2026 with:

```sh
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build --config Release
ctest --test-dir build --build-config Release --output-on-failure
```

Result:

```text
Test #1: voice_envelope ........ Passed
Test #2: synthesizer_mix ....... Passed
100% tests passed, 0 tests failed out of 2
```

The GitHub Actions `Core tests` workflow also completed successfully on the
same `master` merge commit on Ubuntu and Windows.

## What the tests cover

- Attack and release envelope progression
- Voice deactivation after release
- Multi-voice mixing behavior
- Finite and bounded output samples

## Native application acceptance test

The automated suite does not validate the openFrameworks window, system audio
device, keyboard, or mouse. Before final submission, run the procedure in
[`TESTING.md`](../TESTING.md) on the submission machine and record:

- operating system and openFrameworks version;
- successful build and launch;
- audible A/S/D sine, square, and saw voices;
- keyboard and on-screen button press/release behavior;
- active-button highlighting and waveform animation;
- ten-second stability check for each voice.

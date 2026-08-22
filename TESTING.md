# Build and test

This branch completes the existing A/S/D synthesizer:

- A — sine, 440 Hz
- S — square, 493.88 Hz
- D — saw, 523.25 Hz

Platform-specific application prerequisites and build steps are documented in
[`BUILDING.md`](BUILDING.md) for Windows, macOS, and Linux.

## Manual test

1. Confirm A, S, and D are enabled.
2. Hold and release each key; verify its tone starts and stops.
3. Confirm the active button highlights and the waveform animates.
4. Repeat by clicking and holding each on-screen button.
5. Play each voice for at least ten seconds and confirm there is no crash or
   freeze.

Expected result: all three distinct sounds work through both keyboard and mouse
controls using the original Team Alligator interface.

## Automated core tests

The core tests do not require openFrameworks. From the repository root:

```text
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build --config Release
ctest --test-dir build --build-config Release --output-on-failure
```

The same test target runs on Ubuntu and Windows for every push and pull request.

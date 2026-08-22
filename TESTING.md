# Build and test

This branch completes the existing A/S/D synthesizer:

- A — sine, 440 Hz
- S — square, 493.88 Hz
- D — saw, 523.25 Hz

## Windows

1. Use openFrameworks 0.12.1 and Visual Studio with Desktop Development with
   C++.
2. Place the repository under openFrameworks `apps/myApps`.
3. Open `SynthOF.sln`.
4. Retarget the toolset if Visual Studio requests it.
5. Build with `Ctrl+Shift+B` and run with `F5`.

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

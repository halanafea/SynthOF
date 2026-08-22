# Cross-platform openFrameworks build

SynthOF targets openFrameworks 0.12.1. The application keeps the original
A/S/D controls: A plays sine, S plays square, and D plays saw.

## Prerequisites

- openFrameworks 0.12.1 for the target platform
- the compiler/toolchain listed in the openFrameworks setup guide for that
  platform
- no additional openFrameworks add-ons (`addons.make` is empty)

Place the checkout inside the openFrameworks tree so its path is:

```text
<openFrameworks>/apps/myApps/SynthOF
```

If the checkout has a different directory name or location, use the
openFrameworks Project Generator to import the repository and generate a
project in `apps/myApps` before building. Do not remove the existing `src`
files when regenerating a project.

## Windows

1. Install Visual Studio with **Desktop development with C++**, then download
   the openFrameworks 0.12.1 Visual Studio package.
2. Put this repository at `apps/myApps/SynthOF` in that openFrameworks tree.
3. Open `SynthOF.sln`. The committed solution already includes the SynthOF
   source files.
4. If Visual Studio asks to retarget the solution, select the installed
   Windows SDK and toolset.
5. Select `Release` or `Debug` and `x64`, build with `Ctrl+Shift+B`, then run
   with `F5`.

If the committed solution is incompatible with the installed openFrameworks
package, import the repository in `projectGenerator.exe`, select Visual
Studio, and update the project before reopening the solution.

## macOS

1. Install Xcode and its command-line tools, then download the openFrameworks
   0.12.1 macOS package.
2. Put this repository at `apps/myApps/SynthOF` in that openFrameworks tree.
3. Open the openFrameworks Project Generator, import the repository, select
   the Xcode/macOS target, and update the project.
4. Open the generated `SynthOF.xcodeproj`, select the `SynthOF` scheme and
   **My Mac**, then build and run with `Cmd+R`.

Grant microphone access if macOS requests it when the audio stream starts.
SynthOF produces audio output and does not record input.

## Linux

1. Download the openFrameworks 0.12.1 Linux package matching the machine
   architecture.
2. From the openFrameworks root, install its dependencies using the platform
   script documented for the distribution (for Ubuntu/Debian this is
   `scripts/linux/ubuntu/install_dependencies.sh`).
3. Put this repository at `apps/myApps/SynthOF`.
4. Open the openFrameworks Project Generator, import the repository, select
   the Linux target, and update the project. This creates the platform make
   files without changing the application sources.
5. Build and run from the repository root:

   ```sh
   make Release
   make RunRelease
   ```

Use `make` and `make Run` instead for a debug build. If audio initialization
fails, verify that the current user can access the system audio device and
that no other application has it exclusively open.

## Verification

After the application opens, follow the manual A/S/D acceptance procedure in
[`TESTING.md`](TESTING.md). The framework-independent core tests can also be
built on Windows, macOS, or Linux with CMake using the commands in that file;
those tests do not validate the openFrameworks window or audio device.

## Common issues

- **openFrameworks headers or libraries are missing:** confirm the repository
  is under the same openFrameworks tree used to generate the project, then
  update it with that tree's Project Generator.
- **A source file is missing from an IDE project:** regenerate/update the
  project and confirm every file under `src` is included.
- **The app builds but has no audible output:** check the selected system
  output device and volume, then run the manual controls test. A successful
  core CTest run alone is not evidence of audible output.

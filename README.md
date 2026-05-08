# PREAMP No. 4

A minimalist cassette-style preamp saturation plugin built with JUCE and CMake.

Inspired by the sound and character of the Tascam Porta 424 preamp and modern textures associated with artists like Mk.gee.

The long-term goal of PREAMP No. 4 is to provide a lightweight, hardware-inspired saturation plugin powered by Neural Amp Modeler (NAM) captures.

---

# Current MVP

Current signal chain:

Input → NAM (planned) → Output

Current implemented features:

* Input gain control
* Output gain control
* VST3 build
* Standalone application
* DAW-tested functionality
* CMake-based JUCE project structure

Planned features:

* NAM model loading
* Dirtier mode toggle
* Oversampling
* Anti-aliasing/downsampling
* Output protection
* Custom hardware-inspired GUI

---

# Tech Stack

* JUCE
* C++
* CMake
* Visual Studio
* Neural Amp Modeler (planned)

---

# Project Structure

```text
PreampNo4/
│
├── CMakeLists.txt
├── Source/
├── external/
│   └── JUCE/
├── Models/
└── build/
```

---

# Building

## Requirements

* CMake 3.22+
* Visual Studio 2022/2026
* JUCE

## Configure

```bash
mkdir build
cd build
cmake ..
```

## Build

```bash
cmake --build .
```

---

# Plugin Output

Built VST3:

```text
C:\Program Files\Common Files\VST3\
```

Standalone executable:

```text
build/PreampNo4_artefacts/Debug/Standalone/
```

---

# Development Philosophy

The focus of this project is:

* sound first
* minimal UI
* hardware-inspired workflow
* low friction
* intentional limitations

The MVP intentionally avoids feature bloat until the NAM integration is fully functional.

---

# Status

Current Status:

* Core JUCE plugin functioning
* Input/output DSP functioning
* GitHub repository configured
* Ready for NAM integration

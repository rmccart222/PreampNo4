# PREAMP No. 4

PREAMP No. 4 is a neural guitar preamp plugin built with JUCE and NeuralAmpModelerCore.

The plugin currently supports:

- Realtime Neural Amp Modeler (NAM) processing
- WaveNet model loading
- Input gain control
- Output gain control
- VST3 + Standalone builds
- Windows support
- JUCE/CMake workflow

## Signal Flow

Guitar/Input Signal  
→ Input Gain  
→ NAM Capture Processing  
→ Output Gain

## Dependencies

- JUCE
- NeuralAmpModelerCore

## Building

### Requirements

- Visual Studio 2022
- CMake 3.22+
- JUCE submodule
- NeuralAmpModelerCore submodule

### Clone

```bash
git clone --recursive https://github.com/rmccart222/PreampNo4.git
```

### Configure

```bash
cmake -B build
```

### Build (Release Recommended)

```bash
cd build
cmake --build . --config Release
```

## Current Status

The plugin is currently functional and processing realtime NAM captures successfully.

GUI work, model browser support, presets, and additional DSP features are planned.

## License

This project uses NeuralAmpModelerCore and JUCE.
Please refer to their respective licenses.

cmake_minimum_required(VERSION 3.22)

project(PreampNo4 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/JUCE)
add_subdirectory(external/NeuralAmpModelerCore EXCLUDE_FROM_ALL)

juce_add_plugin(PreampNo4
    COMPANY_NAME "RileyAaron"
    BUNDLE_ID "com.rileyaaron.preampno4"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE RlyA
    PLUGIN_CODE Pn04
    FORMATS VST3 Standalone
    PRODUCT_NAME "PREAMP No. 4"
    VST3_AUTO_MANIFEST TRUE
)

juce_add_binary_data(Resources
    SOURCES
        Resources/background_panel.png
        Resources/knob_body.png
        Resources/knob_indicator.png
        Resources/boost_off.png
        Resources/boost_on.png
)

target_sources(PreampNo4
    PRIVATE
        Source/PluginProcessor.cpp
        Source/PluginProcessor.h
        Source/PluginEditor.cpp
        Source/PluginEditor.h

        external/NeuralAmpModelerCore/NAM/activations.cpp
        external/NeuralAmpModelerCore/NAM/container.cpp
        external/NeuralAmpModelerCore/NAM/conv1d.cpp
        external/NeuralAmpModelerCore/NAM/convnet.cpp
        external/NeuralAmpModelerCore/NAM/get_dsp.cpp
        external/NeuralAmpModelerCore/NAM/dsp.cpp
        external/NeuralAmpModelerCore/NAM/lstm.cpp
        external/NeuralAmpModelerCore/NAM/ring_buffer.cpp
        external/NeuralAmpModelerCore/NAM/util.cpp
        external/NeuralAmpModelerCore/NAM/wavenet/a2_fast.cpp
        external/NeuralAmpModelerCore/NAM/wavenet/model.cpp
        external/NeuralAmpModelerCore/NAM/wavenet/slimmable.cpp
)

target_link_libraries(PreampNo4
    PRIVATE
        Resources
        juce::juce_audio_utils

    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

target_include_directories(PreampNo4
    PRIVATE
        external/NeuralAmpModelerCore
        external/NeuralAmpModelerCore/Dependencies/eigen
        external/NeuralAmpModelerCore/Dependencies/nlohmann
)

target_compile_definitions(PreampNo4
    PUBLIC
        JUCE_VST3_CAN_REPLACE_VST2=0
)
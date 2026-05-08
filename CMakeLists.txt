cmake_minimum_required(VERSION 3.22)

project(PreampNo4 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

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

target_sources(PreampNo4
    PRIVATE
        Source/PluginProcessor.cpp
        Source/PluginProcessor.h
        Source/PluginEditor.cpp
        Source/PluginEditor.h
)

target_link_libraries(PreampNo4
    PRIVATE
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

target_compile_definitions(PreampNo4
    PUBLIC
        JUCE_VST3_CAN_REPLACE_VST2=0
)
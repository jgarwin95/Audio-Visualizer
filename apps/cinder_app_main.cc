//
// Created by garwi on 11/15/2020.
//


#include "visualizer/music_visualizer_app.h"

using music_visualizer::MusicVisualizerApp;

void prepareSettings(MusicVisualizerApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(MusicVisualizerApp, ci::app::RendererGl, prepareSettings);



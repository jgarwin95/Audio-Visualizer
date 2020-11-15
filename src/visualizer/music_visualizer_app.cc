//
// Created by garwi on 11/15/2020.
//

#include "../../include/visualizer/music_visualizer_app.h"


namespace music_visualizer {

MusicVisualizerApp::MusicVisualizerApp() : container_((int) kWindowSizeX, (int) kWindowSizeY){
  ci::app::setWindowSize((int) kWindowSizeX, (int) kWindowSizeY);
}

void MusicVisualizerApp::setup() {
}

void MusicVisualizerApp::draw() {
  ci::Color8u background_color(0, 0, 0);  // black
  ci::gl::clear(background_color);

  container_.Draw();
}

void MusicVisualizerApp::update() {
  container_.Update();
}

}  // namespace music_visualizer


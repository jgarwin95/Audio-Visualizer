//
// Created by garwi on 11/15/2020.
//

#include "../../include/visualizer/music_visualizer_app.h"

namespace music_visualizer {
using namespace ci;

MusicVisualizerApp::MusicVisualizerApp() : container_((int) kWindowSizeX, (int) kWindowSizeY){
  app::setWindowSize((int) kWindowSizeX, (int) kWindowSizeY);
}

void MusicVisualizerApp::setup() {
  // helpful sources for loading files in cinder:
  // https://github.com/Leundai/Vibing-Audiovisual/blob/master/apps/vibe_app.cc
  // https://github.com/paulhoux/Cinder-Samples/blob/master/AudioVisualizer/src/AudioVisualizerApp.cpp
  try {
    fs::path path = getOpenFilePath("", {"mp3", "wav"});
    if (!path.empty()) {
      player_.LoadMusic(path);
      player_.PlayMusic();
    }
  } catch (Exception &exc) {
    app::console() << "Unable to load music file. " << exc.what() << std::endl;
  }
}

void MusicVisualizerApp::draw() {
  Color8u background_color(0, 0, 0);  // black
  gl::clear(background_color);

  container_.Draw();
}

void MusicVisualizerApp::update() {
  container_.Update();
  container_.ScaleConnectionStrength(player_.GetDecibelLevel());
}

void MusicVisualizerApp::mouseMove(app::MouseEvent event) {
  container_.UpdateMouseNode(event.getPos());
}

}  // namespace music_visualizer


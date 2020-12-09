//
// Created by garwi on 11/15/2020.
//

#include "../../include/visualizer/music_visualizer_app.h"
#include "cinder/CinderImGui.h"

namespace music_visualizer {
using namespace ci;

MusicVisualizerApp::MusicVisualizerApp() : container_((int) kWindowSizeX, (int) kWindowSizeY){
  app::setWindowSize((int) kWindowSizeX, (int) kWindowSizeY);
  app::setWindowPos(50,50);
  music_is_playing_ = false;
  picker1_ = ColorPicker((int)(kWindowSizeX - 400), 50);
}

void MusicVisualizerApp::setup() {
  ImGui::Initialize();
  // helpful sources for loading files in cinder:
  // https://github.com/Leundai/Vibing-Audiovisual/blob/master/apps/vibe_app.cc
  // https://github.com/paulhoux/Cinder-Samples/blob/master/AudioVisualizer/src/AudioVisualizerApp.cpp
  try {
    fs::path path = getOpenFilePath("", {"mp3", "wav"});
    if (!path.empty()) {
      player_.LoadMusic(path);
      player_.PlayMusic();
      music_is_playing_ = true;
    } else {
      music_is_playing_ = false;
    }
  } catch (Exception &exc) {
    app::console() << "Unable to load music file. " << exc.what() << std::endl;
  }
}

void MusicVisualizerApp::draw() {
  Color8u background_color(0, 0, 0);  // black
  gl::clear(background_color);

  picker1_.Draw();
  //container_.Draw();
}

void MusicVisualizerApp::update() {
  // TODO:: remove this when done!
  /*
  if (music_is_playing_) {
    // Feed current volume level to container
    container_.Update(player_.GetRMSVolume());
  } else {
    // no music is playing
    container_.Update();
  }
   */
}

void MusicVisualizerApp::mouseMove(app::MouseEvent event) {
  container_.UpdateMouseNode(event.getPos());
}

}  // namespace music_visualizer


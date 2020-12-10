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
  background_picker_ = ColorPicker((int)(kWindowSizeX - 400), 50);
  node_picker_ = ColorPicker((int)(background_picker_.GetRect().getX1()), (int)(background_picker_.GetRect().getY2() + 50));
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
  gl::clear(BACKGROUND_COLOR);

  container_.Draw();
  background_picker_.Draw();
  node_picker_.Draw();
}

void MusicVisualizerApp::update() {
  if (music_is_playing_) {
    // Feed current volume level to container
    container_.Update(player_.GetRMSVolume());
  } else {
    // no music is playing
    container_.Update();
  }
}

void MusicVisualizerApp::mouseMove(app::MouseEvent event) {
  container_.UpdateMouseNode(event.getPos());
}

void MusicVisualizerApp::mouseDown(app::MouseEvent event) {
  glm::vec2 eventPos = event.getPos();
  // if within bounds of color picker
  if ((eventPos.x > background_picker_.GetRect().getX1()) && (eventPos.x < background_picker_.GetRect().getX2()) &&
      (eventPos.y > background_picker_.GetRect().getY1()) && (eventPos.y < background_picker_.GetRect().getY2())) {
    std::vector<int> colors = background_picker_.GetColorsAtLocation(eventPos);
    BACKGROUND_COLOR = ci::Color8u(colors.at(0),colors.at(1),colors.at(2));
  }
  else if ((eventPos.x > node_picker_.GetRect().getX1()) && (eventPos.x < node_picker_.GetRect().getX2()) &&
      (eventPos.y > node_picker_.GetRect().getY1()) && (eventPos.y < node_picker_.GetRect().getY2())) {
    std::vector<int> colors2 = node_picker_.GetColorsAtLocation(eventPos);
    container_.ChangeNodeColors(colors2);
    //NODE_COLOR = ci::Color8u(colors2.at(0),colors2.at(1),colors2.at(2));
  }
}
}  // namespace music_visualizer


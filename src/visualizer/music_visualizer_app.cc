//
// Created by garwi on 11/15/2020.
//

#include "../../include/visualizer/music_visualizer_app.h"

namespace music_visualizer {
using namespace ci;

MusicVisualizerApp::MusicVisualizerApp() : container_((int) kWindowSizeX, (int) kWindowSizeY){
  app::setWindowSize((int) kWindowSizeX, (int) kWindowSizeY);
  app::setWindowPos(50,50);
  palette1_ = ColorPalette((int)(kWindowSizeX - 450), 50);
  palette2_ = ColorPalette((int)palette1_.GetRect().getX1(), (int)(palette1_.GetRect().getY2() + 50));
  music_is_playing_ = false;
  draw_count = 0;
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
      music_is_playing_ = true;
    } else {
      music_is_playing_ = false;
    }
  } catch (Exception &exc) {
    app::console() << "Unable to load music file. " << exc.what() << std::endl;
  }
  // start the timer
  app::setFrameRate(45);
}

void MusicVisualizerApp::draw() {
  // Draw pickers twice to keep from phasing in and out
  if(draw_count < 2) {
    palette1_.Draw();
    palette2_.Draw();
    draw_count++;
  }
  container_.Draw();
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
  if (event.getPos().x < container_.GetRect().getX2()) {
    container_.UpdateMouseNode(event.getPos());
  }
}

void MusicVisualizerApp::mouseDown(app::MouseEvent event) {
  glm::vec2 eventPos = event.getPos();
  // if even is clicking on color picker 1
  if (palette1_.IsInboundsOfColorPicker(eventPos)) {
    std::vector<int> colors = palette1_.GetPickerColor(eventPos);
    container_.ChangeBackgroundColor(colors);
  }
    // if event is clicking on color picker 2
  else if (palette2_.IsInboundsOfColorPicker(eventPos)) {
    std::vector<int> colors2 = palette2_.GetPickerColor(eventPos);
    Node::ChangeColor(colors2);
    Connector::ChangeColor(colors2);
  }
    // if event is clicking on color bar 1
  else if (palette1_.IsInboundsOfColorBar(eventPos)) {
    palette1_.ChangePickerColor(eventPos);
    draw_count = 0;
  }
    // if event is clicking on color bar 2
  else if (palette2_.IsInboundsOfColorBar(eventPos)) {
    palette2_.ChangePickerColor(eventPos);
    draw_count = 0;
  }
}
}  // namespace music_visualizer
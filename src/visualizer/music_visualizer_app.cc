//
// Created by garwi on 11/15/2020.
//

#include "../../include/visualizer/music_visualizer_app.h"

namespace music_visualizer {
using namespace ci;

MusicVisualizerApp::MusicVisualizerApp() : container_((int) kWindowSizeX, (int) kWindowSizeY){
  app::setWindowSize((int) kWindowSizeX, (int) kWindowSizeY);
  app::setWindowPos(50,50);
  background_picker_ = ColorPicker((int)(kWindowSizeX - 400), 50);
  color_bar_background_ = ColorBar((int)(background_picker_.GetRect().getX1() - 50), (int)(background_picker_.GetRect().getY1()),
                        (int)background_picker_.GetRect().getWidth(), (int)background_picker_.GetRect().getHeight());
  node_picker_ = ColorPicker((int)(background_picker_.GetRect().getX1()), (int)(background_picker_.GetRect().getY2() + 50));
  color_bar_node_ = ColorBar((int)(node_picker_.GetRect().getX1() - 50), (int)(node_picker_.GetRect().getY1()),
                        (int)node_picker_.GetRect().getWidth(), (int)node_picker_.GetRect().getHeight());
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
    background_picker_.Draw();
    node_picker_.Draw();
    color_bar_background_.Draw();
    color_bar_node_.Draw();
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
  if ((eventPos.x > background_picker_.GetRect().getX1()) && (eventPos.x < background_picker_.GetRect().getX2()) &&
      (eventPos.y > background_picker_.GetRect().getY1()) && (eventPos.y < background_picker_.GetRect().getY2())) {
    std::vector<int> colors = background_picker_.GetColorsAtLocation(eventPos);
    container_.ChangeBackgroundColor(colors);
  }
  // if event is clicking on color picker 2
  else if ((eventPos.x > node_picker_.GetRect().getX1()) && (eventPos.x < node_picker_.GetRect().getX2()) &&
      (eventPos.y > node_picker_.GetRect().getY1()) && (eventPos.y < node_picker_.GetRect().getY2())) {
    std::vector<int> colors2 = node_picker_.GetColorsAtLocation(eventPos);
    Node::ChangeColor(colors2);
    Connector::ChangeColor(colors2);
  }
  // if event is clicking on color bar 1
  else if ((eventPos.x > color_bar_background_.GetRect().getX1()) && (eventPos.x < color_bar_background_.GetRect().getX2()) &&
      (eventPos.y > color_bar_background_.GetRect().getY1()) && (eventPos.y < color_bar_background_.GetRect().getY2())) {
    std::vector<int> colors3 = color_bar_background_.GetColorsAtLocation(eventPos);
    // change color for background color picker
    background_picker_.ChangeColors(colors3);
    draw_count = 0;
  }
    // if event is clicking on color bar 2
  else if ((eventPos.x > color_bar_node_.GetRect().getX1()) && (eventPos.x < color_bar_node_.GetRect().getX2()) &&
      (eventPos.y > color_bar_node_.GetRect().getY1()) && (eventPos.y < color_bar_node_.GetRect().getY2())) {
    std::vector<int> colors4 = color_bar_node_.GetColorsAtLocation(eventPos);
    node_picker_.ChangeColors(colors4);
    draw_count = 0;
  }
}
}  // namespace music_visualizer


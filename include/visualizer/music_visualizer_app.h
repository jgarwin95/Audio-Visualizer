//
// Created by garwi on 11/15/2020.
//

#ifndef FINAL_PROJECT_JGARWIN95_SRC_CORE_MUSIC_VISUALIZER_APP_H_
#define FINAL_PROJECT_JGARWIN95_SRC_CORE_MUSIC_VISUALIZER_APP_H_

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "core/container.h"
#include "music_player/music_player.h"


namespace music_visualizer {

using namespace ci;

/**
 * Simulation of ideal gases.
 */
class MusicVisualizerApp : public ci::app::App {
 public:
  MusicVisualizerApp();

  void draw() override;
  void update() override;
  void setup() override;
  void mouseMove(app::MouseEvent event) override;

  const double kWindowSizeX = 1100;
  const double kWindowSizeY = 950;

 private:
  Container container_;
  MusicPlayer player_;
};

}  // namespace music_visualizer


#endif //FINAL_PROJECT_JGARWIN95_SRC_CORE_MUSIC_VISUALIZER_APP_H_

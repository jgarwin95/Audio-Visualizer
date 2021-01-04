//
// Created by garwi on 1/4/2021.
//

#ifndef MUSIC_VISUALIZER_SRC_CONTROLS_COLOR_PALLETE_H_
#define MUSIC_VISUALIZER_SRC_CONTROLS_COLOR_PALLETE_H_

#include "cinder/gl/gl.h"
#include "color_picker.h"
#include "color_bar.h"

namespace music_visualizer {

class ColorPallete {
 public:
  ColorPallete(int x_pos, int y_pos);
  void Draw();

 private:
  ci::Rectf rect_;
  glm::vec2 top_left_;
  ColorPicker picker_;
  ColorBar bar_;
};

} // namespace music_visualizer

#endif  // MUSIC_VISUALIZER_SRC_CONTROLS_COLOR_PALLETE_H_

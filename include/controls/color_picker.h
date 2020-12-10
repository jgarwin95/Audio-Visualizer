//
// Created by garwi on 12/9/2020.
//

#ifndef MUSIC_VISUALIZER_SRC_CONTROLS_COLOR_PICKER_H_
#define MUSIC_VISUALIZER_SRC_CONTROLS_COLOR_PICKER_H_

#include "cinder/gl/gl.h"

namespace music_visualizer {

class ColorPicker {
 public:
  ColorPicker() = default;
  ColorPicker(int x_pos, int y_pos);
  void Draw();

 private:
  ci::Rectf rect_;
  glm::vec2 top_left_;
  int kXdimension = 255;
  int kYdimension = 255;

  int current_red_ = 255;
  int current_green_ = 128;
  int current_blue_ = 0;
};

}

#endif //MUSIC_VISUALIZER_SRC_CONTROLS_COLOR_PICKER_H_

//
// Created by garwi on 12/9/2020.
//

#include "controls/color_picker.h"

namespace music_visualizer {

ColorPicker::ColorPicker(int x_pos, int y_pos) {
  top_left_ = glm::vec2(x_pos, y_pos);
  rect_ = ci::Rectf(top_left_, top_left_ + glm::vec2(kXdimension, kYdimension));
}

void ColorPicker::Draw() {
  // Draw the outer box
  ci::Color8u background_color(255, 255, 255);  //white
  ci::gl::color(background_color);
  ci::gl::drawStrokedRect(rect_);
  // Draw the inner points
  float rect_side = 5;
  glm::vec2 current_radius_pos = top_left_ + glm::vec2(3,3);
  // double for loop that moves the current rect position along by an amount equal to the side length
  for (float x = 0; x <= kXdimension; x += rect_side) {
    for (float y = 0; y <= kYdimension; y += rect_side) {
      ci::Color8u rect_color((int) x, 0, 0);
      ci::gl::color(rect_color);
      ci::Rectf current(top_left_ + glm::vec2(x,y), top_left_ + glm::vec2(x + rect_side,y + rect_side));
      ci::gl::drawSolidRect(current);
    }
  }
}

} // namespace music_visualizer

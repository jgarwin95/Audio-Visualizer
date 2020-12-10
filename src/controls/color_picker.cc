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
  for (float y = 0; y < kYdimension; y += rect_side) {
    for (float x = 0; x < kXdimension; x += rect_side) {
      ci::Color8u rect_color;
      // The primary color is only a function of the the height of the box (it does not vary with x direction)
      // The other two colors do vary with respect to both x and y. The other colors increase when y increasing however,
      // the amount to which they vary depends on some scaling factor x. If x is maximum then the colors don't depend on y
      // at all. If x in minimum then the colors vary with y proportional to changes in y.
      rect_color = ci::Color8u((int)(current_color_ - y), (int)((((255 - x)/255)*(255 - y))), (int)((((255 - x)/255)*(255 - y))));
      ci::gl::color(rect_color);
      ci::Rectf current(top_left_ + glm::vec2(x,y), top_left_ + glm::vec2(x + rect_side,y + rect_side));
      ci::gl::drawSolidRect(current);
    }
  }
}

} // namespace music_visualizer

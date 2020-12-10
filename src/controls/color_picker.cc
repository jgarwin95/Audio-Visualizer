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
  // Draw the inner points
  float rect_side = 5;
  glm::vec2 current_radius_pos = top_left_ + glm::vec2(3,3);
  // double for loop that moves the current rect position along by an amount equal to the side length
  for (float y = 0; y < kYdimension; y += rect_side) {
    for (float x = 0; x < kXdimension; x += rect_side) {
      ci::Color8u rect_color;
      // The colors are determined by an initial set level of color with components in red, green, and blue
      // the color pallet is then created based on the dimensions of the container. The upper left corner is always
      // white and the bottom of the entire container is always black. In order to achieve this a couple scaling
      // factors need to be used. the x scale ranges from 0 to 255 and there is the additional term added for the
      // baseline color. This entire term is then scaled by the proportion that is in the y direction. If y is max
      // value then no color is present (0,0,0) if y is minimum then this scaling has no effect.
      rect_color = ci::Color8u((int)(((255-y)/255) * ((255 - x) + ((x*current_red_)/255))),
                               (int)(((255-y)/255) * ((255 - x) + ((x*current_green_)/255))),
                               (int)(((255-y)/255) * ((255 - x) + ((x*current_blue_)/255))));
      ci::gl::color(rect_color);
      ci::Rectf current(top_left_ + glm::vec2(x,y), top_left_ + glm::vec2(x + rect_side,y + rect_side));
      ci::gl::drawSolidRect(current);
    }
  }
  // Draw the outer box
  ci::Color8u background_color(255, 255, 255);  //white
  ci::gl::color(background_color);
  ci::gl::drawStrokedRect(rect_);
}

} // namespace music_visualizer

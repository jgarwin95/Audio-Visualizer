//
// Created by garwi on 12/10/2020.
//

#include "controls/color_segment.h"

namespace music_visualizer {

ColorSegment::ColorSegment(int x_pos, int y_pos, int width, int height, std::vector<int> init_state, std::vector<int> change) {
  start_ = init_state;
  end_ = change;
  height_ = height;
  width_ = width;
  top_left_ = glm::vec2(x_pos, y_pos);
  rect_ = ci::Rectf(top_left_, top_left_ + glm::vec2(width, height));
}

void ColorSegment::Draw() {
  float rect_height = 4;
  for (float y = 0; y <= height_; y += rect_height) {
    ci::Color8u rect_color((int)((255 * start_.at(0) + 255*end_.at(0)*(y/height_))),
                           (int)((255 * start_.at(1) + 255*end_.at(1)*(y/height_))),
                           (int)((255 * start_.at(2) + 255*end_.at(2)*(y/height_))));
    ci::gl::color(rect_color);
    ci::Rectf current(top_left_ + glm::vec2(0,y), top_left_ + glm::vec2(width_,y + rect_height));
    ci::gl::drawSolidRect(current);
  }
}

const cinder::Rectf &ColorSegment::GetRect() const {
  return rect_;
}


std::vector<int> ColorSegment::GetColorsAtLocation(glm::vec2& vec) {
  glm::vec2 coords = vec - top_left_;
  std::vector<int> colors = {(int)((255 * start_.at(0) + 255*end_.at(0)*(coords.y/height_))),
                             (int)((255 * start_.at(1) + 255*end_.at(1)*(coords.y/height_))),
                             (int)((255 * start_.at(2) + 255*end_.at(2)*(coords.y/height_)))};
  return colors;
}


} // namespace music_visualizer

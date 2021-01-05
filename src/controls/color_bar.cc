//
// Created by garwi on 12/10/2020.
//

#include "controls/color_bar.h"
#include <math.h>

namespace music_visualizer {

ColorBar::ColorBar(int x_pos, int y_pos, int width, int height) {
  height_ = height/6;
  width_ = width/10;
  top_left_ = glm::vec2(x_pos, y_pos);
  rect_ = ci::Rectf(top_left_, top_left_ + glm::vec2(width_, height));

  ColorSegment color_bar1_ = ColorSegment(x_pos, y_pos, width_, height_,std::vector<int> {1,0,0}, std::vector<int> {0,1,0});
  ColorSegment color_bar2_ = ColorSegment((int)(color_bar1_.GetRect().getX1()), (int)(color_bar1_.GetRect().getY2()),
                                          width_, height_,std::vector<int> {1,1,0}, std::vector<int> {-1,0,0});
  ColorSegment color_bar3_ = ColorSegment((int)(color_bar2_.GetRect().getX1()), (int)(color_bar2_.GetRect().getY2()),
                                          width_, height_,std::vector<int> {0,1,0}, std::vector<int> {0,0,1});
  ColorSegment color_bar4_ = ColorSegment((int)(color_bar3_.GetRect().getX1()), (int)(color_bar3_.GetRect().getY2()),
                                          width_, height_,std::vector<int> {0,1,1}, std::vector<int> {0,-1,0});
  ColorSegment color_bar5_ = ColorSegment((int)(color_bar4_.GetRect().getX1()), (int)(color_bar4_.GetRect().getY2()),
                                          width_, height_,std::vector<int> {0,0,1}, std::vector<int> {1,0,0});
  ColorSegment color_bar6_ = ColorSegment((int)(color_bar5_.GetRect().getX1()), (int)(color_bar5_.GetRect().getY2()),
                                          width_, height_,std::vector<int> {1,0,1}, std::vector<int> {0,0,-1});
  segments_.push_back(color_bar1_);
  segments_.push_back(color_bar2_);
  segments_.push_back(color_bar3_);
  segments_.push_back(color_bar4_);
  segments_.push_back(color_bar5_);
  segments_.push_back(color_bar6_);
}

void ColorBar::Draw() {
  for (ColorSegment& segment : segments_) {
    segment.Draw();
  }
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(rect_);
}

const cinder::Rectf &ColorBar::GetRect() const {
  return rect_;
}

std::vector<int> ColorBar::GetColorsAtLocation(glm::vec2& vec) {
  glm::vec2 coords = vec - top_left_;
  int pos = (int)floor(coords.y/height_);
  std::vector<int> colors = segments_.at(pos).GetColorsAtLocation(vec);
  return colors;
}

} // namespace music_visualizer

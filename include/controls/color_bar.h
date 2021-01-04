//
// Created by garwi on 12/10/2020.
//

#ifndef MUSIC_VISUALIZER_SRC_CONTROLS_COLOR_BAR_H_
#define MUSIC_VISUALIZER_SRC_CONTROLS_COLOR_BAR_H_

#include "cinder/gl/gl.h"
#include "color_segment.h"

namespace music_visualizer {

class ColorBar {
 public:
  ColorBar() = default;
  ColorBar(int x_pos, int y_pos, int width, int height);
  void Draw();
  const cinder::Rectf &GetRect() const;
  std::vector<int> GetColorsAtLocation(glm::vec2& vec);

 private:
  ci::Rectf rect_;
  glm::vec2 top_left_;

  std::vector<ColorSegment> segments_;
  int height_;
  int width_;
};

} // namespace music_visualizer

#endif //MUSIC_VISUALIZER_SRC_CONTROLS_COLOR_BAR_H_

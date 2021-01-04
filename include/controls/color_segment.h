//
// Created by garwi on 12/10/2020.
//

#ifndef MUSIC_VISUALIZER_SRC_CONTROLS_COLOR_SEGMENT_H_
#define MUSIC_VISUALIZER_SRC_CONTROLS_COLOR_SEGMENT_H_

#include "cinder/gl/gl.h"

namespace music_visualizer {

class ColorSegment {
 public:
  ColorSegment() = default;
  ColorSegment(int x_pos, int y_pos, int width, int height, std::vector<int> init_state, std::vector<int> change);
  void Draw();
  const cinder::Rectf &GetRect() const;
  std::vector<int> GetColorsAtLocation(glm::vec2& vec);

 private:
  ci::Rectf rect_;
  glm::vec2 top_left_;

  std::vector<int> start_;
  std::vector<int> end_;
  int height_;
  int width_;
};

} // namespace music_visualizer

#endif //MUSIC_VISUALIZER_SRC_CONTROLS_COLOR_SEGMENT_H_

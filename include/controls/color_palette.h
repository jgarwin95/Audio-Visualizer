//
// Created by garwi on 1/4/2021.
//

#ifndef MUSIC_VISUALIZER_SRC_CONTROLS_COLOR_PALLETE_H_
#define MUSIC_VISUALIZER_SRC_CONTROLS_COLOR_PALLETE_H_

#include "cinder/gl/gl.h"
#include "color_picker.h"
#include "color_bar.h"

namespace music_visualizer {

class ColorPalette {
 public:
  ColorPalette() = default;
  ColorPalette(int x_pos, int y_pos);
  void Draw();
  bool IsInboundsOfColorBar(glm::vec2& pos);
  bool IsInboundsOfColorPicker(glm::vec2& pos);
  void ChangePickerColor(glm::vec2& pos);
  std::vector<int> GetPickerColor(glm::vec2& pos);
  const cinder::Rectf& GetRect() const;

 private:
  int kDimensionPicker = 255;
  int kWidthBar = 25;
  int kSpacing = 50;
  ci::Rectf rect_;
  glm::vec2 top_left_;
  ColorPicker picker_;
  ColorBar bar_;
};

} // namespace music_visualizer

#endif  // MUSIC_VISUALIZER_SRC_CONTROLS_COLOR_PALLETE_H_

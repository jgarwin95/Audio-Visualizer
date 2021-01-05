//
// Created by garwi on 1/4/2021.
//

#include "controls/color_palette.h"

namespace music_visualizer {

ColorPalette::ColorPalette(int x_pos, int y_pos) {
  top_left_ = glm::vec2(x_pos, y_pos);
  rect_ = ci::Rectf(top_left_, top_left_ + glm::vec2(kDimensionPicker + kSpacing, kDimensionPicker));
  picker_ = ColorPicker(x_pos + kSpacing, y_pos);
  bar_ = ColorBar(x_pos, y_pos, kDimensionPicker, kDimensionPicker);
}

void ColorPalette::Draw() {
  picker_.Draw();
  bar_.Draw();
}

bool ColorPalette::IsInboundsOfColorBar(glm::vec2& pos) {
  return ((pos.x > bar_.GetRect().getX1()) && (pos.x < bar_.GetRect().getX2()) &&
      (pos.y > bar_.GetRect().getY1()) && (pos.y < bar_.GetRect().getY2()));
}

bool ColorPalette::IsInboundsOfColorPicker(glm::vec2& pos) {
  return ((pos.x > picker_.GetRect().getX1()) && (pos.x < picker_.GetRect().getX2()) &&
      (pos.y > picker_.GetRect().getY1()) && (pos.y < picker_.GetRect().getY2()));
}

void ColorPalette::ChangePickerColor(glm::vec2& pos) {
  picker_.ChangeColors(bar_.GetColorsAtLocation(pos));
}

std::vector<int> ColorPalette::GetPickerColor(glm::vec2& pos) {
  return picker_.GetColorsAtLocation(pos);
}

const cinder::Rectf& ColorPalette::GetRect() const {
  return rect_;
}

} //namespace music_visualizer

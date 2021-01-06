//
// Created by garwi on 11/15/2020.
//

#include "core/connector.h"
#include "core/container.h"

namespace music_visualizer {

Connector::Connector(const Node& node1,const Node& node2) : node1_(node1), node2_(node2) {
  distance_ = glm::distance(node1.GetPos(), node2.GetPos());
}

void Connector::Draw() {
  // Only draw if they are within range
  if (glm::distance(node1_.GetPos(), node2_.GetPos()) < MAX_CONNECTION_DISTANCE) {
    ci::gl::color(color_);
    ci::gl::drawLine(node1_.GetPos(), node2_.GetPos());
  }
}

void Connector::Update(ci::Color8u &background, float volume) {
  distance_ = glm::distance(node1_.GetPos(), node2_.GetPos());
  // save baseline, background, and current color
  int baseline_red = CONNECTOR_COLOR.r;
  int baseline_green = CONNECTOR_COLOR.g;
  int baseline_blue = CONNECTOR_COLOR.b;
  int background_red = background.r;
  int background_green = background.g;
  int background_blue = background.b;
  int current_red = 0;
  int current_green = 0;
  int current_blue = 0;
  if (distance_ < MIN_CONNECTION_DISTANCE) {
    // full connection strength if within MIN_CONNECTION_DISTANCE
    current_red = baseline_red;
    current_green = baseline_green;
    current_blue = baseline_blue;
  } else if (distance_ <= MAX_CONNECTION_DISTANCE) {
    // color(shading) is proportional to distance between particles
    // min value is baseline (occurs at max distance) with maximum being background
    // (occurs at min distance)
    current_red = baseline_red + (int) ((background_red - baseline_red) * ((distance_ - MIN_CONNECTION_DISTANCE)/(MAX_CONNECTION_DISTANCE - MIN_CONNECTION_DISTANCE)));
    current_green = baseline_green + (int) ((background_green - baseline_green) * ((distance_ - MIN_CONNECTION_DISTANCE)/(MAX_CONNECTION_DISTANCE - MIN_CONNECTION_DISTANCE)));
    current_blue = baseline_blue + (int) ((background_blue - baseline_blue) * ((distance_ - MIN_CONNECTION_DISTANCE)/(MAX_CONNECTION_DISTANCE - MIN_CONNECTION_DISTANCE)));
  } else {
    // equivalent to the current background
    current_red = background_red;
    current_green = background_green;
    current_blue = background_blue;
  }
  std::vector<int> colors = {current_red, current_green, current_blue};
  UpdateColor(colors);
  // scale color with itself according to RMS volume
  //color_ = (int)(color_*volume);
}

ci::Color8u Connector::GetColor() const {
  return color_;
}

float Connector::GetDistance() const {
  return distance_;
}

void Connector::ChangeColor(const std::vector<int> &colors) {
  // baseline color set
  CONNECTOR_COLOR = ci::Color8u(colors.at(0),colors.at(1),colors.at(2));
}

void Connector::UpdateColor(const std::vector<int>& colors) {
  // set instance color
  color_ = ci::Color8u(colors.at(0),colors.at(1),colors.at(2));
}


} // namespace music_visualizer

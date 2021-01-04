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
    ci::gl::color(CONNECTOR_COLOR);
    ci::gl::drawLine(node1_.GetPos(), node2_.GetPos());
  }
}

void Connector::Update(float volume) {
  distance_ = glm::distance(node1_.GetPos(), node2_.GetPos());
  if (distance_ < MIN_CONNECTION_DISTANCE) {
    // full connection strength if within MIN_CONNECTION_DISTANCE
    color_ = 255;
  } else if (distance_ <= MAX_CONNECTION_DISTANCE) {
    // color(shading) is proportional to distance between particles
    color_ = 255 - (int) (255 * ((distance_ - MIN_CONNECTION_DISTANCE)/(MAX_CONNECTION_DISTANCE - MIN_CONNECTION_DISTANCE)));
  } else {
    color_ = 0;
  }
  // scale color with itself according to RMS volume
  color_ = (int)(color_*volume);
}

int Connector::GetColor() const {
  return color_;
}

float Connector::GetDistance() const {
  return distance_;
}

void Connector::ChangeColor(const std::vector<int> &colors) {
  CONNECTOR_COLOR = ci::Color8u(colors.at(0),colors.at(1),colors.at(2));
}
} // namespace music_visualizer

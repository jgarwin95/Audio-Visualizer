//
// Created by garwi on 11/15/2020.
//

#include "core/connector.h"

namespace music_visualizer {

Connector::Connector(Node& node1, Node& node2) : node1_(node1), node2_(node2) {
  distance_ = glm::distance(node1.GetPos(), node2.GetPos());
}

void Connector::Draw() {
  // Only draw if they are within range
  if (glm::distance(node1_.GetPos(), node2_.GetPos()) < MAX_DISTANCE) {
    ci::gl::color(ci::Color8u(color_,color_,color_));
    ci::gl::drawLine(node1_.GetPos(), node2_.GetPos());
  }
}

void Connector::Update() {
  distance_ = glm::distance(node1_.GetPos(), node2_.GetPos());
  if (distance_ <= MAX_DISTANCE) {
    // color(shading) is proportional to distance between particles
    color_ = 255 - (int) (255 * distance_/MAX_DISTANCE);
  }
}
} // namespace music_visualizer

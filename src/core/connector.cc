//
// Created by garwi on 11/15/2020.
//

#include "core/connector.h"

namespace music_visualizer {

Connector::Connector(Node& node1, Node& node2) : node1_(node1), node2_(node2) {
  distance_ = glm::distance(node1.GetPos(), node2.GetPos());
  connection_strength_ = 200.0f/distance_;
}

void Connector::Draw() {
  // Only draw if they are within range
  if (glm::distance(node1_.GetPos(), node2_.GetPos()) < 200) {
    ci::gl::color(ci::Color("white"));
    ci::gl::drawLine(node1_.GetPos(), node2_.GetPos());
  }
}

float Connector::GetDistance() {
  return glm::distance(node1_.GetPos(), node2_.GetPos());
}

} // namespace music_visualizer

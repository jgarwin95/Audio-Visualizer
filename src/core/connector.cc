//
// Created by garwi on 11/15/2020.
//

#include "core/connector.h"

namespace music_visualizer {

Connector::Connector(const Node& node1,const Node& node2) : node1_(node1), node2_(node2) {
  distance_ = glm::distance(node1.GetPos(), node2.GetPos());
}

void Connector::Draw() {
  // Only draw if they are within range
  if (glm::distance(node1_.GetPos(), node2_.GetPos()) < MAX_CONNECTION_DISTANCE) {
    ci::gl::color(ci::Color8u(color_,color_,color_));
    ci::gl::drawLine(node1_.GetPos(), node2_.GetPos());
  }
}

void Connector::Update() {
  distance_ = glm::distance(node1_.GetPos(), node2_.GetPos());
  if (distance_ <= 50) {
    // full connection strength if within 50
    color_ = 255;
  } else if (distance_ <= MAX_CONNECTION_DISTANCE) {
    // color(shading) is proportional to distance between particles
    color_ = 255 - (int) (255 * distance_/(MAX_CONNECTION_DISTANCE - 50));
  }
}
} // namespace music_visualizer

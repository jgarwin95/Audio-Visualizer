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
  if (distance_ < current_min_dist_) {
    // full connection strength if within MIN_CONNECTION_DISTANCE
    color_ = 255;
  } else if (distance_ <= current_max_dist_) {
    // color(shading) is proportional to distance between particles
    color_ = 255 - (int) (255 * ((distance_ - current_min_dist_)/(current_max_dist_ - current_min_dist_)));
  } else {
    color_ = 0;
  }
}

void Connector::ScaleColor(float decibel) {
  color_ = (int)(255*decibel);
  //current_max_dist_ = (MAX_CONNECTION_DISTANCE*decibel);
  //current_min_dist_ = (MIN_CONNECTION_DISTANCE*decibel);
}

int Connector::GetColor() const {
  return color_;
}
float Connector::GetDistance() const {
  return distance_;
}
} // namespace music_visualizer

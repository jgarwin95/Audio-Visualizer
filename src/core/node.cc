//
// Created by garwi on 11/15/2020.
//

#include "core/node.h"
#include "core/container.h"

namespace music_visualizer {

Node::Node(const glm::vec2& pos, const glm::vec2& velo, float radius) : pos_(pos), velo_(velo), radius_(radius) {}

Node::Node() {
  pos_ = glm::vec2(0,0);
  velo_ = glm::vec2(0,0);
  radius_ = 0;
}

void Node::Draw() {
  ci::gl::color(NODE_COLOR);
  ci::gl::drawSolidCircle(pos_, radius_);
}

void Node::Update() {
  // Move node by velocity amount
  pos_ += velo_;

}

const glm::vec2 &Node::GetPos() const {
  return pos_;
}

const glm::vec2 &Node::GetVelo() const {
  return velo_;
}

float Node::GetRadius() const {
  return radius_;
}

void Node::ResetPosition(const glm::vec2 &pos) {
  pos_ = pos;
}

void Node::ResetVelocity(const glm::vec2 &new_velocity) {
  velo_ = new_velocity;
}

void Node::ChangeColor(const std::vector<int> &colors) {
  NODE_COLOR = ci::Color8u(colors.at(0),colors.at(1),colors.at(2));
}


} // namespace music_visualizer

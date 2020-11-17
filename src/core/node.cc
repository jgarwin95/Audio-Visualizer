//
// Created by garwi on 11/15/2020.
//

#include "core/node.h"

namespace music_visualizer {

Node::Node() {
  pos_ = glm::vec2(0,0);
  velo_ = glm::vec2(0,0);
  radius_ = 2;
}

Node::Node(const glm::vec2& pos, const glm::vec2& velo, float radius) : pos_(pos), velo_(velo), radius_(radius) {}

void Node::Draw() {
  ci::gl::color(ci::Color("white"));
  ci::gl::drawSolidCircle(pos_, radius_);
}

void Node::Update() {
  // Move node by velocity amount
  pos_ += velo_;
}

void Node::AddConnection(Node& other) {
  connections_.push_back(other);
}

bool Node::isConnected(Node &other) {
  for (Node& node : connections_) {
    if (node == other) {
      return true;
    }
  }
  return false;
}

const glm::vec2 &Node::GetPos() const {
  return pos_;
}

const glm::vec2 &Node::GetVelo() const {
  return velo_;
}

bool Node::operator==(const Node& rhs) const {
  if ((rhs.GetPos() == this->GetPos()) && rhs.GetVelo() == this->GetVelo()) {
    return true;
  }
  return false;
}

} // namespace music_visualizer

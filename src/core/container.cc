//
// Created by garwi on 11/15/2020.
//

#include "core/container.h"

#include <utility>

namespace music_visualizer {

Container::Container(int X_dimension, int Y_dimension) : x_dimension_(X_dimension), y_dimension_(Y_dimension){
  rect_ = ci::Rectf(glm::vec2(0,0), glm::vec2(X_dimension, Y_dimension));
  // set random seed
  srand(1001);

  for (size_t i = 0; i < NUM_NODES; i++) {
    int x_pos = rand() % x_dimension_;
    int y_pos = rand() % y_dimension_;
    int x_velo = rand() % 7 + (-3); // random number -3 to 3
    int y_velo = rand() % 7 + (-3); // random number -3 to 3
    // alter velocity if both x and y velo are 0 (don't want particles suspended forever)
    if (x_velo == 0 && y_velo == 0) {
      x_velo++;
    }
    nodes_.emplace_back(glm::vec2(x_pos, y_pos), glm::vec2(x_velo,y_velo), 2.0f);
  }

  for (size_t i = 0; i < nodes_.size() - 1; i++) {
    for (size_t j = i + 1; j < nodes_.size(); j++) {
      // create a connection for each node
      connectors_.emplace_back(nodes_.at(i), nodes_.at(j));
    }
  }
}

Container::Container(std::vector<Node> nodes) : x_dimension_(200), y_dimension_(200), nodes_(std::move(nodes)) {
  rect_ = ci::Rectf(glm::vec2(0,0), glm::vec2(x_dimension_, y_dimension_));
  // set random seed
  srand(1001);
  for (size_t i = 0; i < nodes_.size() - 1; i++) {
    for (size_t j = i + 1; j < nodes_.size(); j++) {
      // create a connection for each node
      connectors_.emplace_back(nodes_.at(i), nodes_.at(j));
    }
  }
}

void Container::Draw() {
  for (Node& node : nodes_) {
    node.Draw();
  }
  for (Connector& connector : connectors_) {
    connector.Draw();
  }
}

void Container::Update() {
  for (Node& node : nodes_) {
    float radius = node.GetRadius();
    // node movement
    node.Update();

    // If nodes are out of bounds (far enough to not make any connections with nodes that are in bounds) send them to a new random location
    if (node.GetPos().x - radius >= rect_.x2 + MAX_CONNECTION_DISTANCE || node.GetPos().x + radius <= rect_.x1 - MAX_CONNECTION_DISTANCE ||
        node.GetPos().y - radius >= rect_.y2 + MAX_CONNECTION_DISTANCE || node.GetPos().y + radius <= rect_.y1 - MAX_CONNECTION_DISTANCE) {
      // random side is picked
      int side = rand() % 4; // 0-3
      // generate a random position and velocity
      int x_pos = rand() % (int) ((x_dimension_ - node.GetRadius()));
      int y_pos = rand() % (int) ((y_dimension_ - node.GetRadius()));
      int x_velo = rand() % 4;
      int y_velo = rand() % 4;
      // virtual coin flip to multiply -1 by 1 or 2
      int direction = rand() % 2 + 1;
      // assign new position and velocity
      if (side == 0) { // reset up
        node.ResetPosition(glm::vec2(x_pos, rect_.y1 - radius - MAX_CONNECTION_DISTANCE));
        node.ResetVelocity(glm::vec2(pow(-1,direction)*x_velo,y_velo));
      } else if (side == 1) { // reset down
        node.ResetPosition(glm::vec2(x_pos, rect_.y2 + radius + MAX_CONNECTION_DISTANCE));
        node.ResetVelocity(glm::vec2(pow(-1,direction)*x_velo,-y_velo));
      } else if (side == 2) { // reset right
        node.ResetPosition(glm::vec2(rect_.x2 + radius + MAX_CONNECTION_DISTANCE, y_pos));
        node.ResetVelocity(glm::vec2(-x_velo,pow(-1,direction)*y_velo));
      } else if (side == 3) { // reset left
        node.ResetPosition(glm::vec2(rect_.x1 - radius - MAX_CONNECTION_DISTANCE, y_pos));
        node.ResetVelocity(glm::vec2(x_velo,pow(-1,direction)*y_velo));
      }
    }
  }
  // update connection strength of each connector
  for (Connector& connector : connectors_) {
    connector.Update();
  }
}

const std::vector<Node> &Container::GetNodes() const {
  return nodes_;
}

const std::vector<Connector> &Container::GetConnectors() const {
  return connectors_;
}

} // namespace music_visualizer

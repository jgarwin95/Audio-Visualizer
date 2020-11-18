//
// Created by garwi on 11/15/2020.
//

#include "core/container.h"

namespace music_visualizer {

  Container::Container(int X_dimension, int Y_dimension) : x_dimension_(X_dimension), y_dimension_(Y_dimension){
    rect_ = ci::Rectf(glm::vec2(0,0), glm::vec2(X_dimension, Y_dimension));

    //TODO:: generate random locations for these particles
    for (size_t i = 0; i < 50; i++) {
      nodes_.emplace_back(glm::vec2(X_dimension*2/3.0, Y_dimension/2.0), glm::vec2(-2,0), 2.0f);
    }

    nodes_.emplace_back(glm::vec2(X_dimension*2/3.0, Y_dimension/2.0), glm::vec2(-2,0), 2.0f);
    nodes_.emplace_back(glm::vec2(X_dimension*1/3.0, Y_dimension/2.0 + 100), glm::vec2(2,0), 2.0f);

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

      node.Update();
      //TODO:: nodes that are generating on the side can potentially move directly up the side rather than out into the
      // container space

      // If nodes are out of bounds send them to a new random location
      if (node.GetPos().x - radius > rect_.x2 || node.GetPos().x + radius < rect_.x1 || node.GetPos().y + radius > rect_.y2 ||
          node.GetPos().y - radius < rect_.y1) {
        // random side is picked
        int side = rand() % 4; // 0-3
        // generate a random position and velocity
        int x_pos = rand() % (int) ((x_dimension_ - 2*node.GetRadius()) + node.GetRadius());
        int y_pos = rand() % (int) ((y_dimension_ - 2*node.GetRadius()) + node.GetRadius());
        int x_velo = rand() % 4;
        int y_velo = rand() % 4;
        int direction = rand() % 2 + 1;
        // assign new position and velocity
        if (side == 0) { // reset up
          node.ResetPosition(glm::vec2(x_pos, rect_.y1 - radius));
          node.ResetVelocity(glm::vec2(pow(-1,direction)*x_velo,-y_velo));
        } else if (side == 1) { // reset down
          node.ResetPosition(glm::vec2(x_pos, rect_.y2 + radius));
          node.ResetVelocity(glm::vec2(pow(-1,direction)*x_velo,+y_velo));
        } else if (side == 2) { // reset right
          node.ResetPosition(glm::vec2(rect_.x2 + radius, y_pos));
          node.ResetVelocity(glm::vec2(-x_velo,pow(-1,direction)*y_velo));
        } else if (side == 3) { // reset left
          node.ResetPosition(glm::vec2(rect_.x1 - radius, y_pos));
          node.ResetVelocity(glm::vec2(x_velo,pow(-1,direction)*y_velo));
        }
      }
    }
  }

}

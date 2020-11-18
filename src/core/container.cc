//
// Created by garwi on 11/15/2020.
//

#include "core/container.h"

namespace music_visualizer {

  Container::Container(int X_dimension, int Y_dimension) {
    rect_ = ci::Rectf(glm::vec2(0,0), glm::vec2(X_dimension, Y_dimension));

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

      // If nodes are out of bounds send them to the other side
      if (node.GetPos().x - radius > rect_.x2) {
        node.ResetPosition(glm::vec2(rect_.x1 - radius, node.GetPos().y));
      } else if (node.GetPos().x + radius < rect_.x1) {
        node.ResetPosition(glm::vec2(rect_.x2 + radius, node.GetPos().y));
      }
    }
  }

  bool Container::isOutOfRange(Connector& obj) {
    return obj.GetDistance() > 200;
  }

}

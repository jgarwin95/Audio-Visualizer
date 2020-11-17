//
// Created by garwi on 11/15/2020.
//

#include "core/container.h"

namespace music_visualizer {

  Container::Container(int X_dimension, int Y_dimension) {
    rect_ = ci::Rectf(glm::vec2(0,0), glm::vec2(X_dimension, Y_dimension));

    nodes_.emplace_back(glm::vec2(X_dimension*2/3.0, Y_dimension/2.0), glm::vec2(-2,0), 2.0f);
    nodes_.emplace_back(glm::vec2(X_dimension*1/3.0, Y_dimension/2.0 + 100), glm::vec2(2,0), 2.0f);
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
      node.Update();
    }

    for (size_t i = 0; i < nodes_.size() - 1; i++) {
      for (size_t j = i + 1; j < nodes_.size(); j++) {
        // If nodes are within range create a connector between the two
        glm::vec2 pos1 = nodes_.at(i).GetPos();
        glm::vec2 pos2 = nodes_.at(j).GetPos();
        if ((glm::distance(pos1, pos2) <= 200) && (!nodes_.at(i).isConnected(nodes_.at(j)))) {
          connectors_.emplace_back(nodes_.at(i), nodes_.at(j));
          nodes_.at(i).AddConnection(nodes_.at(j));
          nodes_.at(j).AddConnection(nodes_.at(i));
        }
      }
    }
  }

}

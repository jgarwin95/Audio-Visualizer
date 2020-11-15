//
// Created by garwi on 11/15/2020.
//

#include "core/container.h"

namespace music_visualizer {

  Container::Container(int X_dimension, int Y_dimension) {
    rect_ = ci::Rectf(glm::vec2(0,0), glm::vec2(X_dimension, Y_dimension));

    nodes_.emplace_back(glm::vec2(X_dimension/3.0, Y_dimension/3.0), glm::vec2(2,0), 2.0f);
    nodes_.emplace_back(glm::vec2(X_dimension*2/3.0, Y_dimension/2), glm::vec2(-2,0), 2.0f);
  }

  void Container::Draw() {
    for (Node& node : nodes_) {
      node.Draw();
    }
  }

  void Container::Update() {
    for (Node& node : nodes_) {
      node.Update();
    }
  }

}

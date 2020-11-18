//
// Created by garwi on 11/15/2020.
//

#ifndef MUSIC_VISUALIZER_SRC_CORE_CONNECTOR_H_
#define MUSIC_VISUALIZER_SRC_CORE_CONNECTOR_H_

#include "node.h"

namespace music_visualizer {

class Connector {

 public:
  Connector(Node& node1, Node& node2);
  void Draw();

  void Update();
  float GetDistance();

  //TODO:: Why do I need a copy constructor for the purposes of removing an item from a vector? What does it mean it is trying to reference a deleted function?
  Connector& Connector::operator=(const Connector& source) {
  if(this != &source) {
    this->node1_ = source.node1_;
    this->node2_ = source.node2_;
    this->distance_ = glm::distance(node1_.GetPos(), node2_.GetPos());
  }
  return *this;
  }


 private:
  float distance_;
  Node& node1_;
  Node& node2_;
  float connection_strength_;
};

} // namespace music_visualizer

#endif //MUSIC_VISUALIZER_SRC_CORE_CONNECTOR_H_

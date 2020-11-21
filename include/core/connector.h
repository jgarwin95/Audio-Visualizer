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

 private:
  const float MAX_DISTANCE = 200;

  int color_ = 255;
  float distance_;
  Node& node1_;
  Node& node2_;
};

} // namespace music_visualizer

#endif //MUSIC_VISUALIZER_SRC_CORE_CONNECTOR_H_

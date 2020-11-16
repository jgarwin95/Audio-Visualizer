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

 private:
  float distance_;
  Node node1_;
  Node node2_;
  float connection_strength_;

};

} // namespace music_visualizer

#endif //MUSIC_VISUALIZER_SRC_CORE_CONNECTOR_H_

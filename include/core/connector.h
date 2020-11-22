//
// Created by garwi on 11/15/2020.
//

#ifndef MUSIC_VISUALIZER_SRC_CORE_CONNECTOR_H_
#define MUSIC_VISUALIZER_SRC_CORE_CONNECTOR_H_

#include "node.h"

namespace music_visualizer {

const float static MAX_CONNECTION_DISTANCE = 300;
const float static MIN_CONNECTION_DISTANCE = 100;

class Connector {

 public:
  Connector(const Node& node1,const Node& node2);
  void Draw();
  void Update();

 private:
  int color_ = 255;
  float distance_;
  const Node& node1_;
  const Node& node2_;
};

} // namespace music_visualizer

#endif //MUSIC_VISUALIZER_SRC_CORE_CONNECTOR_H_

//
// Created by garwi on 11/15/2020.
//

#ifndef MUSIC_VISUALIZER_SRC_CORE_CONTAINER_H_
#define MUSIC_VISUALIZER_SRC_CORE_CONTAINER_H_

#include <vector>
#include <cstdlib>
#include "node.h"
#include "connector.h"

namespace music_visualizer {

class Container {
 public:
  Container(std::vector<Node> nodes);
  Container(int X_dimension, int Y_dimension);

  void Draw();
  void Update();

  const std::vector<Node> &GetNodes() const;
  const std::vector<Connector> &GetConnectors() const;

  void PlaceParticle(Node& node);

 private:
  const size_t NUM_NODES = 50;

  int x_dimension_;
  int y_dimension_;
  std::vector<Node> nodes_;
  std::vector<Connector> connectors_;
  ci::Rectf rect_;

};

} // namespace music_visualizer

#endif //MUSIC_VISUALIZER_SRC_CORE_CONTAINER_H_

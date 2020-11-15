//
// Created by garwi on 11/15/2020.
//

#ifndef MUSIC_VISUALIZER_SRC_CORE_CONTAINER_H_
#define MUSIC_VISUALIZER_SRC_CORE_CONTAINER_H_

#include <vector>
#include "node.h"

namespace music_visualizer {

class Container {
 public:
  Container(int X_dimension, int Y_dimension);

  void Draw();
  void Update();

 private:
  std::vector<Node> nodes_;
  ci::Rectf rect_;

};

}

#endif //MUSIC_VISUALIZER_SRC_CORE_CONTAINER_H_

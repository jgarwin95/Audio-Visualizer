//
// Created by garwi on 11/15/2020.
//

#ifndef MUSIC_VISUALIZER_INCLUDE_CORE_NODE_H_
#define MUSIC_VISUALIZER_INCLUDE_CORE_NODE_H_

#include "cinder/gl/gl.h"

namespace music_visualizer {

class Node {
 public:
  Node();
  Node(const glm::vec2& pos, const glm::vec2& velo, float radius);

  void Draw();
  void Update();
  void AddConnection(Node& other);
  bool isConnected(Node& other);
  const glm::vec2 &GetPos() const;
  const glm::vec2 &GetVelo() const;

  bool operator==(const Node& rhs) const;

 private:
  glm::vec2 pos_;
  glm::vec2 velo_;
  float radius_;
  std::vector<std::reference_wrapper<Node>> connections_;

};

} // namespace music_visualizer

#endif //MUSIC_VISUALIZER_INCLUDE_CORE_NODE_H_

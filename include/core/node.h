//
// Created by garwi on 11/15/2020.
//

#ifndef MUSIC_VISUALIZER_INCLUDE_CORE_NODE_H_
#define MUSIC_VISUALIZER_INCLUDE_CORE_NODE_H_

#include "cinder/gl/gl.h"

namespace music_visualizer {

class Node {
 public:
  /**
   * Construct a node object that floats through space connecting to other nodes
   * @param pos glm::vec2 that denotes spatial positioning
   * @param velo glm::vec2 that denotes velocity
   * @param radius float value for radius of node
   */
  Node(const glm::vec2& pos, const glm::vec2& velo, float radius);
  Node();

  void Draw();
  void Update();

  // Getters & Setters
  const glm::vec2 &GetPos() const;
  const glm::vec2 &GetVelo() const;
  float GetRadius() const;
  void ResetPosition(const glm::vec2 &pos);
  void ResetVelocity(const glm::vec2 &velo);

 private:
  glm::vec2 pos_;
  glm::vec2 velo_;
  float radius_;

};

} // namespace music_visualizer

#endif //MUSIC_VISUALIZER_INCLUDE_CORE_NODE_H_

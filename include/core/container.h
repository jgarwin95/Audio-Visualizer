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
  /**
   * Construct container object from a set list of nodes. Size of container is fixed.
   * Primarily for testing purposes
   * @param nodes
   */
  Container(std::vector<Node> nodes);
  /**
   * Construct a container with NUM_NODES nodes and specified dimensions
   * @param X_dimension size of container in x dimension
   * @param Y_dimension size of container in y dimension
   */
  Container(int X_dimension, int Y_dimension);
  /**
   * Call all draw functionality for objects contained within container
   */
  void Draw();
  /**
   * Update particles and connectors
   */
  void Update(float RMSVolume = 1);

  const std::vector<Node> &GetNodes() const;
  const std::vector<Connector> &GetConnectors() const;
  /**
   * Update node that is assigned to mouse movements
   * @param pos glm::vec2 denoting the current position of the mouse
   */
  void UpdateMouseNode(const glm::vec2& pos);

 private:
  /**
   * Number of nodes to be generating upon construction of a container object
   */
  const size_t NUM_NODES = 50;

  int x_dimension_;
  int y_dimension_;
  std::vector<Node> nodes_;
  Node mouse_node_;
  std::vector<Connector> connectors_;
  ci::Rectf rect_;

};

} // namespace music_visualizer

#endif //MUSIC_VISUALIZER_SRC_CORE_CONTAINER_H_

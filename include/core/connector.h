//
// Created by garwi on 11/15/2020.
//

#ifndef MUSIC_VISUALIZER_SRC_CORE_CONNECTOR_H_
#define MUSIC_VISUALIZER_SRC_CORE_CONNECTOR_H_

#include "node.h"

namespace music_visualizer {

/**
 * maximum distance at which a connection is displayed between nodes
 */
const float static MAX_CONNECTION_DISTANCE = 300;
/**
 * minimum distance at which a connection is displayed between nodes
 */
const float static MIN_CONNECTION_DISTANCE = 100;

class Connector {

 public:
  /**
   * Constructor that creates a connection between two nodes
   * @param node1 first connecting partner
   * @param node2 second connecting partner
   */
  Connector(const Node& node1,const Node& node2);
  /**
   * Draw to screen
   */
  void Draw();
  /**
   * Update distance and the associated connection strength with that distance
   */
  void Update(float volume = 1);
  // Getters & Setters
  int GetColor() const;
  float GetDistance() const;

 private:
  /**
   * Color denotes connection strength. 255 is white while 0 is black (same color as background).
   */
  int color_ = 255;
  float distance_;
  const Node& node1_;
  const Node& node2_;
};

} // namespace music_visualizer

#endif //MUSIC_VISUALIZER_SRC_CORE_CONNECTOR_H_

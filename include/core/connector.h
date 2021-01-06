//
// Created by garwi on 11/15/2020.
//

#ifndef MUSIC_VISUALIZER_SRC_CORE_CONNECTOR_H_
#define MUSIC_VISUALIZER_SRC_CORE_CONNECTOR_H_

#include "node.h"

namespace music_visualizer {

ci::Color8u static CONNECTOR_COLOR = ci::Color8u(255,255,255);

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
  void Update(ci::Color8u &background, float volume = 1);
  // Getters & Setters
  ci::Color8u GetColor() const;
  float GetDistance() const;

  /**
   * Initial update of color sets new baseline shared by all instances
   * @param colors std::vector<int> representing RGB values
   */
  void static ChangeColor(const std::vector<int> &colors);
  /**
   * Update instance colors based on connection distance. Does not affect baseline color
   * @param colors std::vector<int> representing RGB values
   */
  void UpdateColor(const std::vector<int> &colors);

 private:
  ci::Color8u color_ = ci::ColorA8u(255,255,255);
  float distance_;
  const Node& node1_;
  const Node& node2_;
};

} // namespace music_visualizer

#endif //MUSIC_VISUALIZER_SRC_CORE_CONNECTOR_H_

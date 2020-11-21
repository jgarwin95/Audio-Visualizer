//
// Created by garwi on 11/15/2020.
//

#include <catch2/catch.hpp>
#include "core/container.h"

namespace music_visualizer {

TEST_CASE("particle movements", "[movement]") {

  SECTION("spawned particles move from initial position") {
    Container container = Container(200, 200);
    glm::vec2 pos_i = container.GetNodes().at(1).GetPos();
    container.Update();
    glm::vec2 pos_f = container.GetNodes().at(1).GetPos();
    REQUIRE(pos_i != pos_f);
  }

  SECTION("single particle halfway through boundary does not preemptively spawn elsewhere") {
    std::vector<Node> test_nodes;
    test_nodes.emplace_back(glm::vec2(50,4), glm::vec2(0,-4), 4.0f);
    Container container = Container(test_nodes);
    container.Update();
    REQUIRE(container.GetNodes().at(0).GetPos().x == 50);
    REQUIRE(container.GetNodes().at(0).GetPos().y == 0);
  }

  SECTION("single particle fully through boundary still does not spawn elsewhere") {
    std::vector<Node> test_nodes;
    test_nodes.emplace_back(glm::vec2(50,0), glm::vec2(0,-4), 4.0f);
    Container container = Container(test_nodes);
    container.Update();
    REQUIRE(container.GetNodes().at(0).GetPos().x == 50);
    REQUIRE(container.GetNodes().at(0).GetPos().y == -4);
  }

  SECTION("single particle fully through boundary and past 200 connector distance spawns elsewhere") {
    std::vector<Node> test_nodes;
    test_nodes.emplace_back(glm::vec2(50,-200), glm::vec2(0,-4), 4.0f);
    Container container = Container(test_nodes);
    container.Update();
    REQUIRE(container.GetNodes().at(0).GetPos().x != 50);
    REQUIRE(container.GetNodes().at(0).GetPos().y != -204);
  }
}

} // namespace music_visualizer
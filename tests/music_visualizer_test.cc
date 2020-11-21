//
// Created by garwi on 11/15/2020.
//

#include <catch2/catch.hpp>
#include "core/container.h"

namespace music_visualizer {

TEST_CASE("particle movements & boundaries", "[movement][boundaries]") {

  SECTION("spawned particles move from initial position") {
    Container container = Container(200, 200);
    glm::vec2 pos_i = container.GetNodes().at(1).GetPos();
    container.Update();
    glm::vec2 pos_f = container.GetNodes().at(1).GetPos();
    REQUIRE(pos_i != pos_f);
  }

  SECTION("single particle halfway through upper y boundary does not preemptively spawn elsewhere") {
    std::vector<Node> test_nodes;
    test_nodes.emplace_back(glm::vec2(50,4), glm::vec2(0,-4), 4.0f);
    Container container = Container(test_nodes);
    container.Update();
    REQUIRE(container.GetNodes().at(0).GetPos().x == 50);
    REQUIRE(container.GetNodes().at(0).GetPos().y == 0);
  }

  SECTION("single particle fully through upper y boundary but not to limit still does not spawn elsewhere") {
    std::vector<Node> test_nodes;
    test_nodes.emplace_back(glm::vec2(50,0), glm::vec2(0,-4), 4.0f);
    Container container = Container(test_nodes);
    container.Update();
    REQUIRE(container.GetNodes().at(0).GetPos().x == 50);
    REQUIRE(container.GetNodes().at(0).GetPos().y == -4);
  }

  SECTION("single particle fully through upper y boundary and past 200 connector distance spawns elsewhere") {
    std::vector<Node> test_nodes;
    test_nodes.emplace_back(glm::vec2(50,-200), glm::vec2(0,-4), 4.0f);
    Container container = Container(test_nodes);
    container.Update();
    REQUIRE(container.GetNodes().at(0).GetPos().x != 50);
  }

  SECTION("single particle halfway through lower y boundary does not preemptively spawn elsewhere") {
    std::vector<Node> test_nodes;
    test_nodes.emplace_back(glm::vec2(50,196), glm::vec2(0,4), 4.0f);
    Container container = Container(test_nodes);
    container.Update();
    REQUIRE(container.GetNodes().at(0).GetPos().x == 50);
    REQUIRE(container.GetNodes().at(0).GetPos().y == 200);
  }

  SECTION("single particle fully through lower y boundary but not to limit still does not spawn elsewhere") {
    std::vector<Node> test_nodes;
    test_nodes.emplace_back(glm::vec2(50,200), glm::vec2(0,4), 4.0f);
    Container container = Container(test_nodes);
    container.Update();
    REQUIRE(container.GetNodes().at(0).GetPos().x == 50);
    REQUIRE(container.GetNodes().at(0).GetPos().y == 204);
  }

  SECTION("single particle fully through lower y boundary and past 200 connector distance spawns elsewhere") {
    std::vector<Node> test_nodes;
    test_nodes.emplace_back(glm::vec2(50,400), glm::vec2(0,4), 4.0f);
    Container container = Container(test_nodes);
    container.Update();
    REQUIRE(container.GetNodes().at(0).GetPos().x != 50);
  }

  SECTION("single particle halfway through right x boundary does not preemptively spawn elsewhere") {
    std::vector<Node> test_nodes;
    test_nodes.emplace_back(glm::vec2(196, 50), glm::vec2(4,0), 4.0f);
    Container container = Container(test_nodes);
    container.Update();
    REQUIRE(container.GetNodes().at(0).GetPos().x == 200);
    REQUIRE(container.GetNodes().at(0).GetPos().y == 50);
  }

  SECTION("single particle fully through right x boundary but not to limit still does not spawn elsewhere") {
    std::vector<Node> test_nodes;
    test_nodes.emplace_back(glm::vec2(200,50), glm::vec2(4,0), 4.0f);
    Container container = Container(test_nodes);
    container.Update();
    REQUIRE(container.GetNodes().at(0).GetPos().x == 204);
    REQUIRE(container.GetNodes().at(0).GetPos().y == 50);
  }

  SECTION("single particle fully through right x boundary and past 200 connector distance spawns elsewhere") {
    std::vector<Node> test_nodes;
    test_nodes.emplace_back(glm::vec2(400,50), glm::vec2(4,0), 4.0f);
    Container container = Container(test_nodes);
    container.Update();
    REQUIRE(container.GetNodes().at(0).GetPos().y != 50);
  }

  SECTION("single particle halfway through left x boundary does not preemptively spawn elsewhere") {
    std::vector<Node> test_nodes;
    test_nodes.emplace_back(glm::vec2(4,50), glm::vec2(-4,0), 4.0f);
    Container container = Container(test_nodes);
    container.Update();
    REQUIRE(container.GetNodes().at(0).GetPos().x == 0);
    REQUIRE(container.GetNodes().at(0).GetPos().y == 50);
  }

  SECTION("single particle fully through left x boundary but not to limit still does not spawn elsewhere") {
    std::vector<Node> test_nodes;
    test_nodes.emplace_back(glm::vec2(0,50), glm::vec2(-4,0), 4.0f);
    Container container = Container(test_nodes);
    container.Update();
    REQUIRE(container.GetNodes().at(0).GetPos().x == -4);
    REQUIRE(container.GetNodes().at(0).GetPos().y == 50);
  }

  SECTION("single particle fully through left x boundary and past 200 connector distance spawns elsewhere") {
    std::vector<Node> test_nodes;
    test_nodes.emplace_back(glm::vec2(-200,50), glm::vec2(-4,0), 4.0f);
    Container container = Container(test_nodes);
    container.Update();
    CHECK((container.GetNodes().at(0).GetPos().y != 50));

  }
}

//TODO:: 1. test connections 2. connection strength and scaling

} // namespace music_visualizer
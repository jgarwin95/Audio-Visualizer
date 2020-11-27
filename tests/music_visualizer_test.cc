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
    test_nodes.emplace_back(glm::vec2(50,-MAX_CONNECTION_DISTANCE), glm::vec2(0,-4), 4.0f);
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
    test_nodes.emplace_back(glm::vec2(50,200 + MAX_CONNECTION_DISTANCE), glm::vec2(0,4), 4.0f);
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
    test_nodes.emplace_back(glm::vec2(200 + MAX_CONNECTION_DISTANCE,50), glm::vec2(4,0), 4.0f);
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
    test_nodes.emplace_back(glm::vec2(-MAX_CONNECTION_DISTANCE,50), glm::vec2(-4,0), 4.0f);
    Container container = Container(test_nodes);
    container.Update();
    CHECK((container.GetNodes().at(0).GetPos().y != 50));
  }
}

TEST_CASE("Connectors", "[connectors]") {
  SECTION("Connection formed between two particles") {
    std::vector<Node> test_nodes;
    test_nodes.emplace_back(glm::vec2(50,50), glm::vec2(-4,0), 4.0f);
    test_nodes.emplace_back(glm::vec2(60,60), glm::vec2(-4,0), 4.0f);
    Container container = Container(test_nodes);
    REQUIRE(container.GetConnectors().size() == 1);
  }

  SECTION("Connection scales at particles move apart") {
    std::vector<Node> test_nodes;
    test_nodes.emplace_back(glm::vec2(50,50), glm::vec2(-4,0), 4.0f);
    test_nodes.emplace_back(glm::vec2(60,50), glm::vec2(4,0), 4.0f);
    Container container = Container(test_nodes);
    float dist1 = container.GetConnectors().at(0).GetDistance();
    container.Update();
    float dist2 = container.GetConnectors().at(0).GetDistance();
    REQUIRE(dist2 != dist1);
  }

  SECTION("Connection strength is full at minimum required distance") {
    std::vector<Node> test_nodes;
    test_nodes.emplace_back(glm::vec2(50,50), glm::vec2(0,0), 4.0f);
    test_nodes.emplace_back(glm::vec2(50 + MIN_CONNECTION_DISTANCE,50), glm::vec2(0,0), 4.0f);
    Container container = Container(test_nodes);
    container.Update();
    REQUIRE(container.GetConnectors().at(0).GetColor() == 255);
  }

  SECTION("Connection strength is less than full at some distance more than min and less than max") {
    std::vector<Node> test_nodes;
    test_nodes.emplace_back(glm::vec2(50,50), glm::vec2(0,0), 4.0f);
    test_nodes.emplace_back(glm::vec2(50 + MIN_CONNECTION_DISTANCE + 5,50), glm::vec2(0,0), 4.0f);
    Container container = Container(test_nodes);
    container.Update();
    REQUIRE(container.GetConnectors().at(0).GetColor() < 255);
  }

  SECTION("Connection strength is 0 at max distance") {
    std::vector<Node> test_nodes;
    test_nodes.emplace_back(glm::vec2(50,50), glm::vec2(0,0), 4.0f);
    test_nodes.emplace_back(glm::vec2(50 + MAX_CONNECTION_DISTANCE,50), glm::vec2(0,0), 4.0f);
    Container container = Container(test_nodes);
    container.Update();
    REQUIRE(container.GetConnectors().at(0).GetColor() == 0);
  }

  SECTION("Connection strength is 0 at greater than max distance") {
    std::vector<Node> test_nodes;
    test_nodes.emplace_back(glm::vec2(50,50), glm::vec2(0,0), 4.0f);
    test_nodes.emplace_back(glm::vec2(50 + MAX_CONNECTION_DISTANCE + 5,50), glm::vec2(0,0), 4.0f);
    Container container = Container(test_nodes);
    container.Update();
    REQUIRE(container.GetConnectors().at(0).GetColor() == 0);
  }


}

} // namespace music_visualizer
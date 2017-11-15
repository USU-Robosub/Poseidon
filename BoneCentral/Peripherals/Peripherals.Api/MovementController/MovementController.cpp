#include "MovementController.hpp"

RoutingTable MovementController::getRoutes() {
  auto table = RoutingTable();
  table["set-position"] = [&](json params){ setPosition(params); }
  table["set-orientation"] = [&](json params) { setOrientation(params); }
  return table;
}

void MovementController::setPosition(json params) {
  // Use other objects to control position
}

void MovementController::setOrientation(json params) {
  // Use other objects to control orientation
}

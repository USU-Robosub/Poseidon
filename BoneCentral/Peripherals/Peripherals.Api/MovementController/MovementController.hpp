#include "../IController.hpp"

class MovementController {
public:
  void RoutingTable getRoutes();
  void setPosition(json params);
  void setOrientation(json params);
};

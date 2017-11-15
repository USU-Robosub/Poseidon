#include <map>
#include <functional>
#include <json.h>
using json = nlohmann::json;

typedef std::std::map<std::string, std::function<void(json)>> RoutingTable

class IController {
private:
  IController() {}
public:
  RoutingTable getRoutes() = 0;
};

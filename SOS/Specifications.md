# SOS

SOS is designed to be a simple way to connect different devices and languages together for use in the USU Robosub Team's robots.

## Hubs

Hubs are capable of communicating with other hubs. Using different connection types, hubs are able to create networks not easily possible by traditional solutions.

#### Naming a hub

In a network, each hub requires a name. A hub's name can be anything, but it must be unique.

## Nodes

Nodes are resources exposed to the network. Each node is hosted by a hub, and is invoked to process every message received by the hub. Additionally, nodes can use its host hub to send messages to other nodes.

#### Naming a node

In a network, each node is designated by its name. A hub's name can be anything, but it must be unique.

## C++ Basic Example

```C++
// main.cpp
int main() {

  Hub app("Example");

  SOS sos(true); // create SOS master [true = master, false = normal]
  sos.mountTo(&app);

  // custom setup for hub

  Sensor sensor;
  app.use("Sensor", &sensor);

  WebSocket websocket(1234);
  app.connect("Website", &websocket);

  // ===

  app.listen(); // starts app

  return 0;
}
```

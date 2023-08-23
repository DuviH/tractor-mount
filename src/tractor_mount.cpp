
#include "common.hpp"
#include "TractorImplement.hpp"
#include "server.hpp"


ImplementsServer server;

void setup() {
  server.begin();
}


void loop() {

  server.get_command();

}

#include <cstdio>

#include <glm/glm.hpp>
#include <ld55/engine.h>
#include <ld55/service_locator.h>

int main() {
  printf("Hello, world!\n");
  ld55::Engine::Init("ld55.can");

  ld55::ServiceLocator::GetWindow()->Open();
  bool should_close = false;
  while (!should_close) {
    should_close = ld55::ServiceLocator::GetWindow()->HandleEvents();
  }
}
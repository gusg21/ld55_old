#include "ld55/engine.h"

#include <cstdio>

#include <ld55/service_locator.h>

#include "platform/sdl_window.h"
#include "ld55/assets.h"

using namespace ld55;

void Engine::Init(const std::string& can_file) { 
    printf("Creating window...");
    ServiceLocator::Provide(new SDLWindow());
    ServiceLocator::Provide(new Assets(can_file));
 }
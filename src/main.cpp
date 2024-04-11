#include <ld55/engine.h>
#include <ld55/service_locator.h>
#include <ld55/texture.h>

#include <cstdio>
#include <glm/glm.hpp>

using namespace ld55;

int main() {
  printf("Hello, world!\n");
  Engine::Init("ld55.can");
  ServiceLocator::GetWindow()->Open();

//  const AssetHandle* barnHandle =
//      ServiceLocator::GetAssets()->FindAssetHandle("barn.png");
//  Texture tex(
//      ServiceLocator::GetAssets()->GetAssetData(barnHandle));

  const AssetHandle* fragHandle =
      ServiceLocator::GetAssets()->FindAssetHandle("sprite.frag");
  const AssetHandle* vertHandle =
      ServiceLocator::GetAssets()->FindAssetHandle("sprite.vert");
  Shader shader = ServiceLocator::GetRenderer()->CreateShader(
      reinterpret_cast<const char*>(
          ServiceLocator::GetAssets()->GetAssetData(vertHandle)),
      reinterpret_cast<const char*>(
          ServiceLocator::GetAssets()->GetAssetData(fragHandle)));
  shader.use();
  //tex.bindToTextureUnit(0);

  bool should_close = false;
  while (!should_close) {
    should_close = ServiceLocator::GetWindow()->HandleEvents();
  }
}
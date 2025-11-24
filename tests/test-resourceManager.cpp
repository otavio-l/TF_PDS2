#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "resourceManager.hpp"

TEST_CASE("resourceManager - carregar e obter textura") {
    ResourceManager resourceManager;

    CHECK_NOTHROW(resourceManager.loadTexture("menuNew"));

    CHECK_NOTHROW(resourceManager.getTexture("menuNew"));
}

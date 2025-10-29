#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "resourceManager.hpp"

TEST_CASE("resourceManager - carregar e obter textura") {
    ResourceManager resourceManager;

    CHECK_NOTHROW(resourceManager.loadTexture("testTexture", "textura.png"));

    CHECK_NOTHROW(resourceManager.getTexture("testTexture"));
}

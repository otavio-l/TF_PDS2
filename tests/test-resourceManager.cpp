#include "doctest.h"

#include "resourceManager.hpp"

TEST_CASE("resourceManager - carregar e obter textura") {
    ResourceManager resourceManager;

    CHECK_NOTHROW(resourceManager.loadTexture("menuNew"));

    CHECK_NOTHROW(resourceManager.getTexture("menuNew"));
}

TEST_CASE("resourceManager - obter textura nao carregada") {
    ResourceManager resourceManager;

    CHECK_THROWS_AS(resourceManager.getTexture("nonExistentTexture"), 
        std::runtime_error);
}

TEST_CASE("resourceManager - carregar textura inexistente") {
    ResourceManager resourceManager;

    CHECK_THROWS_AS(resourceManager.loadTexture("nonExistentFile"), 
        std::runtime_error);
}

TEST_CASE("resourceManager - obter áudio nao carregada") {
    ResourceManager resourceManager;

    CHECK_THROWS_AS(resourceManager.getSound("nonExistentSound"), 
        std::runtime_error);
}

TEST_CASE("resourceManager - carregar áudio inexistente") {
    ResourceManager resourceManager;

    CHECK_THROWS_AS(resourceManager.loadSound("nonExistentFile"), 
        std::runtime_error);
}

TEST_CASE("resourceManager - obter fonte nao carregada") {
    ResourceManager resourceManager;

    CHECK_THROWS_AS(resourceManager.getFont("nonExistentFont"), 
        std::runtime_error);
}

TEST_CASE("resourceManager - carregar fonte inexistente") {
    ResourceManager resourceManager;

    CHECK_THROWS_AS(resourceManager.loadFont("nonExistentFile"), 
        std::runtime_error);
}
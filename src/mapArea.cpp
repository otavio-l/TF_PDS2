// # define NDEBUG
constexpr float SPAWN_FLAG = 1337.0f;


#include "mapArea.hpp"
#include <array>
#include <fstream>
#include <cassert>
#include <climits>
#include <cmath>
#include "constants.hpp"


static const std::array<std::string, 10> jsonLookup = {
    "maps/1x1.json",
    "maps/1x2.json",
    "maps/1x3.json",
    "maps/2x1.json",
    "maps/2x2.json",
    "maps/2x3.json",
    "maps/3x1.json",
    "maps/3x2.json",
    "maps/3x3.json",
    "maps/church.json"
};

static std::array<std::string, 4> expectedWalls = {
    "left-wall", "right-wall", "up-wall", "down-wall"
};


MapArea::MapArea(LiveEntity &mainCharacter, ResourceManager& rM, int checkpoint) : rM(rM), 
    mainCharacter(mainCharacter), checkpoint(checkpoint) {}

void MapArea::newMap(int targetMap, std::string currentSpawn) {
    mapEntities.clear();

    mapData.clear();
    mapData = loadJson(jsonLookup[(long unsigned int)targetMap]);
    loadCurrentSpawn(targetMap, currentSpawn);
    loadBackground();
    loadWalls();
    loadmapEntities();
}

nlohmann::json MapArea::loadJson(std::string jsonFile)  {
    std::ifstream file(jsonFile);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open map file");
    }
    nlohmann::json j;
    file >> j;
    file.close();
    return j;
}

void MapArea::loadCurrentSpawn(int targetMap, std::string targetSpawn) {
    // define default spawn coordinates if not specified in json
    assert (mapData["spawn"].contains(targetSpawn));
    assert (SPAWN_FLAG > (constants::xLogicPixels * 4));

    float absoluteX = mapData["spawn"][targetSpawn].value("x", SPAWN_FLAG);
    float absoluteY = mapData["spawn"][targetSpawn].value("y", SPAWN_FLAG);

    if (absoluteX == SPAWN_FLAG) {
        // it doens't work for church.json, it's outside main map;
        int screenX {targetMap / 3};
        int screenY {targetMap % 3};
        float offsetX {static_cast<float>(constants::xLogicPixels * screenY)};
        float offsetY {static_cast<float>(constants::yLogicPixels * screenX)};

        if (targetSpawn == "left") {
            absoluteX = 1.0f + offsetX;
            absoluteY = 70.0f + offsetY;
        }
        else if (targetSpawn == "right") {
            absoluteX = 183.0f + offsetX;
            absoluteY = 60.0f + offsetY;
        }
        else if (targetSpawn == "up") {
            absoluteX = 90.0f + offsetX;
            absoluteY = 1.0f + offsetY;
        }
        else if (targetSpawn == "down") {
            absoluteX = 90.0f + offsetX;
            absoluteY = 138.0f + offsetY;
        }
        else {
            throw std::runtime_error("Unspecified map spawn");
        }
    }

    mainCharacter.absX = absoluteX;
    mainCharacter.absY = absoluteY;

    float relativeX { fmodf( absoluteX , constants::xLogicPixels ) };
    float relativeY { fmodf( absoluteY , constants::yLogicPixels ) };
    mainCharacter.drawable.setPosition(relativeX, relativeY);
    mainCharacter.hitbox.setPosition(relativeX, relativeY);
}

void MapArea::loadBackground() {
    std::string background = mapData.value("background", "");
    if (!background.empty()) {
        MapEntity ent;
        ent.drawable.setTexture(rM.getTexture(background));
        ent.drawable.setPosition(0, 0);
        ent.hasTexture = true;
        ent.hasCollision = false;
        ent.hasTrigger = false;
        mapEntities.push_back(ent);
    }
}

bool MapArea::checkLifespan(const nlohmann::json_abi_v3_12_0::json& ent) {
    /*
    0: intro cutscene and church;
    1: outside church gameplay;
    3: end, player took all crucifixes
    */

    if (!ent.contains("checkpoint")) return true;

    int min {ent["checkpoint"].value("min", INT_MIN)};
    int max {ent["checkpoint"].value("max", INT_MAX)};

    if ((min <= checkpoint) && (checkpoint <= max)) return true;
    else return false;
}

void MapArea::loadWalls() {
    // create expectedWalls with default values if not specified by
    if (!mapData.contains("walls")) return;

    nlohmann::json defaulWalls = loadJson("maps/walls.json");

    const auto& customWalls = mapData["walls"];

    for (auto& currentWall : expectedWalls) {
        auto& hitbox {defaulWalls[currentWall]["hitbox"]};
        MapEntity ent;
        ent.hasCollision = true;
        ent.hasTexture = false;
        ent.hasTrigger = false;
        
        if (customWalls.contains(currentWall)) {
            if (customWalls[currentWall].contains("hitbox")) {
                hitbox = customWalls[currentWall]["hitbox"];
            }
            if (customWalls[currentWall].contains("trigger")) {
                ent.hasTrigger = true;
                ent.trigger.type = customWalls[currentWall]["trigger"].value("type", TriggerType::NONE);
                ent.trigger.targetMap = customWalls[currentWall]["trigger"].value("targetMap", 0);
                ent.trigger.targetSpawn = customWalls[currentWall]["trigger"].value("targetSpawn", "");
            }
        }

        float x = hitbox.value("x", 0.0f);
        float y = hitbox.value("y", 0.0f);
        float width = hitbox.value("width", 0.0f);
        float height = hitbox.value("height", 0.0f);
        ent.hitbox.setPosition(x, y);
        ent.hitbox.setSize({width, height});

        mapEntities.push_back(ent);
    }
}

void MapArea::loadmapEntities() {
    assert (mapData.contains("mapEntities"));

    for (const auto& e : mapData["mapEntities"]) {
        MapEntity ent;

        if (!checkLifespan(e)) continue;

        ent.hasTexture = e.contains("sprite");
        if (ent.hasTexture) {
            const auto& sp = e["sprite"];
            float x = sp.value("x", 0.0f);
            float y = sp.value("y", 0.0f);
            ent.drawable.setPosition(x, y);

            std::string texture = sp.value("texture", "");
            sf::Texture& t = rM.getTexture(texture);
            ent.drawable.setTexture(t);
        }
        
        ent.hasTrigger = e.contains("trigger");
        if (ent.hasTrigger) {
            const auto& tr = e["trigger"];
            ent.trigger.type = tr.value("type", TriggerType::NONE);
            ent.trigger.targetMap = tr.value("targetMap", 0);
            ent.trigger.targetSpawn = tr.value("targetSpawn", "");
        }

        ent.hasCollision = e.contains("hitbox");
        if (ent.hasCollision) {

            const auto& hb = e["hitbox"];
            float left = hb.value("x", 0.0f);
            float top = hb.value("y", 0.0f);
            float width = hb.value("width", 0.0f);
            float height = hb.value("height", 0.0f);

            ent.hitbox.setPosition(left, top);
            ent.hitbox.setSize({width, height});
        }
        //TODO: Unitialized texture, always assert "hasTexture" first
        //TODO: Unitialized targetMap and targetSpawn, assert "hasTrigger" first
        //TODO: Unitialized hitbox, assert "hasCollision" first

        mapEntities.push_back(ent);
    }
}

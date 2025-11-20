// # define NDEBUG
constexpr float SPAWN_FLAG = 1337.0f;


#include "mapArea.hpp"
#include <fstream>
#include <cassert>
#include <climits>


MapArea::MapArea(Entity &mainCharacter, ResourceManager& rM, int checkpoint) : rM(rM), 
    mainCharacter(mainCharacter), checkpoint(checkpoint) {}

void MapArea::newMap(std::string jsonFile, std::string currentSpawn) {
    mapEntities.clear();

    mapData.clear();
    mapData = loadJson(jsonFile);
    loadCurrentSpawn(currentSpawn);
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

void MapArea::loadCurrentSpawn(std::string targetSpawn) {
    assert (mapData["spawn"].contains(targetSpawn));

    float x = mapData["spawn"][targetSpawn].value("x", SPAWN_FLAG);
    float y = mapData["spawn"][targetSpawn].value("y", SPAWN_FLAG);

    if (x == SPAWN_FLAG) {
        if (targetSpawn == "left") {
            x = 1.0f;
            y = 70.0f;
        }
        else if (targetSpawn == "right") {
            x = 183.0f;
            y = 60.0f;
        }
        else if (targetSpawn == "up") {
            x = 90.0f;
            y = 1.0f;
        }
        else if (targetSpawn == "down") {
            x = 90.0f;
            y = 138.0f;
        }
        else {
            throw std::runtime_error("Unspecified map spawn");
        }
    }

    mainCharacter.drawable.setPosition(x, y);
    mainCharacter.hitbox.setPosition(x, y);
}

void MapArea::loadBackground() {
    std::string background = mapData.value("background", "");
    if (!background.empty()) {
        Entity ent;
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
    if (!mapData.contains("walls")) return;

    nlohmann::json defaulWalls = loadJson("maps/walls.json");

    std::array<std::string, 4> walls = {"left-wall", "right-wall", "up-wall", "down-wall"};
    const auto& customWalls = mapData["walls"];

    for (auto& currentWall : walls) {
        auto& hitbox {defaulWalls[currentWall]["hitbox"]};
        Entity ent;
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
                ent.trigger.targetMap = customWalls[currentWall]["trigger"].value("targetMap", "");
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
        Entity ent;

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
            ent.trigger.targetMap = tr.value("targetMap", "");
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

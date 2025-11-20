// # define NDEBUG


#include "mapArea.hpp"
#include <fstream>
#include <cassert>
#include <climits>


MapArea::MapArea(Entity &mainCharacter, ResourceManager& rM, int checkpoint) : rM(rM), 
    mainCharacter(mainCharacter), checkpoint(checkpoint) {}

void MapArea::newMap(std::string jsonFile, std::string currentSpawn) {
    mapEntities.clear();

    mapData.clear();
    loadJson(jsonFile);
    loadCurrentSpawn(currentSpawn);
    loadBackground();
    loadmapEntities();
}

void MapArea::loadJson(std::string jsonFile)  {
    std::ifstream file(jsonFile);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open map file");
    }
    file >> mapData;
    file.close(); // TODO: Maybe error closing before necessary
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

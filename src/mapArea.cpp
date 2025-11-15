// # define NDEBUG


#include <fstream>
#include <cassert>
#include "mapArea.hpp"


MapArea::MapArea(Entity &mainCharacter, ResourceManager& rM) : rM(rM), 
    mainCharacter(mainCharacter) {}

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

    float x = mapData["spawn"][targetSpawn]["x"];
    float y = mapData["spawn"][targetSpawn]["y"];
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

void MapArea::loadmapEntities() {
    assert (mapData.contains("mapEntities"));

    for (const auto& e : mapData["mapEntities"]) {
        Entity ent;

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
            ent.trigger.type = tr.value("type", "");
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

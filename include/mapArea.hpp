#ifndef PARSER_HPP
#define PARSER_HPP


#include <nlohmann/json.hpp>
#include "resourceManager.hpp"
#include "entity.hpp"


class MapArea {
public:
    // std::string jsonFile;
    nlohmann::json mapData;
    std::vector<Entity> mapEntities;
    ResourceManager &rM;
    // std::string currentSpawn;
    Entity &mainCharacter;
    int checkpoint;

    MapArea(Entity &mainCharacter, ResourceManager &rM, int checkpoint);

    void newMap(std::string jsonFile, std::string currentSpawn);

    void loadJson(std::string jsonFile);

    void loadCurrentSpawn(std::string targetSpawn);

    void loadBackground();

    void loadmapEntities();

    bool checkLifespan(const nlohmann::json_abi_v3_12_0::json& ent);
};

#endif

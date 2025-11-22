#ifndef PARSER_HPP
#define PARSER_HPP


#include <nlohmann/json.hpp>
#include "resourceManager.hpp"
#include "entity.hpp"


class MapArea {
public:
    // std::string jsonFile;
    nlohmann::json mapData;
    std::vector<MapEntity> mapEntities;
    ResourceManager &rM;
    // std::string currentSpawn;
    LiveEntity &mainCharacter;
    int checkpoint;

    MapArea(LiveEntity &mainCharacter, ResourceManager &rM, int checkpoint);

    void newMap(int targetMap, std::string currentSpawn);

    nlohmann::json loadJson(std::string jsonFile);

    void loadCurrentSpawn(int targetMap, std::string targetSpawn);

    void loadBackground();

    void loadmapEntities();

    bool checkLifespan(const nlohmann::json_abi_v3_12_0::json& ent);

    void loadWalls();
};

#endif

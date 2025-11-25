#ifndef PARSER_HPP
#define PARSER_HPP


#include <nlohmann/json.hpp>
#include "resourceManager.hpp"
#include "entity.hpp"


/**
 * @brief Gerencia o mapa atual
 * 
 */
class MapArea {
private:
    ResourceManager &rM;
    nlohmann::json mapData;
    LiveEntity &mainCharacter;

    /**
     * @brief Cria o objeto json
     * 
     * @param jsonFile Arquivo a ser lido
     * @return nlohmann::json Objeto json
     */
    nlohmann::json loadJson(std::string jsonFile);

    /**
     * @brief Define as posiçãoes iniciais do player em um mapa
     * 
     * @param targetMap Próximo mapa
     * @param targetSpawn Spawn no proximo mapa
     */
    void loadCurrentSpawn(int targetMap, std::string targetSpawn);

    /**
     * @brief Carrega o backgroung de mapas internos
     * 
     */
    void loadBackground();

    /**
     * @brief Extrai as entidades do mapa do json
     * 
     */
    void loadmapEntities();

    /**
     * @brief Checa se a entidade vai ser extraida de acordo com o checkpoint
     * 
     * @param ent Entidade analisada
     * @return true Entidade será extrída
     * @return false Entidade não será extrída
     */
    bool checkLifespan(const nlohmann::json_abi_v3_12_0::json& ent);

    /**
     * @brief Extrai limites padrões para o mapa
     * 
     */
    void loadWalls();
public:
    std::vector<MapEntity> mapEntities;
    int checkpoint;

    MapArea(LiveEntity &mainCharacter, ResourceManager &rM, int checkpoint);

    /**
     * @brief 
     * 
     * @param targetMap 
     * @param currentSpawn 
     */
    void newMap(int targetMap, std::string currentSpawn);
};

#endif

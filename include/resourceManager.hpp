#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/**
* @brief Carrega e gerencia recursos do jogo, como texturas, fontes e sons.
*/
class ResourceManager {
    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, sf::Font> fonts;
    std::unordered_map<std::string, sf::SoundBuffer> sounds;

public:
    /**
    * @brief Carrega uma textura de um arquivo
    * @param filename nome do arquivo
    */
    void loadTexture(const std::string& filename);
    
    /**
    * @brief Retorna uma textura carregada anteriormente
    * @param name Identificador da textura
    */   
    sf::Texture& getTexture(const std::string& name);
};

#endif

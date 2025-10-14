#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class ResourceManager {
    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, sf::Font> fonts;
    std::unordered_map<std::string, sf::SoundBuffer> sounds;

public:
    void loadTexture(const std::string& name, const std::string& filename);
    sf::Texture& getTexture(const std::string& name);
};

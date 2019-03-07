#ifndef TEXTURES_H
#define TEXTURES_H

#include<SFML/Graphics.hpp>
#include<map>

class Textures
{
public:
    std::map<std::string, sf::Texture> loadedTextures;

    void loadTexture(std::string path, std::string name);
};

#endif // TEXTURES_H

#include "Textures.h"

void Textures::loadTexture(std::string path, std::string name)
{
    if (this->loadedTextures.find(path) == this->loadedTextures.end())
    {
        sf::Texture t;
        t.setSmooth(true);
        t.loadFromFile(path);
        (this->loadedTextures)[name] = t;
    }
}

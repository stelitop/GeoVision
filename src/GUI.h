#ifndef GUI_H
#define GUI_H

#include<SFML/Graphics.hpp>

#include"Enums.h"

using namespace sf;

class Hitbox
{
public:
    Vector2f pos, sz;
    int layer = 0;

    Hitbox();
    Hitbox(Vector2f pos, Vector2f sz);
    Hitbox(double left, double up, double width, double height);
    Hitbox(Vector2f pos, Vector2f sz, int layer);
    Hitbox(double left, double up, double width, double height, int layer);

    bool isPointInside(double x, double y);
    void drawOutline(RenderWindow * window);
};


class Button
{
public:
    std::string name;
    std::string texturePath, textureName;
    int layer = 0;
    Hitbox hitbox;

    geometricToolSelected tool = NO_TOOL;

    Button();
    Button(std::string name, Hitbox hitbox);
    Button(std::string name, Hitbox hitbox, int layer);
    Button(std::string name, Hitbox hitbox, int layer, std::string textureName, std::string texturePath);
};

class Menu
{
public:
    std::string name, textureName;
    std::vector<Button> buttons;
    int layer=0;
    Hitbox hitbox;

    Menu();
    Menu(std::string name, Hitbox hitbox, int layer);
};

int clickedMenu(double mouseX, double mouseY, std::vector<Menu> * menus);
std::pair<int, int> clickedButton(double mouseX, double mouseY, std::vector<Menu> * menus);

#endif // GUI_H

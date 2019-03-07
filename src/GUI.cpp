#include "GUI.h"

Hitbox::Hitbox()
{
    *this = Hitbox(Vector2f(0, 0), Vector2f(0, 0), 0);
}
Hitbox::Hitbox(Vector2f pos, Vector2f sz)
{
    *this = Hitbox(pos, sz, 0);
}
Hitbox::Hitbox(double left, double up, double width, double height)
{
    *this = Hitbox(left, up, width, height, 0);
}
Hitbox::Hitbox(Vector2f pos, Vector2f sz, int layer)
{
    this->pos = pos;
    this->sz = sz;
    this->layer = layer;
}
Hitbox::Hitbox(double left, double up, double width, double height, int layer)
{
    this->pos.x = left;
    this->pos.y = up;
    this->sz.x = width;
    this->sz.y = height;
    this->layer = layer;
}
bool Hitbox::isPointInside(double x, double y)
{
    if (this->pos.x <= x && x <= this->pos.x + this->sz.x && this->pos.y <= y && y <= this->pos.y + this->sz.y) return true;
    return false;
}
void Hitbox::drawOutline(RenderWindow * window)
{
    VertexArray v(LineStrip, 5);
    for (int i=0; i<5; i++) v[i].color = Color::White;
    v[0].position = this->pos;
    v[1].position = this->pos + Vector2f(this->sz.x, 0);
    v[2].position = this->pos + this->sz;
    v[3].position = this->pos + Vector2f(0, this->sz.y);
    v[4].position = this->pos;
    window->draw(v);
}

Button::Button()
{
    *this = Button("", Hitbox(), 0, "", "");
}
Button::Button(std::string name, Hitbox hitbox)
{
    *this = Button(name, hitbox, 0, "", "");
}
Button::Button(std::string name, Hitbox hitbox, int layer)
{
    *this = Button(name, hitbox, layer, "", "");
}
Button::Button(std::string name, Hitbox hitbox, int layer, std::string textureName, std::string texturePath)
{
    this->name = name;
    this->hitbox = hitbox;
    this->layer = layer;
    this->textureName = textureName;
    this->texturePath = texturePath;
}

Menu::Menu()
{
    *this = Menu("", Hitbox(), 0);
}
Menu::Menu(std::string name, Hitbox hitbox, int layer)
{
    this->name = name;
    this->layer = layer;
    this->hitbox = hitbox;
}

int clickedMenu(double mouseX, double mouseY, std::vector<Menu> * menus)
{
    int ret = -1, bestLayer = -INT_MAX;
    for (int i=0; i<menus->size(); i++)
    {
        if ((*menus)[i].hitbox.isPointInside(mouseX, mouseY))
        {
            if ((*menus)[i].layer > bestLayer)
            {
                ret = i;
                bestLayer = (*menus)[i].layer;
            }
        }
    }
    return ret;
}
std::pair<int, int> clickedButton(double mouseX, double mouseY, std::vector<Menu> * menus)
{
    std::pair<int, int> ret(-1, -1);
    int bestLayer = -INT_MAX;
    for (int i=0; i<menus->size(); i++)
    {
        if ((*menus)[i].hitbox.isPointInside(mouseX, mouseY))
        {
            if ((*menus)[i].layer > bestLayer)
            {
                ret.first = i;
                bestLayer = (*menus)[i].layer;
            }
        }
    }
    if (ret.first == -1) return ret;
    bestLayer = -INT_MAX;
    for (int i=0; i<(*menus)[ret.first].buttons.size(); i++)
    {
        if ((*menus)[ret.first].buttons[i].hitbox.isPointInside(mouseX, mouseY))
        {
            if ((*menus)[ret.first].buttons[i].layer > bestLayer)
            {
                ret.second = i;
                bestLayer = (*menus)[ret.first].buttons[i].layer;
            }
        }
    }
    return ret;
}

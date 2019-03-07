#include<iostream>
#include<SFML/Graphics.hpp>
#include<vector>
#include<map>

#include"Geometry.h"
#include"Rendering.h"
#include"GMColors.h"
#include"DynamicalShapeData.h"
#include"Enums.h"
#include"DistanceToMouse.h"
#include"MemoryManagement.h"
#include"DynamicToStatic.h"
#include"RenderingDynamicObjects.h"
#include"UpdateRelativePoints.h"
#include"GUI.h"
#include"Textures.h"
#include"ObjectPreview.h"
#include"DeleteObject.h"

using namespace std;
using namespace GM;
using namespace sf;

const double RECOGNISABLE_DISTANCE = 8;
const double DEFAULT_THICKNESS = 1;

void setMenusPosition(RenderWindow * window, vector<Menu> * menus)
{
    double windowX = window->getSize().x, windowY = window->getSize().y;
    (*menus)[0].hitbox = Hitbox(0, 0, windowX*15/100, windowY);
    (*menus)[0].buttons[0].hitbox = Hitbox(windowX*1/100, windowX*1/100, windowX*6/100, windowX*6/100);
    (*menus)[0].buttons[1].hitbox = Hitbox(windowX*8/100, windowX*1/100, windowX*6/100, windowX*6/100);
    (*menus)[0].buttons[2].hitbox = Hitbox(windowX*1/100, windowX*1/100 + windowX*7/100, windowX*6/100, windowX*6/100);
    (*menus)[0].buttons[3].hitbox = Hitbox(windowX*8/100, windowX*1/100 + windowX*7/100, windowX*6/100, windowX*6/100);
    (*menus)[0].buttons[4].hitbox = Hitbox(windowX*1/100, windowX*1/100 + windowX*14/100, windowX*6/100, windowX*6/100);
    (*menus)[0].buttons[5].hitbox = Hitbox(windowX*8/100, windowX*1/100 + windowX*14/100, windowX*6/100, windowX*6/100);
    (*menus)[0].buttons[6].hitbox = Hitbox(windowX*1/100, windowX*1/100 + windowX*21/100, windowX*6/100, windowX*6/100);
    (*menus)[0].buttons[7].hitbox = Hitbox(windowX*8/100, windowX*1/100 + windowX*21/100, windowX*6/100, windowX*6/100);
    (*menus)[0].buttons[8].hitbox = Hitbox(windowX*1/100, windowX*1/100 + windowX*28/100, windowX*6/100, windowX*6/100);
    (*menus)[0].buttons[9].hitbox = Hitbox(windowX*8/100, windowX*1/100 + windowX*28/100, windowX*6/100, windowX*6/100);
    (*menus)[0].buttons[10].hitbox = Hitbox(windowX*1/100, windowX*1/100 + windowX*35/100, windowX*6/100, windowX*6/100);
    (*menus)[0].buttons[11].hitbox = Hitbox(windowX*8/100, windowX*1/100 + windowX*35/100, windowX*6/100, windowX*6/100);
}

void init(RenderWindow * window, vector<Menu> * menus)
{
    double windowX = window->getSize().x, windowY = window->getSize().y;
    menus->emplace_back("MainTools", Hitbox(0, 0, windowX*15/100, windowY), 0);
    (*menus)[0].buttons.emplace_back("ToolMove", Hitbox(windowX*1/100, windowX*1/100, windowX*6/100, windowX*6/100), 1, "ToolMove", "textures/ToolMove.png");
    (*menus)[0].buttons.emplace_back("ToolCreatePoint", Hitbox(windowX*8/100, windowX*1/100, windowX*6/100, windowX*6/100), 1, "CreatePoint", "textures/ToolCreatePoint.png");
    (*menus)[0].buttons.emplace_back("ToolCreateSegment", Hitbox(windowX*1/100, windowX*1/100 + windowX*7/100, windowX*6/100, windowX*6/100), 1, "CreateSegment", "textures/ToolCreateSegment.png");
    (*menus)[0].buttons.emplace_back("ToolCreateLine", Hitbox(windowX*8/100, windowX*1/100 + windowX*7/100, windowX*6/100, windowX*6/100), 1, "CreateLine", "textures/ToolCreateLine.png");
    (*menus)[0].buttons.emplace_back("ToolCreateCircleDB2", Hitbox(windowX*1/100, windowX*1/100 + windowX*14/100, windowX*6/100, windowX*6/100), 1, "CreateCircleDB2", "textures/ToolCreateCircleDB2.png");
    (*menus)[0].buttons.emplace_back("ToolCreateCircleDB3", Hitbox(windowX*8/100, windowX*1/100 + windowX*14/100, windowX*6/100, windowX*6/100), 1, "CreateCircleDB3", "textures/ToolCreateCircleDB3.png");
    (*menus)[0].buttons.emplace_back("ToolCreateAltitudeFoot", Hitbox(windowX*1/100, windowX*1/100 + windowX*21/100, windowX*6/100, windowX*6/100), 1, "CreateAltitudeFoot", "textures/ToolCreateAltitudeFoot.png");
    (*menus)[0].buttons.emplace_back("ToolCreateMidpoint", Hitbox(windowX*8/100, windowX*1/100 + windowX*21/100, windowX*6/100, windowX*6/100), 1, "CreateMidpoint", "textures/ToolCreateMidpoint.png");
    (*menus)[0].buttons.emplace_back("ToolCreatePerpendicularBisector", Hitbox(windowX*1/100, windowX*1/100 + windowX*28/100, windowX*6/100, windowX*6/100), 1, "CreatePerpendicularBisector", "textures/ToolCreatePerpendicularBisector.png");
    (*menus)[0].buttons.emplace_back("ToolCreateAngleBisector", Hitbox(windowX*8/100, windowX*1/100 + windowX*28/100, windowX*6/100, windowX*6/100), 1, "CreateAngleBisector", "textures/ToolCreateAngleBisector.png");
    (*menus)[0].buttons.emplace_back("ToolCreateOutsideAngleBisector", Hitbox(windowX*1/100, windowX*1/100 + windowX*35/100, windowX*6/100, windowX*6/100), 1, "CreateOutsideAngleBisector", "textures/ToolCreateOutsideAngleBisector.png");
    (*menus)[0].buttons.emplace_back("ToolDeleteObject", Hitbox(windowX*8/100, windowX*1/100 + windowX*35/100, windowX*6/100, windowX*6/100), 1, "DeleteObject", "textures/ToolDeleteObject.png");

    (*menus)[0].buttons[0].tool = MOVE_OBJECTS;
    (*menus)[0].buttons[1].tool = CREATE_POINT;
    (*menus)[0].buttons[2].tool = CREATE_SEGMENT;
    (*menus)[0].buttons[3].tool = CREATE_LINE;
    (*menus)[0].buttons[4].tool = CREATE_CIRCLE_DB2;
    (*menus)[0].buttons[5].tool = CREATE_CIRCLE_DB3;
    (*menus)[0].buttons[6].tool = CREATE_ALTITUDE_FOOT;
    (*menus)[0].buttons[7].tool = CREATE_MIDPOINT;
    (*menus)[0].buttons[8].tool = CREATE_PERPENDICULAR_BISECTOR;
    (*menus)[0].buttons[9].tool = CREATE_ANGLE_BISECTOR;
    (*menus)[0].buttons[10].tool = CREATE_OUTSIDE_ANGLE_BISECTOR;
    (*menus)[0].buttons[11].tool = DELETE_OBJECT;

}

int main()
{
    Textures texturesList;

    geometricToolSelected toolSelection = MOVE_OBJECTS;
    GM::Vector offset(0, 0);
    int desktopX = VideoMode().getDesktopMode().width, desktopY = VideoMode().getDesktopMode().height - 70;
    ContextSettings settings;
    settings.antialiasingLevel = 10;
    RenderWindow window(VideoMode(desktopX*9/10, desktopY*9/10), "", Style::Default, settings);
    window.setPosition(Vector2i(desktopX/20, desktopY/20));

    vector<dynamicIndex> indexSelection;

    vector<dynamicPoint> pointMemory;
    vector<dynamicPointIndexes2> segmentMemory, lineMemory, circleMemoryDB2;
    vector<dynamicPointIndexes3> circleMemoryDB3;

    vector<pointPos> oldPointPositions;

    vector<Menu> menus;

    bool grabbedScreen = false;
    Vector2i oldMousePos;

    init(&window, &menus);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) window.close();
            else if (event.type == Event::Resized)
            {
                int windX = window.getSize().x, windY = window.getSize().y;
                View v;
                GM::Vector difference(window.getSize().x - window.getView().getSize().x, window.getSize().y - window.getView().getSize().y);
                //offset = offset - difference/2;
                v.setCenter(windX/2, windY/2);
                v.setSize(windX, windY);
                window.setView(v);
                setMenusPosition(&window, &menus);
            }
            else if (event.type == Event::KeyPressed)
            {
                switch(event.key.code)
                {
                case Keyboard::Escape:
                    cleanTemporaryData(&indexSelection, &pointMemory, &segmentMemory, &lineMemory, &circleMemoryDB2, &circleMemoryDB3);
                    restoreOldPositions(&oldPointPositions, &pointMemory);
                    break;
                default:
                    break;
                }
            }
            else if (event.type == Event::MouseButtonPressed && Mouse::isButtonPressed(Mouse::Left))
            {
//                for (int i=0; i<pointMemory.size(); i++) cout<<i<<" pointMemory pType "<<pointMemory[i].pType<<endl;
//                for (int i=0; i<segmentMemory.size(); i++) cout<<i<<" segmentMemory dependencies "<<segmentMemory[i].pointIndexA<<" "<<segmentMemory[i].pointIndexB<<endl;
//                for (int i=0; i<lineMemory.size(); i++) cout<<i<<" lineMemory dependencies "<<lineMemory[i].pointIndexA<<" "<<lineMemory[i].pointIndexB<<endl;
//                for (int i=0; i<circleMemoryDB2.size(); i++) cout<<i<<" circleMemoryDB3 dependencies "<<circleMemoryDB2[i].pointIndexA<<" "<<circleMemoryDB2[i].pointIndexB<<endl;
//                for (int i=0; i<circleMemoryDB3.size(); i++) cout<<i<<" circleMemoryDB2 dependencies "<<circleMemoryDB3[i].pointIndexA<<" "<<circleMemoryDB3[i].pointIndexB<<" "<<circleMemoryDB3[i].pointIndexC<<endl;
//                cout<<"--------------------------------------------------"<<endl;

                Vector2i mouse = Mouse::getPosition(window);
                pair<int, int> curButton = clickedButton(mouse.x, mouse.y, &menus);
                if (curButton.first != -1)
                {
                    cleanTemporaryData(&indexSelection, &pointMemory, &segmentMemory, &lineMemory, &circleMemoryDB2, &circleMemoryDB3);
                    restoreOldPositions(&oldPointPositions, &pointMemory);
                    if (curButton.second != -1)
                    {
                        Button selectedButton = menus[curButton.first].buttons[curButton.second];
                        if (menus[curButton.first].name == "MainTools")
                        {

                            if (selectedButton.name == "ToolMove") toolSelection = MOVE_OBJECTS;
                            else if (selectedButton.name == "ToolCreatePoint") toolSelection = CREATE_POINT;
                            else if (selectedButton.name == "ToolCreateSegment") toolSelection = CREATE_SEGMENT;
                            else if (selectedButton.name == "ToolCreateLine") toolSelection = CREATE_LINE;
                            else if (selectedButton.name == "ToolCreateCircleDB2") toolSelection = CREATE_CIRCLE_DB2;
                            else if (selectedButton.name == "ToolCreateCircleDB3") toolSelection = CREATE_CIRCLE_DB3;
                            else if (selectedButton.name == "ToolCreateAltitudeFoot") toolSelection = CREATE_ALTITUDE_FOOT;
                            else if (selectedButton.name == "ToolCreateMidpoint") toolSelection = CREATE_MIDPOINT;
                            else if (selectedButton.name == "ToolCreatePerpendicularBisector") toolSelection = CREATE_PERPENDICULAR_BISECTOR;
                            else if (selectedButton.name == "ToolCreateAngleBisector") toolSelection = CREATE_ANGLE_BISECTOR;
                            else if (selectedButton.name == "ToolCreateOutsideAngleBisector") toolSelection = CREATE_OUTSIDE_ANGLE_BISECTOR;
                            else if (selectedButton.name == "ToolDeleteObject") toolSelection = DELETE_OBJECT;
                        }
                    }
                }
                else
                {
                    mouse.y = window.getSize().y - mouse.y;
                    mouse.x += offset.x;
                    mouse.y += offset.y;
                    if (toolSelection)
                    {
                        if (toolSelection == MOVE_OBJECTS)
                        {
                            vector<indexDist> closePoints = findClosestPoint(mouse.x, mouse.y, &pointMemory, RECOGNISABLE_DISTANCE);
                            if (closePoints.size() > 0)
                            {
                                if (pointMemory[closePoints[0].index].pType == FREE || pointMemory[closePoints[0].index].pType == RELATIVE)
                                {
                                    GM::Point p = DTSPoint(closePoints[0].index, &pointMemory);
                                    oldPointPositions.emplace_back(closePoints[0].index, p.x, p.y, pointMemory[closePoints[0].index].arg);
                                }
                            }
                            else
                            {
                                grabbedScreen = true;
                                oldMousePos = Mouse::getPosition(window);
                            }
                        }

                        else if (toolSelection == CREATE_POINT)
                        {
                            createPoint(mouse.x, mouse.y, &indexSelection, &pointMemory, &segmentMemory, &lineMemory, &circleMemoryDB2, &circleMemoryDB3, RECOGNISABLE_DISTANCE);
                        }
                        else if (toolSelection == CREATE_SEGMENT)
                        {
                            createSegment(mouse.x, mouse.y, &indexSelection, &pointMemory, &segmentMemory, &lineMemory, &circleMemoryDB2, &circleMemoryDB3, RECOGNISABLE_DISTANCE);
                        }
                        else if (toolSelection == CREATE_LINE)
                        {
                            createLine(mouse.x, mouse.y, &indexSelection, &pointMemory, &segmentMemory, &lineMemory, &circleMemoryDB2, &circleMemoryDB3, RECOGNISABLE_DISTANCE);
                        }
                        else if (toolSelection == CREATE_CIRCLE_DB2)
                        {
                            createCircleDB2(mouse.x, mouse.y, &indexSelection, &pointMemory, &segmentMemory, &lineMemory, &circleMemoryDB2, &circleMemoryDB3, RECOGNISABLE_DISTANCE);
                        }
                        else if (toolSelection == CREATE_CIRCLE_DB3)
                        {
                            createCircleDB3(mouse.x, mouse.y, &indexSelection, &pointMemory, &segmentMemory, &lineMemory, &circleMemoryDB2, &circleMemoryDB3, RECOGNISABLE_DISTANCE);
                        }
                        else if (toolSelection == CREATE_ALTITUDE_FOOT)
                        {
                            createAltitude(mouse.x, mouse.y, &indexSelection, &pointMemory, &segmentMemory, &lineMemory, &circleMemoryDB2, &circleMemoryDB3, RECOGNISABLE_DISTANCE);
                        }
                        else if (toolSelection == CREATE_MIDPOINT)
                        {
                            createMidpoint(mouse.x, mouse.y, &indexSelection, &pointMemory, &segmentMemory, &lineMemory, &circleMemoryDB2, &circleMemoryDB3, RECOGNISABLE_DISTANCE);
                        }
                        else if (toolSelection == CREATE_PERPENDICULAR_BISECTOR)
                        {
                            createPerpendicularBisector(mouse.x, mouse.y, &indexSelection, &pointMemory, &segmentMemory, &lineMemory, &circleMemoryDB2, &circleMemoryDB3, RECOGNISABLE_DISTANCE);
                        }
                        else if (toolSelection == CREATE_ANGLE_BISECTOR)
                        {
                            createAngleBisector(mouse.x, mouse.y, &indexSelection, &pointMemory, &segmentMemory, &lineMemory, &circleMemoryDB2, &circleMemoryDB3, RECOGNISABLE_DISTANCE);
                        }
                        else if (toolSelection == CREATE_OUTSIDE_ANGLE_BISECTOR)
                        {
                            createOutsideAngleBisector(mouse.x, mouse.y, &indexSelection, &pointMemory, &segmentMemory, &lineMemory, &circleMemoryDB2, &circleMemoryDB3, RECOGNISABLE_DISTANCE);
                        }
                        else if (toolSelection == DELETE_OBJECT)
                        {
                            Vector2i mouse = Mouse::getPosition(window);
                            double mouseX = mouse.x + offset.x, mouseY = window.getSize().y - mouse.y + offset.y;
                            const std::set<geometryShape> preferred = {POINT, SEGMENT, LINE, CIRCLE_DB2, CIRCLE_DB3};
                            dynamicIndex hovered = selectObject(mouseX, mouseY, &indexSelection, &pointMemory, &segmentMemory, &lineMemory, &circleMemoryDB2, &circleMemoryDB3,
RECOGNISABLE_DISTANCE, preferred);
                            if (hovered.shape != NO_SHAPE)
                            {
                                switch(hovered.shape)
                                {
                                case POINT:
                                    deletePoint(hovered.index, &pointMemory, &segmentMemory, &lineMemory, &circleMemoryDB2, &circleMemoryDB3);
                                    break;
                                case SEGMENT:
                                    deleteSegment(hovered.index, &pointMemory, &segmentMemory, &lineMemory, &circleMemoryDB2, &circleMemoryDB3);
                                    break;
                                case LINE:
                                    deleteLine(hovered.index, &pointMemory, &segmentMemory, &lineMemory, &circleMemoryDB2, &circleMemoryDB3);
                                    break;
                                case CIRCLE_DB2:
                                    deleteCircleDB2(hovered.index, &pointMemory, &segmentMemory, &lineMemory, &circleMemoryDB2, &circleMemoryDB3);
                                    break;
                                case CIRCLE_DB3:
                                    deleteCircleDB3(hovered.index, &pointMemory, &segmentMemory, &lineMemory, &circleMemoryDB2, &circleMemoryDB3);
                                    break;
                                default:
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            else if (event.type == Event::MouseButtonPressed && Mouse::isButtonPressed(Mouse::Right))
            {
                cleanTemporaryData(&indexSelection, &pointMemory, &segmentMemory, &lineMemory, &circleMemoryDB2, &circleMemoryDB3);
                restoreOldPositions(&oldPointPositions, &pointMemory);
            }

            else if (event.type == Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    if (toolSelection == MOVE_OBJECTS)
                    {
                        if (oldPointPositions.size() == 1)
                        {
                            oldPointPositions.clear();
                        }
                        else if (oldPointPositions.size() == 0)
                        {
                            grabbedScreen = false;
                        }
                    }
                }
            }
        }
        if (toolSelection == MOVE_OBJECTS && oldPointPositions.size() == 1 && Mouse::isButtonPressed(Mouse::Left))
        {
            Vector2i mouse = Mouse::getPosition(window);
            double mouseX = mouse.x + offset.x;
            double mouseY = window.getSize().y - mouse.y + offset.y;

            if (pointMemory[oldPointPositions[0].index].pType == FREE)
            {
                pointMemory[oldPointPositions[0].index].coords = GM::Point(mouseX, mouseY);
            }
            else
            {
                switch (pointMemory[oldPointPositions[0].index].defShape1)
                {
                    case LINE:
                    {
                        GM::Line l = DTSLine(pointMemory[oldPointPositions[0].index].defIndex1, &pointMemory, &lineMemory);
                        GM::Segment alt = altitude(l, GM::Point(mouseX, mouseY));
                        GM::Point p1 = DTSPoint(lineMemory[pointMemory[oldPointPositions[0].index].defIndex1].pointIndexA, &pointMemory), p2 = DTSPoint(lineMemory[pointMemory[oldPointPositions[0].index].defIndex1].pointIndexB, &pointMemory);
                        double dx = p2.x - p1.x, dy = p2.y - p1.y, dx2 = alt.b.x - p1.x, dy2 = alt.b.y - p1.x;
                        if (dx == 0 || dy == 0) break;
                        if (l.straight())
                        {
                            pointMemory[oldPointPositions[0].index].arg = dy2/dy;
                        }
                        else
                        {
                            pointMemory[oldPointPositions[0].index].arg = dx2/dx;
                        }
                        break;
                    }
                    case SEGMENT:
                    {
                        GM::Line l = GM::Line(DTSSegment(pointMemory[oldPointPositions[0].index].defIndex1, &pointMemory, &segmentMemory));
                        GM::Segment alt = altitude(l, GM::Point(mouseX, mouseY));
                        GM::Point p1 = DTSPoint(segmentMemory[pointMemory[oldPointPositions[0].index].defIndex1].pointIndexA, &pointMemory), p2 = DTSPoint(segmentMemory[pointMemory[oldPointPositions[0].index].defIndex1].pointIndexB, &pointMemory);
                        double dx = p2.x - p1.x, dy = p2.y - p1.y, dx2 = alt.b.x - p1.x, dy2 = alt.b.y - p1.x;
                        if (dx == 0 || dy == 0) break;
                        if (l.straight())
                        {
                            pointMemory[oldPointPositions[0].index].arg = dy2/dy;
                        }
                        else
                        {
                            pointMemory[oldPointPositions[0].index].arg = dx2/dx;
                        }

                        if (pointMemory[oldPointPositions[0].index].arg > 0.95) pointMemory[oldPointPositions[0].index].arg = 0.95;
                        else if (pointMemory[oldPointPositions[0].index].arg < 0.05) pointMemory[oldPointPositions[0].index].arg = 0.05;

                        break;
                    }
                    case CIRCLE_DB2:
                    {
                        GM::Circle c = DTSCircleDB2(pointMemory[oldPointPositions[0].index].defIndex1, &pointMemory, &circleMemoryDB2);
                        std::vector<GM::Point> pts = crossPoints(c, GM::Line(c.center, GM::Point(mouseX, mouseY)));
                        GM::Point p = pts[0];
                        if (distanceBetweenPoints(GM::Point(mouseX, mouseY), pts[0]) > distanceBetweenPoints(GM::Point(mouseX, mouseY), pts[1])) p = pts[1];
                        pointMemory[oldPointPositions[0].index].arg = atan2(p.y - c.center.y, p.x - c.center.x);
                        break;
                    }
                    case CIRCLE_DB3:
                    {
                        GM::Circle c = DTSCircleDB3(pointMemory[oldPointPositions[0].index].defIndex1, &pointMemory, &circleMemoryDB3);
                        std::vector<GM::Point> pts = crossPoints(c, GM::Line(c.center, GM::Point(mouseX, mouseY)));
                        GM::Point p = pts[0];
                        if (distanceBetweenPoints(GM::Point(mouseX, mouseY), pts[0]) > distanceBetweenPoints(GM::Point(mouseX, mouseY), pts[1])) p = pts[1];
                        pointMemory[oldPointPositions[0].index].arg = atan2(p.y - c.center.y, p.x - c.center.x);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

        if (toolSelection == MOVE_OBJECTS && oldPointPositions.size() == 0 && Mouse::isButtonPressed(Mouse::Left) && grabbedScreen == true)
        {
            Vector2i mouse = Mouse::getPosition(window);
            offset.x -= mouse.x - oldMousePos.x;
            offset.y += mouse.y - oldMousePos.y;
            oldMousePos = mouse;
        }

        window.clear(Color(40,40,40));

//        renderGMShape(&window, GM::Line(GM::Point(0, 0), GM::Point(1, 0)), LineColors(sf::Color(100, 100, 100)), offset, DEFAULT_THICKNESS);
//        renderGMShape(&window, GM::Line(GM::Point(0, 0), GM::Point(0, 1)), LineColors(sf::Color(100, 100, 100)), offset, DEFAULT_THICKNESS);

        updateRelativePoints(&pointMemory, &segmentMemory, &lineMemory, &circleMemoryDB2, &circleMemoryDB3);

        {
            Vector2i mouse = Mouse::getPosition(window);
            double mouseX = mouse.x + offset.x, mouseY = window.getSize().y - mouse.y + offset.y;
            renderDynamicObjects(&window, mouseX, mouseY, &indexSelection, &pointMemory, &segmentMemory, &lineMemory, &circleMemoryDB2, &circleMemoryDB3, offset, RECOGNISABLE_DISTANCE, DEFAULT_THICKNESS);
        }
        //Previews:

        if (indexSelection.size() > 0)
        {
            objectPreview(&window, &indexSelection, &pointMemory, &segmentMemory, &lineMemory, &circleMemoryDB2, &circleMemoryDB3, toolSelection, offset, RECOGNISABLE_DISTANCE, DEFAULT_THICKNESS);
        }
        //Menus:

        for (unsigned int i=0; i<menus.size(); i++)
        {
            RectangleShape rect;
            rect.setPosition(menus[i].hitbox.pos);
            rect.setSize(menus[i].hitbox.sz);
            rect.setFillColor(Color(55, 55, 55));
            rect.setOutlineColor(Color(55, 55, 55));
            window.draw(rect);
            menus[i].hitbox.drawOutline(&window);
            for (unsigned int j=0; j<menus[i].buttons.size(); j++)
            {
                Sprite s;
                sf::Texture t(texturesList.loadedTextures[menus[i].buttons[j].textureName]);
                if (menus[i].buttons[j].textureName != "") texturesList.loadTexture(menus[i].buttons[j].texturePath, menus[i].buttons[j].textureName);
                s.setPosition(menus[i].buttons[j].hitbox.pos);
                s.setScale(menus[i].buttons[j].hitbox.sz.x/t.getSize().x, menus[i].buttons[j].hitbox.sz.y/t.getSize().y);
                s.setTexture(t);
                window.draw(s);
                menus[i].buttons[j].hitbox.drawOutline(&window);
                RectangleShape rect;
                rect.setFillColor(sf::Color(255, 255, 255, 60));
                rect.setPosition(menus[i].buttons[j].hitbox.pos);
                rect.setSize(menus[i].buttons[j].hitbox.sz);
                rect.setOutlineThickness(0);
                if (toolSelection == menus[i].buttons[j].tool) window.draw(rect);
            }
        }
        window.display();
    }

    return 0;
}

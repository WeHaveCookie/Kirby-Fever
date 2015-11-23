#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <iostream>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include "Reader.h"
#include "DrawableObject.h"
#include "Map.hpp"
#include "MapLoader.h"
#include "QuadTree.hpp"

class QuadTree;

class Level : public Reader
{
public:
    Level(std::string _path);
    std::list<DrawableObject*> getObjects();
    void drawMap(sf::RenderWindow* window);
    int getSizeX();
    int getSizeY();
    void destroyItem(int x,int y);
    QuadTree* createQuadTree();
    ~Level();

private:
    void read();
    void build();
    std::string path;
    std::string levelName;
    std::list<DrawableObject*> objects;
    Map* foreground;
    Map* backgroundLv1;
    Map* backgroundLv2;
};

#endif // LEVEL_HPP

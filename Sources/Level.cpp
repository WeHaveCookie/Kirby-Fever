#include "Level.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////
Level::Level(std::string _path)
: path(_path), Reader(_path)
{
    std::cout << _path <<std::endl;
    build();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void Level::drawMap(sf::RenderWindow* window)
{
    window->draw(*backgroundLv2);
    window->draw(*backgroundLv1);
    window->draw(*foreground);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
QuadTree* Level::createQuadTree()
{
    return foreground->createQuadtree();
}

int Level::getSizeX()
{
    return foreground->getSizeX();
}

int Level::getSizeY()
{
    return foreground->getSizeY();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void Level::build()
{
    read();
    MapLoader mumu(path);
    foreground = mumu.createMap();
    backgroundLv1 = mumu.createBackground("Lv1");
    backgroundLv2 = mumu.createBackground("Lv2");

}

///////////////////////////////////////////////////////////////////////////////////////////////////
void Level::read()
{
    while (m_curChar != EOF)
    {
        m_curWord = nextWord();
        if (m_curWord == "Name")
        {
            skipSeparator();
            levelName = nextWord();
            std::cout<<"Level Name : "<<levelName<<std::endl;
        }
        else if (m_curWord == "Map")
        {
            skipSeparator();
            path = nextWord();
            path = defaultMapPath + path;
            std::cout<<"Path Map : "<<path<<std::endl;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void Level::destroyItem(int x,int y)
{
    foreground->destroyItem(x,y);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
std::list<DrawableObject*> Level::getObjects()
{
    return objects;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
Level::~Level()
{
    objects.clear();
}

#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include <iostream>
#include <Vector>
#include <List>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "QuadTree.hpp"



class Map : public sf::Drawable, public sf::Transformable
{
public:
    Map(const std::string & filePath, std::vector <int> tabMap, sf::Vector2i mapSize, sf::Vector2u spriteSize, sf::Vector2f initPosChar);
    Map(const std::string & filePath, std::vector <int> tabMap, sf::Vector2i mapSize, sf::Vector2u spriteSize);
    Map();
    ~Map();

    void createMap();
    int getSizeX();
    int getSizeY();
    QuadTree* createQuadtree();
    bool loadVertice();
    void destroyItem(int x,int y);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        states.texture = &m_tileset;
        target.draw(m_vertices, states);
    }

protected:
private:
    sf::Texture m_tileset;
    std::string m_filePath;
    std::vector <int> m_tabMap;
    sf::Vector2f m_initPosChar;
    sf::Vector2i m_mapSize;
    sf::Vector2u m_spriteSize;
    sf::VertexArray m_vertices;
};

#endif // MAP_H_INCLUDED

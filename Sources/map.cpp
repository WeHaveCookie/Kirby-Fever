#include "Map.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////
Map::Map(const std::string & filePath, std::vector <int> tabMap, sf::Vector2i mapSize, sf::Vector2u spriteSize, sf::Vector2f initPosChar)
:m_filePath(filePath), m_tabMap(tabMap), m_mapSize(mapSize), m_spriteSize(spriteSize), m_initPosChar(initPosChar)
{
    m_mapSize.x = m_mapSize.x/32;
    m_mapSize.y = m_mapSize.y/32;
    m_spriteSize = sf::Vector2u(32,32);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
Map::Map(const std::string & filePath, std::vector <int> tabMap, sf::Vector2i mapSize, sf::Vector2u spriteSize)
:m_filePath(filePath), m_tabMap(tabMap), m_mapSize(mapSize), m_spriteSize(spriteSize)
{
    m_mapSize.x = m_mapSize.x/32;
    m_mapSize.y = m_mapSize.y/32;
    m_spriteSize = sf::Vector2u(32,32);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
Map::Map()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////
Map::~Map()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////
bool Map::loadVertice()
{
    if (!m_tileset.loadFromFile(m_filePath))
    {
        return false;
    }
    sf::Vector2u taille = m_tileset.getSize();

    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(m_mapSize.x * m_mapSize.y * 4);

    // on remplit le tableau de vertex, avec un quad par tuile
    for (int i(0); i < m_mapSize.y; ++i)
    {
        for (int j(0); j < m_mapSize.x; ++j)
        {
            // on récupère le numéro de tuile courant
            int tileNumber = m_tabMap[j + i * m_mapSize.x]-1;
            //std::cout <<tileNumber << " | ";

            // on en déduit sa position dans la texture du tileset
            int tu = tileNumber % (m_tileset.getSize().x / m_spriteSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / m_spriteSize.x);

            // on récupère un pointeur vers le quad à définir dans le tableau de vertex
            sf::Vertex* quad = &m_vertices[(j + i * m_mapSize.x) * 4];

            // on définit ses quatre coins
            quad[0].position = sf::Vector2f(j * m_spriteSize.x, i * m_spriteSize.y);
            quad[1].position = sf::Vector2f((j + 1) * m_spriteSize.x, i * m_spriteSize.y);
            quad[2].position = sf::Vector2f((j + 1) * m_spriteSize.x, (i + 1) * m_spriteSize.y);
            quad[3].position = sf::Vector2f(j * m_spriteSize.x, (i + 1) * m_spriteSize.y);

            // on définit ses quatre coordonnées de texture
            quad[0].texCoords = sf::Vector2f(tu * m_spriteSize.x, tv * m_spriteSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * m_spriteSize.x, tv * m_spriteSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * m_spriteSize.x, (tv + 1) * m_spriteSize.y);
            quad[3].texCoords = sf::Vector2f(tu * m_spriteSize.x, (tv + 1) * m_spriteSize.y);
        }
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void Map::createMap()
{
    loadVertice();
}

int Map::getSizeX()
{
    return m_mapSize.x*m_spriteSize.x;
}

int Map::getSizeY()
{
    return m_mapSize.y*m_spriteSize.y;
}

void Map::destroyItem(int x,int y)
{
    m_tabMap[x + y*m_mapSize.x] = 1023;
    int tileNumber = 1023;
    y++;
    // on en déduit sa position dans la texture du tileset
    int tu = tileNumber % (m_tileset.getSize().x / m_spriteSize.x);
    int tv = tileNumber / (m_tileset.getSize().x / m_spriteSize.x);

    // on récupère un pointeur vers le quad à définir dans le tableau de vertex
    sf::Vertex* quad = &m_vertices[(x + y * m_mapSize.x) * 4];

    // on définit ses quatre coins
    quad[0].position = sf::Vector2f(0,0);
    quad[1].position = sf::Vector2f(0,0);
    quad[2].position = sf::Vector2f(0,0);
    quad[3].position = sf::Vector2f(0,0);

}

QuadTree* Map::createQuadtree()
{
    QuadTree* tree = new QuadTree(0,0,m_mapSize.x*m_spriteSize.x,m_mapSize.x*m_spriteSize.x,0,5);
    sf::Sprite* sprite;
    for (int i(0); i < m_mapSize.y; ++i)
    {
        for (int j(0); j < m_mapSize.x; ++j)
        {
            sf::Vertex* quad = &m_vertices[(j + i * m_mapSize.x) * 4];
            int tileNumber = m_tabMap[j + i * m_mapSize.x]-1;
            int tu = tileNumber % (m_tileset.getSize().x / m_spriteSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / m_spriteSize.x);
            if(tileNumber != 0 && tileNumber != 1023 && tileNumber != 1024)
            {
                sprite = new sf::Sprite;
                sprite->setTexture(m_tileset);
                sprite->setTextureRect(sf::IntRect(tu * m_spriteSize.x, tv * m_spriteSize.y,m_spriteSize.x,m_spriteSize.y));
                sprite->setPosition(j * m_spriteSize.x, i * m_spriteSize.y);
                tree->AddObject(sprite);
            }

        }
    }
    return tree;
}

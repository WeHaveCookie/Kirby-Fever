#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include "Reader.h"
#include "Map.hpp"
#include "constantes.hpp"



class MapLoader : public Reader
{
public:

        //Constructor//
        MapLoader(const std::string & filePath);
        virtual ~MapLoader();

        //Getteur//
        inline std::string getAuthor () { return m_author;}
        inline sf::Vector2i getMapSize () { return m_mapSize;}
        inline int getSpriteSize () { return m_spriteSize;}
        inline sf::Vector2f getInitPosChar () { return m_initPosChar;}
        inline std::string getMapName () { return m_mapName;}


        //Setteur//
        inline void setFilePath (const std::string & filePath) {m_filePath = filePath;}

        //Function//
        void loadMap();
        void reloadMap();
        Map* createMap();
        Map* createBackground(std::string lvl);

        sf::IntRect getRectSprite(int numSprite);


private:

        //Function//

        void read();
        std::string m_fileName;
        std::string m_author;
        sf::Vector2i m_mapSize;
        int m_spriteSize;
        int m_spriteColumn;
        int m_spriteLine;
        sf::Vector2f m_initPosChar;
        sf::Texture m_tileset;
        std::string m_mapName;
        std::vector <int> m_tabMap;
        std::vector <int> m_tabBackgroundLv1;
        std::vector <int> m_tabBackgroundLv2;
        std::vector<unsigned int> m_numBlockBlocking;
};

#endif // MAPLOADER_H

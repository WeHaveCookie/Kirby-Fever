#include "MapLoader.h"

using namespace sf;

///////////////////////////////////////////////////////////////////////////////////////////////////
MapLoader::MapLoader(const std::string & filePath)
:Reader(filePath)
{
    loadMap();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
MapLoader::~MapLoader()
{
    close();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void MapLoader::loadMap()
{
    read();
    std::cerr<<"Succes : Map load ! "<<std::endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void MapLoader::reloadMap()
{
    m_file.close();
    open(m_filePath);
    loadMap();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
sf::IntRect MapLoader::getRectSprite(int numSprite)
{
    return IntRect(sf::IntRect(32*((numSprite-1)%32),32*((numSprite-1)/32),32,32));
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void MapLoader::read()
{

    while (m_curChar != EOF)
    {
        m_curWord = nextWord();
        if (m_curWord == "CreateBy")
        {
            skipSeparator();
            m_author = nextWord();
            std::cerr<<"Author :  "<<m_author<<std::endl;
        }
        else if (m_curWord == "MapName")
        {
            skipSeparator();
            m_mapName = nextWord();
            std::cerr<<"Map Name :  "<<m_mapName<<std::endl;
        }
        else if (m_curWord == "SizeMap")
        {
            skipSeparator();
            std::istringstream x(nextWord());
            x >> m_mapSize.x;
            std::istringstream y(nextWord());
            y >> m_mapSize.y;
            std::cerr<<"Size Map :  x :  "<<m_mapSize.x<<" y : "<<m_mapSize.y<<std::endl;
        }
        else if (m_curWord == "SizeSprite")
        {
            skipSeparator();
            std::istringstream si(nextWord());
            si >> m_spriteSize;
            std::cerr<<"Size Sprite :  "<<m_spriteSize<<std::endl;
        }
        else if (m_curWord == "SpriteColumn")
        {
            skipSeparator();
            std::istringstream co(nextWord());
            co >> m_spriteColumn ;
            std::cerr<<"Sprite Column :  "<<m_spriteColumn<<std::endl;
        }
        else if (m_curWord == "SpriteLine")
        {
            skipSeparator();
            std::istringstream li(nextWord());
            li >> m_spriteLine;
            std::cerr<<"Sprite Line :  "<<m_spriteLine<<std::endl;
        }
        else if (m_curWord == "InitPosChar")
        {
            skipSeparator();
            std::istringstream x(nextWord());
            x >> m_initPosChar.x;
            std::istringstream y(nextWord());
            y >> m_initPosChar.y;
            std::cerr<<"Initial Position Character :  x :  "<<m_initPosChar.x<<" y : "<<m_initPosChar.y<<std::endl;
        }
        else if (m_curWord == "BlockBlocking")
        {
            unsigned int num;
            skipSeparator();
            m_curWord = nextWord();
            do{
                std::istringstream nu(m_curWord);
                nu >> num;
                m_numBlockBlocking.push_back(num);
                skipSeparator();
                m_curWord = nextWord();
            } while (m_curChar != '\n');
            std::istringstream nu(m_curWord);
            nu >> num;
            m_numBlockBlocking.push_back(num);
            std::cerr<<"Vector Num Blocking Block : "<<m_numBlockBlocking.size()<<" : ";
            for(int i=0;i<m_numBlockBlocking.size();i++)
            {
                std::cerr<<m_numBlockBlocking[i]<<" | ";
            }
            std::cerr<<std::endl;
        }
        else if (m_curWord == "PathSprite")
        {
            skipSeparator();
            m_filePath = nextWord();
            m_filePath = defaultTilPath + m_filePath;
            std::cerr<<"Path Sprite :  "<<m_filePath<<std::endl;
        }
        else if (m_curWord == "Map")
        {
            skipSeparator();
            m_curWord = nextWord();
            while (m_curWord != "BackgroundLv1" )
            {
                unsigned int numSprite;
                std::istringstream re(m_curWord);
                re >> numSprite;
                if (m_curWord == "0")
                {
                    numSprite = 1024;
                }
                m_tabMap.push_back(numSprite);
                skipSeparator();
                m_curWord = nextWord();
            }
            std::cout<<m_curWord;
        }
        if (m_curWord == "BackgroundLv1")
        {
            skipSeparator();
            m_curWord = nextWord();
            while(m_curWord != "BackgroundLv2")
            {
                unsigned int numSprite;
                std::istringstream re(m_curWord);
                re >> numSprite;
                if (m_curWord == "0")
                {
                    numSprite = 1024;
                }
                m_tabBackgroundLv1.push_back(numSprite);
                skipSeparator();
                m_curWord = nextWord();
            }
        }
        if (m_curWord == "BackgroundLv2")
        {
                        skipSeparator();
            m_curWord = nextWord();
            while(m_curWord != "")
            {
                unsigned int numSprite;
                std::istringstream re(m_curWord);
                re >> numSprite;
                if (m_curWord == "0")
                {
                    numSprite = 1024;
                }
                m_tabBackgroundLv2.push_back(numSprite);
                skipSeparator();
                m_curWord = nextWord();
            }
        }
    }

}

Map* MapLoader::createMap()
{
    Map* map1 = new Map(m_filePath,m_tabMap,m_mapSize,sf::Vector2u(32,32),m_initPosChar);
    map1->createMap();
    return map1;
}

Map* MapLoader::createBackground(std::string lvl)
{
    if (lvl == "Lv1")
    {
        Map* map1 = new Map(m_filePath,m_tabBackgroundLv1,m_mapSize,sf::Vector2u(32,32));
        map1->createMap();
        return map1;
    }
    else if (lvl == "Lv2")
    {
        Map* map1 = new Map(m_filePath,m_tabBackgroundLv2,m_mapSize,sf::Vector2u(32,32));
        map1->createMap();
        return map1;
    }
    else
    {
        return NULL;
    }
}

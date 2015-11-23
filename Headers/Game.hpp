#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "constantes.hpp"
#include "Level.hpp"
#include "DrawableObject.h"
#include "Character.hpp"
#include "Menu.hpp"
#include "QuadTree.hpp"



class Game
{
public:
    Game(sf::RenderWindow* _window);
    void launch();
    void setLevel(std::string path);
    sf::RenderWindow* getWindow();
    inline sf::Vector2f getDecalage(){return decalageVue;}
    QuadTree* getQuadTree();
    ~Game();
private:
    sf::RenderWindow* window;
    sf::View view;
    sf::Vector2f decalageVue;
    Menu menu;
    Level* level;
    QuadTree* tree;
    bool gameIsRunning;
};

#endif // GAME_HPP

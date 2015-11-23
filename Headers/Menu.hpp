#ifndef MENU_HPP
#define MENU_HPP
#include <SFML/Graphics.hpp>
#include "DrawableObject.h"
#include "constantes.hpp"
#define pourcG 33
#define pourcH 20
#define ecart 80

class Menu : public DrawableObject
{
public:
    Menu();
    bool updateMenu(sf::RenderWindow *window);
    void update(sf::RenderWindow *window){}
    void razMenu();
    int choixMenu(sf::RenderWindow *window);
    void draw(sf::RenderWindow* window);
    void enable();
    void disable();
    bool isEnabled();
    ~Menu();
private:
    int _nombreChoix;
    bool show;
    sf::Color _couleurFond;
    sf::Color _couleurFont;
    sf::Font _font;
    sf::Vector2f _position;
    sf::Text *_texte;
    sf::Sprite* _sprites;
    sf::Texture* _textures;
    sf::Image* _images;
    sf::Sprite fond;
    sf::Texture textureFond;
    sf::Image imageFond;
};

#endif // MENU_HPP

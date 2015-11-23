#ifndef MAINMENU_HPP
#define MAINMENU_HPP
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "constantes.hpp"
#define pourcG 33
#define pourcH 40
#define ecart 40

class MainMenu : public sf::Drawable,public sf::Transformable
{

public:
    MainMenu();
    void update(sf::RenderWindow *window);
    void razMenu();
    int choixMenu(sf::RenderWindow *window);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        states.texture = NULL;
        target.draw(_sprite,states);
        for (int i(0);i<_nombreChoix;i++)
        {
            target.draw(_texte[i],states);
        }
    }
    ~MainMenu();

protected:
    int _nombreChoix;
    sf::Color _couleurFond;
    sf::Color _couleurFont;
    sf::Font _font;
    sf::Vector2f _position;
    sf::Text *_texte;
    sf::Sprite _sprite;
    sf::Texture _texture;


};


#endif // MAINMENU_HPP

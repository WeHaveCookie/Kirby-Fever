#include "mainMenu.hpp"


using namespace std;

MainMenu::MainMenu()
{
    _texture.loadFromFile("Ressources/Menu/Menu.png");
    _sprite.setTexture(_texture);
    _sprite.setPosition(0,0);

    _position.x = LARGEURFENETRE*pourcG/100;
    _position.y = LARGEURFENETRE*pourcH/100;

    _sprite.setPosition(_position.x-_texture.getSize().x/3,_position.y-250);

    _nombreChoix = 5;
    _texte = new sf::Text[_nombreChoix];
    _texte[0].setString("1.Nouvelle partie");
    _texte[1].setString("2.Charger une partie");
    _texte[2].setString("3.Options");
    _texte[3].setString("4.Crédits");
    _texte[4].setString("5.Exit");

    _font.loadFromFile(defaultFont);

    for (int i(0);i<_nombreChoix;i++)
    {
        _texte[i].setFont(_font);
        _texte[i].setPosition(_position.x,_position.y+ecart*i);
        _texte[i].setCharacterSize(24);
        _texte[i].setColor(sf::Color::Red);
    }


}

void MainMenu::update(sf::RenderWindow *window)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
    for (int i(0);i<_nombreChoix;i++)
    {
        if (mousePosition.y >= (_position.y + ecart*i) && mousePosition.y < (_position.y + ecart*(i+1)) && mousePosition.x)
        {
            _texte[i].setCharacterSize(30);
        }
    }
}

int MainMenu::choixMenu(sf::RenderWindow *window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
        for (int i(0);i<_nombreChoix;i++)
        {
            if (mousePosition.y >= (_position.y + ecart*i) && mousePosition.y < (_position.y + ecart*(i+1)) && mousePosition.x)
            {
                return i;
            }
        }
    }
    return _nombreChoix+1;
}

void MainMenu::razMenu()
{
    for (int i(0);i<_nombreChoix;i++)
    {
        _texte[i].setCharacterSize(24);
    }
}

MainMenu::~MainMenu()
{
    delete _texte;
}

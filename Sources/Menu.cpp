#include "Menu.hpp"

Menu::Menu()
{
    imageFond.create(800,640,sf::Color(30,67,255,128));
    textureFond.loadFromImage(imageFond);
    fond.setTexture(textureFond);

    _position.x = LARGEURFENETRE*pourcG/100;
    _position.y = LARGEURFENETRE*pourcH/100;

    _nombreChoix = 5;
    _texte = new sf::Text[_nombreChoix];
    _texte[0].setString("Continuer");
    _texte[1].setString("Sauvegarder");
    _texte[2].setString("Options");
    _texte[3].setString("Quitter vers menu");
    _texte[4].setString("Quitter vers Bureau");

    _images = new sf::Image[_nombreChoix];
    _textures = new sf::Texture[_nombreChoix];
    _sprites = new sf::Sprite[_nombreChoix];

    _font.loadFromFile(defaultFont);

    for (int i(0);i<_nombreChoix;i++)
    {
        _texte[i].setFont(_font);
        _texte[i].setPosition(_position.x,_position.y+ecart*i);
        _texte[i].setCharacterSize(24);
        _texte[i].setColor(sf::Color::White);

        _images[i].create(300,50,sf::Color(255,0,0));
        _textures[i].loadFromImage(_images[i]);
        _sprites[i].setTexture(_textures[i]);
        _sprites[i].setPosition(_position.x-20,_position.y + i*ecart - 10);
    }
    disable();
}

void Menu::draw(sf::RenderWindow* window)
{
    if(show)
    {
        window->draw(fond);
        for (int i(0);i<_nombreChoix;i++)
            window->draw(_sprites[i]);
        for (int i(0);i<_nombreChoix;i++)
            window->draw(_texte[i]);
    }
}

bool Menu::updateMenu(sf::RenderWindow* window)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
    for (int i(0);i<_nombreChoix;i++)
    {
        if (mousePosition.y >= (_position.y + ecart*i) && mousePosition.y < (_position.y + ecart*(i+1)) && mousePosition.x)
        {
            _images[i].create(300,50,sf::Color(255,236,38));
            _textures[i].loadFromImage(_images[i]);
            _sprites[i].setTexture(_textures[i]);
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        //return true;
    return false;
}

void Menu::razMenu()
{
    for (int i(0);i<_nombreChoix;i++)
    {
        _images[i].create(300,50,sf::Color(255,0,0));
        _textures[i].loadFromImage(_images[i]);
        _sprites[i].setTexture(_textures[i]);
    }
}

int Menu::choixMenu(sf::RenderWindow* window)
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

void Menu::enable()
{
    show = true;
}
void Menu::disable()
{
    show = false;
}
bool Menu::isEnabled()
{
    return show;
}

Menu::~Menu()
{

}

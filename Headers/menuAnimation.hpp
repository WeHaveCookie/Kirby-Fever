#ifndef MENUANIMATION_HPP
#define MENUANIMATION_HPP
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

class MenuAnimation : public sf::Drawable
{
public:
    MenuAnimation(std::string path,int _length);
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    ~MenuAnimation();
private:
    sf::Sprite sprite;
    sf::Texture* textures;
    int current;
    int beginIndex;
    int length;
    int latence;
    int currLatence;
};

#endif // MENUANIMATION_HPP

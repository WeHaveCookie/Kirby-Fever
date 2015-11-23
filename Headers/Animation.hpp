#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

class Animation
{
public:
    Animation(int _latence = 0);
    void update();
    sf::Sprite getCurrentSprite();
    void noUpdate();
    void addSprite(sf::Sprite sprite);
    void moveSprite(sf::Vector2f pos);
    void setPosition(sf::Vector2f _position);
    void reload();
    bool isEnd();
    sf::Vector2f getPosition();
    ~Animation();
private:
    sf::Vector2f position;
    std::vector<sf::Sprite> sprites;
    int it;
    int latence;
    int currLatence;
    bool needUpdate;

};

#endif // ANIMATION_HPP

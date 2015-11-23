#ifndef BULLET_HPP
#define BULLET_HPP
#include <SFML/Graphics.hpp>
#include "DrawableObject.h"
#include "weapon.hpp"
#include "constantes.hpp"
#include "CouldGetForce.h"


class Bullet : public DrawableObject, public CouldGetForce
{
public:
    Bullet(sf::RenderWindow *window,bulletType type,sf::Vector2f _position,sf::Vector2f _angle, sf::Vector2f decalage);
    void draw(sf::RenderWindow* window);
    void update(sf::RenderWindow* window);
    int getPuissance();
    int getPortee();
    void noUpdate();
    inline sf::Vector2f getPosition(){return sprite.getPosition();}
    inline sf::FloatRect getBound(){return sprite.getLocalBounds();}
    ~Bullet();
private:
    int typeOfBullet;
    int puissance;
    int portee;
    int speed;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f angle;
    bool needUpdate;
};

#endif // BULLET_HPP

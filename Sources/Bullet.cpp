#include "Bullet.hpp"
Bullet::Bullet(sf::RenderWindow *window,bulletType type,sf::Vector2f _position,sf::Vector2f _angle, sf::Vector2f decalage) :
    typeOfBullet(type),
    needUpdate(true)
{
    std::string path;
    switch(type)
    {
        case rifle:
            puissance = 100;
            portee = 1000;
            speed = 6;
            path = defaultWeaPath + "rifle-bullet.png";
            break;
        case sniper:
            puissance = 200;
            portee = 2000;
            speed = 10;
            path = defaultWeaPath + "sniper-bullet.png";
            break;
        case launcher:
            puissance = 300;
            portee = 1000;
            speed = 5;
            addForce(Force(sf::Vector2f(0,-3),-1));
            path = defaultWeaPath + "launcher-bullet.png";
            break;
        case closeRanged:
            puissance = 250;
            portee = 300;
            speed = 3;
            path = defaultWeaPath + "closeRanged-bullet.png";
            break;
    }
    angle = _angle;
    texture.loadFromFile(path);
    sprite.setTexture(texture);
    float cosa = (acos(angle.x)*180/3.14159);

    sf::Vector2i localPosition = sf::Mouse::getPosition(*window);

    if(localPosition.x+decalage.x > _position.x)
    {
        if(cosa <= 90 && cosa >= -90)
        {
            if(localPosition.y+decalage.y < _position.y)
            {
                angle.y = -angle.y;
                sprite.setRotation((-cosa));
            }
            else
            {
                sprite.setRotation(cosa);
            }
        }
        sprite.setPosition(_position.x + angle.x*speed,_position.y-10 + angle.y*speed);
    }
    else
    {
        if(cosa >= 90)
        {
            if(localPosition.y+decalage.y < _position.y)
            {
                angle.y = -angle.y;
                sprite.setRotation(-cosa);
            }
            else
                sprite.setRotation(cosa);
        }
        sprite.setPosition(_position.x + angle.x*speed,_position.y-10 + angle.y*speed);
    }
}

void Bullet::draw(sf::RenderWindow* window)
{
    update(window);
    window->draw(sprite);
}

void Bullet::update(sf::RenderWindow* window)
{
    sprite.setPosition(sprite.getPosition().x + angle.x*speed,sprite.getPosition().y + angle.y*speed - applyForce().y);
    portee--;
}

int Bullet::getPuissance()
{
    return puissance;
}

int Bullet::getPortee()
{
    return portee;
}

void Bullet::noUpdate()
{
    needUpdate = false;
}

Bullet::~Bullet()
{

}


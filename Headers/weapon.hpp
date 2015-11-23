#ifndef WEAPON_HPP
#define WEAPON_HPP
#include <ctime>
#include <list>
#include <SFML/Graphics.hpp>
#include "DrawableObject.h"
#include "constantes.hpp"
#include "Bullet.hpp"
#include "Force.hpp"

class Bullet;
class Force;

class Weapon : public DrawableObject, public sf::Transformable
{
public:
    Weapon(std::string filePath,int rof,bulletType _type);
    virtual void draw(sf::RenderWindow* window);
    virtual void update(sf::RenderWindow* window);
    virtual void fire(sf::RenderWindow* window);
    void noUpdate();
    void setPosition(sf::Vector2f pos);
    void setDecalage(sf::Vector2f dec){decalage = dec;}
    sf::Vector2f getPosition();
    inline std::list<Bullet*>* getBullets(){return &bullets;}
    virtual ~Weapon();
protected:
    void addBullet(sf::RenderWindow* window);
    sf::Vector2f position;
    sf::Vector2f decalage;
    bulletType bullet;
    std::list<Bullet*> bullets;
    std::string path;
    sf::Sprite sprite;
    sf::Sprite spriteReverse;
    sf::Texture texture;
    sf::Vector2f angle;
    int rateOfFire; // Nombre de coups par secondes
    int offSetX;
    int offSetY;
    bool reverse;
    bool needUpdate;
    float timeBetweenFire; // temps entre chaque coup
    clock_t deb;
    clock_t fin;
};

#endif // WEAPON_HPP

#ifndef RIFLE_HPP
#define RIFLE_HPP

#include <ctime>
#include <list>
#include <SFML/Graphics.hpp>
#include "DrawableObject.h"
#include "constantes.hpp"
#include "Bullet.hpp"
#include "Force.hpp"
#include "weapon.hpp"

class Weapon;

class Rifle : public Weapon
{
public:
    Rifle(std::string filePath);
    ~Rifle();
private:
};

class Sniper : public Weapon
{
public:
    Sniper(std::string filePath);
    ~Sniper();
private:

};

class Launcher : public Weapon
{
public:
    Launcher(std::string filePath);
    ~Launcher();
private:

};

class Pump : public Weapon
{
public:
    Pump(std::string filePath);
    ~Pump();
private:

};

#endif // WEAPON_HPP

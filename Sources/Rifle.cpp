#include "Rifle.hpp"

Rifle::Rifle(std::string filePath) :
    Weapon::Weapon(filePath,14,rifle)
{
    sprite.setTextureRect(sf::IntRect(713,106,58,33));
    spriteReverse.setTextureRect(sf::IntRect(sprite.getTextureRect().left + sprite.getTextureRect().width,sprite.getTextureRect().top,-sprite.getTextureRect().width,sprite.getTextureRect().height));
    sprite.setOrigin(16,16);
    spriteReverse.setOrigin(16,16);
    offSetX = 26;
    offSetY = 26;
    sprite.setRotation(10);
}

Rifle::~Rifle()
{

}

Sniper::Sniper(std::string filePath):
    Weapon::Weapon(filePath,2,sniper)
{
    sprite.setTextureRect(sf::IntRect(23,187,98,22));
    spriteReverse.setTextureRect(sf::IntRect(sprite.getTextureRect().left + sprite.getTextureRect().width,sprite.getTextureRect().top,-sprite.getTextureRect().width,sprite.getTextureRect().height));
    sprite.setOrigin(16,16);
    spriteReverse.setOrigin(16,16);
    offSetX = 26;
    offSetY = 26;
    sprite.setRotation(10);
}

Sniper::~Sniper()
{

}

Launcher::Launcher(std::string filePath):
    Weapon::Weapon(filePath,3,launcher)
{
    sprite.setTextureRect(sf::IntRect(23,265,83,30));
    spriteReverse.setTextureRect(sf::IntRect(sprite.getTextureRect().left + sprite.getTextureRect().width,sprite.getTextureRect().top,-sprite.getTextureRect().width,sprite.getTextureRect().height));
    sprite.setOrigin(16,16);
    spriteReverse.setOrigin(16,16);
    offSetX = 26;
    offSetY = 26;
    sprite.setRotation(10);
}

Launcher::~Launcher()
{

}

Pump::Pump(std::string filePath):
    Weapon::Weapon(filePath,5,closeRanged)
{
    sprite.setTextureRect(sf::IntRect(713,106,58,33));
    spriteReverse.setTextureRect(sf::IntRect(sprite.getTextureRect().left + sprite.getTextureRect().width,sprite.getTextureRect().top,-sprite.getTextureRect().width,sprite.getTextureRect().height));
    sprite.setOrigin(16,16);
    spriteReverse.setOrigin(16,16);
    offSetX = 26;
    offSetY = 26;
    sprite.setRotation(10);
}

Pump::~Pump()
{

}

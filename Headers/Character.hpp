#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include <SFML/Graphics.hpp>
#include "DrawableObject.h"
#include "constantes.hpp"
#include "Animation.hpp"
#include "CouldGetForce.h"
#include "Game.hpp"
#include "QuadTree.hpp"
#include "weapon.hpp"
#include "Rifle.hpp"

enum action{rien,walk,sprint,Jump,attack};
enum direction{leftDir,rightDir};

class Game;
class Weapon;
class Rifle;

class Character : public DrawableObject, public CouldGetForce
{
public:
    Character(Game* _game,std::string path);
    void move(int x,int y,bool run = false);
    void jump();
    void doNothing();
    void draw(sf::RenderWindow* window);
    void update(sf::RenderWindow* window);
    void setAnimation(action _action);
    void noUpdate();
    void isBlock();
    void razBlocage();
    void enableWeapon();
    void disableWeapon();
    bool isOnAction();
    int getCurrentFrameX();
    int getCurrentFrameY();
    inline direction getDir(){return dir;}
    sf::Vector2f getPosition();
    void setWeapon(bulletType type);
    inline Weapon* getWeapon(){return weapon;}
    inline std::list<Bullet*>* getBullets(){return weapon->getBullets();}
    ~Character();
private:
    void build();
    sf::Vector2f position;
    sf::Vector2f speedToAdd;
    Weapon* weapon;
    Animation* currentAnimation;
    Animation** animations;
    Game* game;
    std::string tilesetPath;
    sf::Texture tileset;
    direction dir;
    int currAnim;
    int currX;
    int currY;
    bool first;
    bool showWeapon;
    bool onAction;
    bool blocageUpSide;
    bool blocageDownSide;
    bool blocageLeftSide;
    bool blocageRightSide;


};

#endif // CHARACTER_HPP

#include "Character.hpp"

Character::Character(Game* _game,std::string path) :
    game(_game),
    tilesetPath(path),
    onAction(false)
{
    tilesetPath = defaultCharPath + tilesetPath;
    tileset.loadFromFile(tilesetPath);
    dir = rightDir;
    currAnim = walk*2+rightDir;
    build();
    first = true;
    std::string pathBob = defaultWeaPath + "weapons.png";
    weapon = new Rifle(pathBob);
    showWeapon = false;
    //Blocage
    blocageUpSide = false;
    blocageDownSide = false;
    blocageLeftSide = false;
    blocageRightSide = false;
    //Position initiale
    position.x = 1;
    position.y =150;
    //Ajout de gravité
    addForce(Force(sf::Vector2f(0,5),-1));

}

void Character::move(int x,int y, bool run)
{
    if(!isOnAction())
    {
        currX = 0;
        if (x>0&&first)
        {
            currAnim = walk*2+rightDir;
            first = false;
        }
        //Marche
        if (x >= 0 && dir != rightDir)
        {
            dir = rightDir;
            currAnim = walk*2+rightDir;
        }
        else if(x < 0 && dir != leftDir)
        {
            dir = leftDir;
            currAnim = walk*2+leftDir;
        }
        //Course
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            if(dir == rightDir)
                currAnim = sprint*2+rightDir;
            else
                currAnim = sprint*2+leftDir;
            speedToAdd.x = x;
            speedToAdd.y = y;
            currX = x;
        }
        currentAnimation = animations[currAnim];

        speedToAdd.x += x;
        speedToAdd.y += y;
        currX += x;

        if(x > 0 && blocageRightSide)
        {
            speedToAdd.x = 0;
        }
        else if(x < 0 && blocageLeftSide)
        {
            speedToAdd.x = 0;
        }
    }
}

void Character::jump()
{
    if(!isOnAction())
    {
        onAction = true;
        currentAnimation = animations[Jump*2+dir];
        currentAnimation->setPosition(position);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::E)))
        {
            addForce(Force(sf::Vector2f(8,-15)));
            addForce(Force(sf::Vector2f(4,2),20,22));
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::E)))
        {
            addForce(Force(sf::Vector2f(-8,-15)));
            addForce(Force(sf::Vector2f(-4,2),20,22));
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            addForce(Force(sf::Vector2f(4,-10)));
            addForce(Force(sf::Vector2f(2,0),25,20));
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            addForce(Force(sf::Vector2f(-4,-10)));
            addForce(Force(sf::Vector2f(-2,0),25,20));
        }
        else
        {
            addForce(Force(sf::Vector2f(0,-10)));
        }
    }
}

void Character::doNothing()
{
    if(dir == leftDir && !isOnAction())
    {
        currentAnimation = animations[rien*2+leftDir];
    }
    else if(dir == rightDir && !isOnAction())
    {
        currentAnimation = animations[rien*2+rightDir];
    }
}

void Character::draw(sf::RenderWindow* window)
{
    update(window);
    window->draw(currentAnimation->getCurrentSprite());
    weapon->setPosition(position);
    if(showWeapon)
    {
        weapon->setDecalage(game->getDecalage());
        weapon->draw(window);
    }

}

void Character::update(sf::RenderWindow* window)
{
    currY = 0;
    isBlock();
    speedToAdd += applyForce();

    if(blocageLeftSide && speedToAdd.x < 0)
        speedToAdd.x = 0;
    if (blocageRightSide && speedToAdd.x > 0)
        speedToAdd.x = 0;
    if (blocageUpSide && speedToAdd.y < 0)
        speedToAdd.y = 0;
    if (blocageDownSide && speedToAdd.y > 0)
        speedToAdd.y = 0;

    if(speedToAdd.y > 0)
        currY = speedToAdd.y;

    if(currentAnimation->isEnd() && isOnAction())
    {
        onAction = false;
        currentAnimation->reload();
        currentAnimation = animations[rien*2+dir];
    }

    position += speedToAdd;
    currentAnimation->setPosition(position);
    currentAnimation->update();

    speedToAdd.x = 0;
    speedToAdd.y = 0;
    razBlocage();
}

void Character::enableWeapon()
{
    showWeapon = true;
}

void Character::disableWeapon()
{
    showWeapon = false;
}

void Character::isBlock()
{
    QuadTree* tree = game->getQuadTree();
    int x = tree->getMinWidth();
    int y = tree->getMinHeight();
    std::list<sf::Sprite*> ens;
    std::list<sf::Sprite*> ens1;
    sf::IntRect rect(position.x,position.y,57,43);

    for (std::list<sf::Sprite*>::iterator it = ens.begin();it != ens.end();it++)
    {
        if (rect.intersects(sf::IntRect((*it)->getPosition().x,(*it)->getPosition().y,32,32)))
        {
            if(position.x > (*it)->getPosition().x)
                blocageLeftSide = true;
        }
    }

    //Right
    ens = tree->GetObjectsAt(position.x+x,position.y);
    if(dir == rightDir)
    {
        ens1 = tree->GetObjectsAt(position.x,position.y);
        ens.insert(ens.end(), ens1.begin(), ens1.end());
    }
    ens1 = tree->GetObjectsAt(position.x+x,position.y+y);
    ens.insert(ens.end(), ens1.begin(), ens1.end());

    for (std::list<sf::Sprite*>::iterator it = ens.begin();it != ens.end();it++)
    {
        if (rect.intersects(sf::IntRect((*it)->getPosition().x,(*it)->getPosition().y,32,32)) && (*it)->getPosition().x > rect.left+57)
        {
            if(position.x < (*it)->getPosition().x)
                blocageRightSide = true;
        }
    }

    //Down
    ens = tree->GetObjectsAt(position.x+x,position.y+y);
    ens1 = tree->GetObjectsAt(position.x-x,position.y+y);
    ens.insert(ens.end(), ens1.begin(), ens1.end());
    ens1 = tree->GetObjectsAt(position.x,position.y);
    ens.insert(ens.end(), ens1.begin(), ens1.end());
    ens1 = tree->GetObjectsAt(position.x,position.y+y);
    ens.insert(ens.end(), ens1.begin(), ens1.end());

    for (std::list<sf::Sprite*>::iterator it = ens.begin();it != ens.end();it++)
    {
        if (rect.intersects(sf::IntRect((*it)->getPosition().x,(*it)->getPosition().y,32,32)))
        {
            blocageDownSide = true;
        }
    }

    //Up
    ens = tree->GetObjectsAt(position.x+x,position.y-y);
    ens1 = tree->GetObjectsAt(position.x-x,position.y-y);
    ens.insert(ens.end(), ens1.begin(), ens1.end());
    ens1 = tree->GetObjectsAt(position.x,position.y-y);
    ens.insert(ens.end(), ens1.begin(), ens1.end());

    for (std::list<sf::Sprite*>::iterator it = ens.begin();it != ens.end();it++)
    {
        if (rect.intersects(sf::IntRect((*it)->getPosition().x,(*it)->getPosition().y,32,32)))
        {
            blocageUpSide = true;
        }
    }
}

void Character::setWeapon(bulletType type)
{
    delete weapon;
    std::string pathBob = defaultWeaPath + "weapons.png";
    switch(type)
    {
    case rifle:
        weapon = new Rifle(pathBob);
        break;
    case sniper:
        weapon = new Sniper(pathBob);
        break;
    case launcher:
        weapon = new Launcher(pathBob);
        break;
    }

}

void Character::razBlocage()
{
    blocageLeftSide = false;
    blocageDownSide = false;
    blocageUpSide = false;
    blocageRightSide = false;
}

void Character::setAnimation(action _action)
{
    currentAnimation->setPosition(position);
}

void Character::build()
{
    sf::Sprite sprite;
    sprite.setTexture(tileset);

    animations = new Animation*[(attack+1)*2];

    //****************************************************************************************
    //animation rien rightDir
    //****************************************************************************************
    Animation* animation = new Animation(15);
    sprite.setTextureRect(sf::IntRect(10,17,57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(72,17,57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(137,17,57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(201,17,57,43));
    animation->addSprite(sprite);

    currAnim = rien*2+rightDir;
    animations[currAnim] = animation;
    currentAnimation = animations[currAnim];

    //****************************************************************************************
    //animation rien leftDir
    //****************************************************************************************
    animation = new Animation(15);
    sprite.setTextureRect(sf::IntRect(10+57,17,-57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(72+57,17,-57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(137+57,17,-57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(201+57,17,-57,43));
    animation->addSprite(sprite);

    animations[rien*2+leftDir] = animation;

    //****************************************************************************************
    //animation walk rightDir
    //****************************************************************************************
    animation = new Animation(15);
    sprite.setTextureRect(sf::IntRect(7,72,57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(75,72,57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(141,72,57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(206,72,57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(272,72,57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(341,72,57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(403,72,57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(473,72,57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(537,72,57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(603,72,57,43));
    animation->addSprite(sprite);

    animations[walk*2+rightDir] = animation;

    //****************************************************************************************
    //animation sprint leftDir
    //****************************************************************************************
    animation = new Animation(15);
    sprite.setTextureRect(sf::IntRect(7+57,72,-57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(75+57,72,-57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(141+57,72,-57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(206+57,72,-57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(272+57,72,-57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(341+57,72,-57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(403+57,72,-57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(473+57,72,-57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(537+57,72,-57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(603+57,72,-57,43));
    animation->addSprite(sprite);

    animations[walk*2+leftDir] = animation;

    //****************************************************************************************
    //animation run rightDir
    //****************************************************************************************
    animation = new Animation(15);
    sprite.setTextureRect(sf::IntRect(14,132,57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(94,132,57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(172,132,57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(245,132,57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(318,132,57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(393,132,57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(466,132,57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(545,132,57,43));
    animation->addSprite(sprite);

    animations[sprint*2+rightDir] = animation;

    //****************************************************************************************
    //animation run leftDir
    //****************************************************************************************
    animation = new Animation(15);
    sprite.setTextureRect(sf::IntRect(14+57,132,-57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(94+57,132,-57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(172+57,132,-57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(245+57,132,-57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(318+57,132,-57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(393+57,132,-57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(466+57,132,-57,43));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(545+57,132,-57,43));
    animation->addSprite(sprite);

    animations[sprint*2+leftDir] = animation;

    //****************************************************************************************
    //animation jump rightDir
    //****************************************************************************************
    animation = new Animation(240);
    sprite.setTextureRect(sf::IntRect(12,213,57,50));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(94,213,57,50));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(163,213,57,50));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(228,213,57,50));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(302,213,57,50));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(370,213,57,50));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(441,213,57,50));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(516,213,57,50));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(581,213,57,50));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(667,213,57,50));
    animation->addSprite(sprite);

    animations[Jump*2+rightDir] = animation;

    //****************************************************************************************
    //animation jump leftDir
    //****************************************************************************************
    animation = new Animation(240);
    sprite.setTextureRect(sf::IntRect(12+57,213,-57,50));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(94+57,213,-57,50));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(163+57,213,-57,50));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(228+57,213,-57,50));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(302+57,213,-57,50));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(370+57,213,-57,50));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(441+57,213,-57,50));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(516+57,213,-57,50));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(581+57,213,-57,50));
    animation->addSprite(sprite);
    sprite.setTextureRect(sf::IntRect(667+57,213,-57,50));
    animation->addSprite(sprite);

    animations[Jump*2+leftDir] = animation;
}

int Character::getCurrentFrameX()
{
    return currX;
}

int Character::getCurrentFrameY()
{
    return currY;
}

sf::Vector2f Character::getPosition()
{
    return position;
}

bool Character::isOnAction()
{
    return onAction;
}

void Character::noUpdate()
{
    currentAnimation->noUpdate();
    weapon->noUpdate();
}

Character::~Character()
{

}



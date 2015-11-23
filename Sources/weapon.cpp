#include "weapon.hpp"


Weapon::Weapon(std::string filePath, int rof, bulletType _type) :
    path(),
    rateOfFire(rof),
    bullet(_type),
    needUpdate(true)
{
    texture.loadFromFile(filePath);
    sprite.setTexture(texture);
    spriteReverse.setTexture(texture);
    timeBetweenFire = 1/(float)rateOfFire;
    deb = clock();
}

void Weapon::draw(sf::RenderWindow* window)
{
    if(needUpdate)
        update(window);
    if(reverse)
        window->draw(spriteReverse);
    else
        window->draw(sprite);

    for(std::list<Bullet*>::iterator it = bullets.begin();it != bullets.end();it++)
    {
        (*it)->update(window);
        (*it)->draw(window);
        if ((*it)->getPortee() <= 0)
        {
            bullets.erase(it);
            delete (*it);
        }
    }

    needUpdate = true;
}

void Weapon::update(sf::RenderWindow* window)
{
    sf::Vector2i localPosition = sf::Mouse::getPosition(*window);
    float x = (float)localPosition.x;
    float y = (float)localPosition.y;

    Force vect(position.x,position.y,decalage.x+x,y);
    Force vectHor(position.x,position.y,position.x+100,position.y);
    //calcul du cosinus de l'angle choisit
    float cosa = vect.produitScalaire(vectHor);
    cosa /= (vect.getNorme() * vectHor.getNorme());
    //calcul du sinus de l'angle choisit
    float sina = vect.normeProduitVectoriel(vectHor);
    sina /= (vect.getNorme() * vectHor.getNorme());
    angle.x = cosa;
    angle.y = sina;
    cosa = (acos(cosa)*180/3.14159);

    if(x+decalage.x > position.x)
    {
        if(cosa < 90 && cosa > -90)
        {
            if(y+decalage.y < position.y)
                sprite.setRotation(-cosa);
            else
                sprite.setRotation(cosa);
        }
        position += sf::Vector2f(offSetX,offSetY);
        sprite.setPosition(position);
        reverse=false;
    }
    else
    {
        if(cosa > 90)
        {
            if(y+decalage.y < position.y)
                spriteReverse.setRotation(-cosa-180);
            else
                spriteReverse.setRotation(cosa-180);
        }
        position += sf::Vector2f(offSetX,offSetY);
        spriteReverse.setPosition(position);
        reverse = true;
    }
}

void Weapon::fire(sf::RenderWindow* window)
{
    fin = clock();
    if((((float)fin-(float)deb)/(float)CLOCKS_PER_SEC) > timeBetweenFire)
    {
        deb = clock();
        addBullet(window);
    }
}

void Weapon::addBullet(sf::RenderWindow* window)
{
    Bullet* bul;
    bul = new Bullet(window,bullet,position,angle,decalage);
    bullets.push_back(bul);
}

void Weapon::noUpdate()
{
    needUpdate = false;
}

void Weapon::setPosition(sf::Vector2f pos)
{
    position = pos;
}

sf::Vector2f Weapon::getPosition()
{
    return position;
}

Weapon::~Weapon()
{

}



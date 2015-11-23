#include "Force.hpp"

Force::Force(int _length,int _decalage) :
    point1(sf::Vector2f(0,0)),
    point2(sf::Vector2f(0,0)),
    length(_length),
    debLength(_length),
    decalage(_decalage),
    debDecalage(_decalage)
{}

Force::Force(float x1, float y1, float x2, float y2,int _length,int _decalage) :
    point1(sf::Vector2f(x1,y1)),
    point2(sf::Vector2f(x2,y2)),
    length(_length),
    debLength(_length),
    decalage(_decalage),
    debDecalage(_decalage)
{}

Force::Force(sf::Vector2f pointDep, sf::Vector2f pointFin,int _length,int _decalage) :
    point1(pointDep),
    point2(pointFin),
    length(_length),
    debLength(_length),
    decalage(_decalage),
    debDecalage(_decalage)
{}

Force::Force(sf::Vector2f pointFin,int _length,int _decalage) :
    point1(sf::Vector2f(0,0)),
    point2(pointFin),
    length(_length),
    debLength(_length),
    decalage(_decalage),
    debDecalage(_decalage)
{}

sf::Vector2f Force::getForce()
{
    if(decalage == 0)
    {
        if (debLength != -1)
            return sf::Vector2f((point2.x-point1.x)*(float)((float)length/(float)debLength),(point2.y-point1.y)*(float)((float)length/(float)debLength));
        else if (debLength == -1)
            return sf::Vector2f((point2.x-point1.x),(point2.y-point1.y));
    }
    else
    {
        return sf::Vector2f(0,0);
    }

}

float Force::produitScalaire(Force vect)
{
    return (getForce().x*vect.getForce().x+getForce().y*vect.getForce().y);
}

sf::Vector3f Force::produitVectoriel(Force vect)
{
    sf::Vector3f vect3d;
    vect3d.x = 0;
    vect3d.y = 0;
    vect3d.z = getForce().x*vect.getForce().y-getForce().y*vect.getForce().x;
    return vect3d;
}

float Force::normeProduitVectoriel(Force vect)
{
    sf::Vector3f vect3d = produitVectoriel(vect);
    float carreZ = pow(vect3d.z,2);
    return (float) sqrt(carreZ);
}

float Force::getNorme()
{
    float carreX = pow((getForce().x),2);
    float carreY = pow((getForce().y),2);
    return (float) sqrt(carreX+carreY);
}

void Force::decreaseLength()
{
    if (decalage == 0)
        length--;
    else
        decalage --;
}

void Force::decrease()
{

}

int Force::getLength()
{
    return length;
}

Force::~Force()
{

}


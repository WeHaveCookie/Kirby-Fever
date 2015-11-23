#ifndef FORCE_HPP
#define FORCE_HPP
#include <SFML/System.hpp>
#include <math.h>
class Force
{
public:
    Force(int _length=30,int _decalage = 0);
    Force(float x1, float y1, float x2, float y2,int _length=30,int _decalage = 0);
    Force(sf::Vector2f pointDep, sf::Vector2f pointFin,int _length=30,int _decalage = 0);
    Force(sf::Vector2f pointFin,int _length=30,int _decalage = 0);
    sf::Vector2f getForce();
    sf::Vector3f produitVectoriel(Force vect);
    float produitScalaire(Force vect);
    float normeProduitVectoriel(Force vect);
    float getNorme();
    void decreaseLength();
    void decrease();
    int getLength();
    ~Force();
private:
    sf::Vector2f point1;
    sf::Vector2f point2;
    int length;
    int debLength;
    int decalage;
    int debDecalage;

};

#endif // FORCE_HPP

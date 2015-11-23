#ifndef COULDGETFORCE_H
#define COULDGETFORCE_H
#include "Force.hpp"
#include <vector>
#include <iostream>

class CouldGetForce
{
public:
    CouldGetForce();
    void addForce(Force force);
    sf::Vector2f applyForce();
    ~CouldGetForce();
protected:
private:
    void update();
    std::vector<Force> forces;

};

#endif // COULDGETFORCE_H

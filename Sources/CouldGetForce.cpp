#include "CouldGetForce.h"

CouldGetForce::CouldGetForce()
{

}
void CouldGetForce::addForce(Force force)
{
    forces.push_back(force);
}

sf::Vector2f CouldGetForce::applyForce()
{
    sf::Vector2f temp(0,0);
    for (int i(0);i<forces.size();i++)
    {
        temp.x += forces[i].getForce().x;
        temp.y += forces[i].getForce().y;
    }
    update();
    return temp;
}

void CouldGetForce::update()
{
    std::vector<int> vectToDelete;
    for (int i(0);i<forces.size();i++)
    {
        forces[i].decreaseLength();
        if(forces[i].getLength() == 0)
            vectToDelete.push_back(i);
    }
    for (int i(0);i<vectToDelete.size();i++)
    {
        forces.erase(forces.begin()+vectToDelete[i]);
    }

}

CouldGetForce::~CouldGetForce()
{

}

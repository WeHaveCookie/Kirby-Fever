#include "menuAnimation.hpp"


MenuAnimation::MenuAnimation(std::string path,int _length) :
    beginIndex(1),
    current(1),
    length(84),
    latence(2),
    currLatence(0)
{
    textures = new sf::Texture[length];
    std::string pathFile;
    char* buffer = new char[2];
    for(int i(0);i<length;i++)
    {
        pathFile = path;
        itoa(i,buffer,10);
        pathFile += buffer;
        pathFile += ".png";
        textures[i].loadFromFile(pathFile);
    }
    sprite.setTexture(textures[1]);
}

void MenuAnimation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    target.draw(sprite,states);
}

void MenuAnimation::update()
{
    if(currLatence%latence == 0)
    {
        current++;
        if(current>length)
        {
            current = 1;
        }
        sprite.setTexture(textures[current]);
    }
    currLatence++;
}

MenuAnimation::~MenuAnimation()
{

}

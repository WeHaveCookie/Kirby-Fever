#include "Animation.hpp"

Animation::Animation(int _latence) : latence(0),currLatence(_latence),
    needUpdate(true)
{

}

void Animation::update()
{
    if (needUpdate)
    {
        if (latence%currLatence != 0)
        {
            if(it == (sprites.size()-1))
                it = 0;
            else
                it++;
            latence = 0;
        }
        else
            latence++;
    }
    needUpdate = true;
}

bool Animation::isEnd()
{
    return it == sprites.size()-1;
}

void Animation::reload()
{
    it = 0;
}

void Animation::noUpdate()
{
    needUpdate = false;
}

sf::Sprite Animation::getCurrentSprite()
{
    sprites[it].setPosition(position);
    return sprites[it];
}

void Animation::setPosition(sf::Vector2f _position)
{
    position = _position;
}

sf::Vector2f Animation::getPosition()
{
    return position;
}

void Animation::moveSprite(sf::Vector2f pos)
{
    position += pos;
}

void Animation::addSprite(sf::Sprite sprite)
{
    sprites.push_back(sprite);
    it = 0;
}

Animation::~Animation()
{

}


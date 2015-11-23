#include "QuadTree.hpp"


using namespace std;

QuadTree::QuadTree(float _x, float _y, float _width, float _height, int _level, int _maxLevel) :
    x	(_x),
    y	(_y),
    width	(_width),
    height	(_height),
    level	(_level),
    maxLevel(_maxLevel),
    enable(true)
{
    color = sf::Color::Green;
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color(0, 0, 0, 0));
    shape.setOutlineThickness(1.0f);
    shape.setOutlineColor(color);


    if (level == maxLevel)
    {
        return;
    }

    NW = new QuadTree(x, y, width / 2.0f, height / 2.0f, level+1, maxLevel);
    NE = new QuadTree(x + width / 2.0f, y, width / 2.0f, height / 2.0f, level+1, maxLevel);
    SW = new QuadTree(x, y + height / 2.0f, width / 2.0f, height / 2.0f, level+1, maxLevel);
    SE = new QuadTree(x + width / 2.0f, y + height / 2.0f, width / 2.0f, height / 2.0f, level+1, maxLevel);
}

QuadTree::~QuadTree()
{
    if (level == maxLevel)
    return;

    delete NW;
    delete NE;
    delete SW;
    delete SE;
}

void QuadTree::AddObject(sf::Sprite *object) {
    if (level == maxLevel)
    {
        objects.push_back(object);
        return;
    }
    if (contains(NW, object))
    {
        NW->AddObject(object);
        return;
    }
    else if (contains(NE, object))
    {
        NE->AddObject(object);
        return;
    }
    else if (contains(SW, object))
    {
        SW->AddObject(object);
        return;
    }
    else if (contains(SE, object))
    {
        SE->AddObject(object);
        return;
    }
    if (contains(this, object))
    {
        objects.push_back(object);
    }
}

list<sf::Sprite*> QuadTree::GetObjectsAt(float _x, float _y)
{
    if (level == maxLevel)
    {
        return objects;
    }
    list<sf::Sprite*> returnObjects, childReturnObjects;
    if (!objects.empty())
    {
        returnObjects = objects;
    }
    if (_x > x + width / 2.0f && _x < x + width)
    {
        if (_y > y + height / 2.0f && _y < y + height)
        {
            childReturnObjects = SE->GetObjectsAt(_x, _y);
            returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
            return returnObjects;
        }
        else if (_y >= y && _y <= y + height / 2.0f)
        {
            childReturnObjects = NE->GetObjectsAt(_x, _y);
            returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
            return returnObjects;
        }
    }
    else if (_x > x && _x < x + width / 2.0f) //_x = 500    x=0    width = 3200   _y=0   y=0
    {
        if (_y > y + height / 2.0f && _y < y + height)
        {
            childReturnObjects = SW->GetObjectsAt(_x, _y);
            returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
            return returnObjects;
        }
        else if (_y >= y && _y <= y + height / 2.0f)
        {
            childReturnObjects = NW->GetObjectsAt(_x, _y);
            returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
            return returnObjects;
        }
    }
    return returnObjects;
}

list<sf::Sprite*>	QuadTree::GetObjects(float x, float y)
{
    list<sf::Sprite*> returnObjects;
    for (std::list<sf::Sprite*>::iterator it = objects.begin(); it != objects.end(); it++)
    {
        if ((*it)->getPosition().x >= x && (*it)->getPosition().x<= x+width&&(*it)->getPosition().y >= y &&(*it)->getPosition().y <= y+height)
            returnObjects.push_back((*it));
    }
    return returnObjects;
}

void QuadTree::Clear()
{
    if (level == maxLevel)
    {
        objects.clear();
        return;
    }
    else {
    NW->Clear();
    NE->Clear();
    SW->Clear();
    SE->Clear();
}
    if (!objects.empty())
    {
        objects.clear();
    }
}

void QuadTree::Draw(sf::RenderWindow* window)
{
    window->draw(shape);
    if (level != maxLevel)
    {
        NW->Draw(window);
        NE->Draw(window);
        SW->Draw(window);
        SE->Draw(window);
    }
}

bool QuadTree::contains(QuadTree *child, sf::Sprite *object) {
return	!(  object->getPosition().x >= child->x + child->width ||
            object->getPosition().y >= child->y + child->height ||
            object->getPosition().x + 32 <= child->x ||
            object->getPosition().y + 32 <= child->y );
}

void QuadTree::AfficherTree()
{
    if (level == maxLevel)
        return;
    std::cout << level << std::endl;
    NW->AfficherTree();
    NE->AfficherTree();
    SW->AfficherTree();
    SE->AfficherTree();
}


int QuadTree::getMinWidth()
{
    if (level == maxLevel)
        return width;
    else
        NW->getMinWidth();
}

int QuadTree::getMinHeight()
{
    if (level == maxLevel)
        return height;
    else
        NW->getMinHeight();
}


void QuadTree::SetColor(sf::Color couleur)
{
    if (enable)
    {
        color = couleur;
        shape.setOutlineColor(color);

        if (level == maxLevel)
            return;

        NW->SetColor(color);
        NE->SetColor(color);
        SW->SetColor(color);
        SE->SetColor(color);
    }
}

void QuadTree::Disable()
{
    enable = false;
}

bool QuadTree::getIntersect(Bullet* bullet)
{
    std::list<sf::Sprite*> temp = GetObjectsAt(bullet->getPosition().x,bullet->getPosition().y);
    for(std::list<sf::Sprite*>::iterator it = temp.begin();it!=temp.end();it++)
    {
        if(bullet->getBound().intersects((*it)->getLocalBounds()))
        {
            deleteObjectAt(bullet->getPosition().x,bullet->getPosition().y+50);
            return true;
        }

    }
    return false;
}

void QuadTree::deleteObjectAt(float _x,float _y)
{
    if (level == maxLevel)
    {
        for(std::list<sf::Sprite*>::iterator it = objects.begin();it!=objects.end();it++)
        {
            if(sf::FloatRect(_x,_y,32,32).intersects(sf::FloatRect((*it)->getPosition().x,(*it)->getPosition().y,32,32)))
            {
                objects.clear();
            }
        }
        return;
    }
    if (_x > x + width / 2.0f && _x < x + width)
    {
        if (_y > y + height / 2.0f && _y < y + height)
        {
            SE->deleteObjectAt(_x, _y);
        }
        else if (_y >= y && _y <= y + height / 2.0f)
        {
            NE->deleteObjectAt(_x, _y);
        }
    }
    else if (_x > x && _x < x + width / 2.0f)
    {
        if (_y > y + height / 2.0f && _y < y + height)
        {
            SW->deleteObjectAt(_x, _y);
        }
        else if (_y >= y && _y <= y + height / 2.0f)
        {
            NW->deleteObjectAt(_x, _y);
        }
    }

}

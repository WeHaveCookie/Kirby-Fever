#include "Game.hpp"


Game::Game(sf::RenderWindow* _window) :
    window(_window),
    gameIsRunning(true)
{
    std::string path = defaultLevelPath+"mainLevel.level";
    setLevel(path);
    view = window->getDefaultView();
}

void Game::setLevel(std::string path)
{
    level = new Level(path);
}

void Game::launch()
{
    //Variables SFML
    sf::Event Event;
    //Variables du jeu
    Character* kirby;
    kirby = new Character(this,"kirby.png");
    int sizeX = level->getSizeX();
    int sizeY = level->getSizeY();
    bool moveR = false;
    bool moveL = false;
    bool jump = false;
    tree = level->createQuadTree();

    while (gameIsRunning)
    {
        window->clear(sf::Color::Cyan);
        while (window->pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed)
                window->close();
            if(Event.type == sf::Event::KeyPressed)
            {
                if (Event.key.code == sf::Keyboard::Escape)
                {
                    if (!menu.isEnabled())
                        menu.enable();
                    else
                        menu.disable();
                }
            }
        }

        if(!menu.isEnabled())
        {
            //gestion mouvement
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {kirby->move(4,0); moveR = true;}
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {kirby->move(-4,0); moveL = true;}
            else
            {kirby->doNothing();}
            //Gestion saut
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {kirby->jump(); jump = true;}
            //Gestion des armes
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {kirby->getWeapon()->fire(window);}
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
            {kirby->setWeapon(rifle);}
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
            {kirby->setWeapon(sniper);}
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::F3))
            {kirby->setWeapon(launcher);}
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::F4))
            {kirby->enableWeapon();}
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
            {kirby->disableWeapon();}
            //gestion vue
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {view.move(-4,0);}
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {view.move(4,0);}
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {view.move(0,-4);}
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {view.move(0,4);}
        }
        else
        {
            switch(menu.choixMenu(window))
            {
                case 0:
                    menu.disable();
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    gameIsRunning = false;
                    break;
                case 4:
                    exit(0);
                    break;
            }
            kirby->noUpdate();
            menu.razMenu();
            menu.updateMenu(window);
        }

        level->drawMap(window);
        kirby->draw(window);
        //tree->Draw(window);

        //Gestion scrolling
        if(kirby->getPosition().x+57 >= (decalageVue.x+view.getSize().x*0.8) && (decalageVue.x+view.getSize().x) <= sizeX && (moveR ||jump))
        {
            decalageVue.x += kirby->getCurrentFrameX();
            view.move(kirby->getCurrentFrameX(),0);
        }
        else if (kirby->getPosition().x <= (decalageVue.x+view.getSize().x*0.2) && decalageVue.x > 0 && (moveL || jump))
        {
            decalageVue.x += kirby->getCurrentFrameX();
            view.move(kirby->getCurrentFrameX(),0);
        }
        if(kirby->getPosition().y+43 >= (decalageVue.y+view.getSize().y*0.8) && (decalageVue.y+view.getSize().y) <= sizeY)
        {
            decalageVue.y += kirby->getCurrentFrameY();
            view.move(0,kirby->getCurrentFrameY());
        }
        else if (kirby->getPosition().y <= (decalageVue.y+view.getSize().y*0.2) && decalageVue.y > 0 && jump)
        {
            decalageVue.y += kirby->getCurrentFrameY();
            view.move(0,-kirby->getCurrentFrameX());
        }


        window->setView(view);
        //Fin gestion scrolling

        if(menu.isEnabled())
            menu.draw(window);
        window->display();
        moveR = false;
        moveL = false;
        jump = false;
    }
}

sf::RenderWindow* Game::getWindow()
{
    return window;
}

QuadTree* Game::getQuadTree()
{
    return tree;
}

Game::~Game()
{

}

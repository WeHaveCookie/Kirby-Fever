#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "constantes.hpp"
#include "mainMenu.hpp"
#include "menuAnimation.hpp"
#include "Game.hpp"

void Demarrer_jeu(sf::RenderWindow* window);


int main()
{
    MainMenu menu;
    sf::RenderWindow App(sf::VideoMode (LARGEURFENETRE, HAUTEURFENTRE, 32),"Kirby Fever 1.0");
    App.setFramerateLimit(30);
    sf::Event Event;

    //Options option;

    MenuAnimation animation("./Ressources/Menu/Animation/File-",90);

    while (App.isOpen ())
    {
        while (App.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed)
            {
                App.close();
            }
        }
        switch(menu.choixMenu(&App))
        {
            case 0:
                Demarrer_jeu(&App);
                break;
            case 1:
                //Demarrer_jeu(window);
                break;
            case 2:
                //Demarrer_options(window);
                break;
            case 3:
                //Demarrer_credits(window);
                break;
            case 4:
                App.close();
                break;
        }
        App.clear(sf::Color::Cyan);
        App.draw(animation);
        animation.update();
        menu.update(&App);
        App.draw(menu);
        App.display();
        menu.razMenu();
    }
    return 0;
}

void Demarrer_jeu(sf::RenderWindow* window)
{
    Game jeu(window);
    jeu.launch();
}

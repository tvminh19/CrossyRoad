#include "CMenu.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(750, 450), "Road crossing");
    CMenu menu(window.getSize().x, window.getSize().y);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::W:
                    menu.MoveUp();
                    break;
                case sf::Keyboard::S:
                    menu.MoveDown();
                    break;
                case sf::Keyboard::Return:
                    switch (menu.get_choice())
                    {
                    case 0:
                        //New game
                        break;
                    case 1:
                        //Load game
                        break;
                    case 2:
                        //Ranking
                        break;
                    case 3:
                        //Setting
                        break;
                    case 4:
                        //Exit
                        window.close();
                        break;
                    default:
                        break;
                    }
                default:
                    break;
                }
                break;
            case sf::Event::Closed:
                window.close();
                exit(0);
                break;
            default:
                break;
            }
            
        }

        window.clear();

        menu.draw(window);

        window.display();
    }

    return 0;
}


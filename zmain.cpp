#include "Menu.h"

int main(){
    Menu menu;
	sf::RenderWindow* window = menu.getWindow();
    menu.play_sound();
    while (window->isOpen()){
        sf::Event event;
        while (window->pollEvent(event)){
            switch (event.type){ 
			case sf::Event::KeyReleased:
				switch (event.key.code){
				case sf::Keyboard::W:
					menu.MoveUp();
					break;
				case sf::Keyboard::S:
					menu.MoveDown();
					break;
				case sf::Keyboard::Return:
					switch (menu.get_choice()){
						case 0:
							window->clear();
							menu.newGame();
							break;
						case 1:
							//Load game
							window->clear();
							menu.LoadGame(*window);
							break;
						case 2:
							//Ranking
							break;
						case 3:
							menu.set_sound();
							break;
						case 4:
							//Exit
							std::cout << "GAME STOPPED!\n";
							window->close();
							break;
						default:
							break;
					}
					break;
				default:
					break;
				}
				break;
			case sf::Event::Closed:
				exit(0);
				break;
			default:
				break;
            }
            window->clear();
            menu.draw(*window);
            window->display();
        }
    }

    return 0;
}

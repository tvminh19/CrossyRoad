#ifndef _CTRAFFIC_LANE_H_
#define _CTRAFFIC_LANE_H_
#include "Enemy.h"
#include "Bird.h"
#include "Car.h"
#include "Truck.h"
#include "Dinasour.h"
#include <ctime>

class TrafficLane{
private:
    float enemySpawnTimer=20.f;
    float enemySpawnTImerMax=20.f;

    Bird* bird;
    Car* car;
    Truck* truck;
    Dinasour* dinasour;

    std::vector<Enemy*> enemies;
public:
    void update(sf::RenderWindow& window){
        if (this->enemies.size() < 10)
        {
            if (this->enemySpawnTimer >= this->enemySpawnTImerMax)
            {
                this->spawnEnemy(window);
                this->enemySpawnTimer = 0.f;
            }
            else
                this->enemySpawnTimer += 1.f;
        }

        for (int i = 0; i < enemies.size(); ++i) {
            enemies[i]->setSpeed(10.f,0.f);
            enemies[i]->update();
            if (enemies[i]->shape.getPosition().x > window.getSize().x) {
                this->enemies.erase(this->enemies.begin() + i);
            }
        }
    }

    void spawnEnemy(sf::RenderWindow& window){
        int t = rand() % 4; 
        Enemy* tmp=nullptr;
        if (t==0){
            tmp = new Bird;
        }
        else if (t==1){
            tmp = new Car;
        }
        else if (t==2){
            tmp = new Truck;
        }
        else if (t==3){
            tmp = new Dinasour;
        }
        tmp->shape.setPosition(
            0.f,
            // static_cast<float>(rand() % static_cast<int>(window.getSize().y + tmp->shape.getSize().y))
            static_cast<int>((rand() % 5) * (tmp->shape.getSize().x + 20.f))
        );
        this->enemies.push_back(tmp);
    }

    void renderEnemies(sf::RenderWindow& window){
        for (auto& e: this->enemies){
            window.draw(e->shape);
        }
    }
};


#endif // !_CTRAFFIC_LANE_H_

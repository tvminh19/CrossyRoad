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
    float enemySpawnTimer;
    float enemySpawnTImerMax=3.f;

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
                this->spawnEnemy();
                this->enemySpawnTimer = 0.f;
            }
            else
                this->enemySpawnTimer += 1.f;
        }

        for (int i = 0; i < enemies.size(); ++i) {
            enemies[i]->update();
            if (enemies[i]->shape.getPosition().x > window.getSize().x) {
                this->enemies.erase(this->enemies.begin() + i);
            }
        }
    }

    void spawnEnemy(){
        int t = rand() % 4; 
        if (t==0){
            this->bird = new Bird;
            this->bird->init();
            this->bird->shape.setPosition(
                0.f,
                static_cast<int>((rand() % 5) * (this->bird->shape.getSize().x))
            );
            this->enemies.push_back(this->bird);
        }
        else if (t==1){
            this->car = new Car;
            this->car->init();
            this->car->shape.setPosition(
                0.f,
                static_cast<int>((rand() % 5) * (this->car->shape.getSize().x))
            );
            this->enemies.push_back(this->car);
        }
        else if (t==2){
            this->truck = new Truck;
            this->truck->init();
            this->truck->shape.setPosition(
                0.f,
                static_cast<int>((rand() % 5) * (this->truck->shape.getSize().x))
            );
            this->enemies.push_back(this->truck);
        }
        else if (t==3){
            this->dinasour = new Dinasour;
            this->dinasour->init();
            this->dinasour->shape.setPosition(
                0.f,
                static_cast<int>((rand() % 5) * (this->dinasour->shape.getSize().x))
            );
            this->enemies.push_back(this->dinasour);
        }
    }

    void renderEnemies(sf::RenderWindow& window){
        for (auto& e: this->enemies){
            window.draw(e->shape);
        }
    }
};


#endif // !_CTRAFFIC_LANE_H_

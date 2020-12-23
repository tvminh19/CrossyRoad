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

    bool isRed=false;
    int trafficTimeRed=3;
    int trafficTimeGreen=10;
    sf::Clock clock;

    int lane=0;
public:

    void update(sf::RenderWindow& window, int level){
        if (this->enemies.size() < 8)
        {
            if (this->enemySpawnTimer >= this->enemySpawnTImerMax)
            {
                this->spawnEnemy(window);
                this->enemySpawnTimer = 0.f;
            }
            else
                this->enemySpawnTimer += 0.5f+float(level)/5;
        }

        for (int i = 0; i < enemies.size(); ++i) {
            if (!isRed){
                enemies[i]->setSpeed(float(5+level),0.f);
                if (clock.getElapsedTime()>sf::seconds(trafficTimeGreen)){ //TODO
                    this->isRed=true;
                    clock.restart();
                }
            }
            else {
                enemies[i]->setSpeed(0.f,0.f);
                if (clock.getElapsedTime()>sf::seconds(trafficTimeRed)){ //TODO
                    this->isRed=false;
                    clock.restart();
                }
            }
            enemies[i]->update();//TODO
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
        int k=rand()%5;

        if (k!=lane){
            lane=k;
        }else{
            lane=(k+1)%5;
        }

        tmp->shape.setPosition(
            0.f,
            // static_cast<float>(rand() % static_cast<int>(window.getSize().y + tmp->shape.getSize().y))
            static_cast<int>(this->lane * (tmp->shape.getSize().y + 20.f))
        );
        this->enemies.push_back(tmp);
    }

    void renderEnemies(sf::RenderWindow& window){
        for (auto& e: this->enemies){
            window.draw(e->shape);
        }
    }

    bool checkCollision(sf::FloatRect other){
        for (auto& e : this->enemies){
            if (e->shape.getGlobalBounds().intersects(other)){
                // return true; //TODO
                return false;
            }
        }
        return false;
    }

    void resetClock(){
        this->clock.restart();
    }
    
};


#endif // !_CTRAFFIC_LANE_H_

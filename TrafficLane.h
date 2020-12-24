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
    std::vector<int> light;

    bool isRed=false;
    int trafficTimeRed=3;
    int trafficTimeGreen=5;
    sf::Clock clock;

    int lane=0;
    bool traffic[5]={0,0,0,0,0};
public:

    void update(sf::RenderWindow& window, int level){
        if (this->enemies.size() < 10+level)
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
            enemies[i]->setSpeed(float(5+level),0.f);
            if (clock.getElapsedTime()>sf::seconds(1+rand()%5)){ //TODO
                srand(time(NULL));
                for (int i=0; i<5; ++i){
                    traffic[i]=rand()%2;
                }
                clock.restart();
            }



            if (canMove(light[i]))
                enemies[i]->update();//TODO
            if (enemies[i]->shape.getPosition().x > window.getSize().x) {
                this->enemies.erase(this->enemies.begin() + i);
                this->light.erase(this->light.begin() + i);
            }
        }
    }

    bool canMove(int _lane){
        for (int i=0; i<5; ++i){
            if (traffic[_lane]==1){
                return false;
            }
        }
        return true;
    }

    void spawnEnemy(sf::RenderWindow& window){
        int k=rand()%5;

        if (k!=lane){
            lane=k;
        }else if (k==lane){
            lane=(k+1)%5;
        }

        if (canMove(lane)){
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
                -80.f,
                // static_cast<float>(rand() % static_cast<int>(window.getSize().y + tmp->shape.getSize().y))
                static_cast<int>(this->lane * (tmp->shape.getSize().y + 20.f))
            );
            this->enemies.push_back(tmp);
            this->light.push_back(lane);
        }
    }

    void renderEnemies(sf::RenderWindow& window){
        for (auto& e: this->enemies){
            window.draw(e->shape);
        }
    }

    bool checkCollision(sf::FloatRect other){
        for (auto& e : this->enemies){
            if (e->shape.getGlobalBounds().intersects(other)){
                return true; //TODO
                // return false;
            }
        }
        return false;
    }

    void resetClock(){
        this->clock.restart();
    }
    
};


#endif // !_CTRAFFIC_LANE_H_

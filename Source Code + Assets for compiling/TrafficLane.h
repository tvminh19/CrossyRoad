#ifndef _CTRAFFIC_LANE_H_
#define _CTRAFFIC_LANE_H_
#include "Enemy.h"
#include "Bird.h"
#include "Car.h"
#include "Truck.h"
#include "Dinasour.h"
#include "TrafficLight.h"
#include <ctime>

class TrafficLane{
private:
    float enemySpawnTimer=20.f;
    float timeForSpawnEnemy=20.f;

    Bird* bird;
    Car* car;
    Truck* truck;
    Dinasour* dinasour;

    std::vector<TrafficLight*> trafficLight;

    std::vector<Enemy*> enemies;
    std::vector<int> light;

    bool isRed=false;
    int trafficTimeRed=3;
    int trafficTimeGreen=5;
    sf::Clock clock;

    int lane=0;
    bool traffic[5]={0,0,0,0,0};
public:
    TrafficLane();

    ~TrafficLane();

    void update(sf::RenderWindow& window, int level);

    bool canMove(int _lane);

    void spawnEnemy(sf::RenderWindow& window);

    void renderEnemies(sf::RenderWindow& window);

    void renderTrafficLight(sf::RenderWindow& window);

    bool checkCollision(sf::FloatRect other);

    void resetClock();
    
};


#endif // !_CTRAFFIC_LANE_H_

#include "TrafficLane.h"

TrafficLane::TrafficLane() {
    for (int i=0; i<5; ++i){
        TrafficLight* tmp=new TrafficLight;
        tmp->setPosition(
            0,
            static_cast<int>(i * (tmp->getShape().getSize().y + 70.f)) + 20.f
        );
        trafficLight.push_back(tmp);
    }
}

TrafficLane::~TrafficLane() {
    for (int i=0; i<enemies.size(); ++i){
        delete enemies[i];
    }
    for (int i=0; i<5; ++i){
        delete trafficLight[i];
    }
}

void TrafficLane::update(sf::RenderWindow& window, int level) {
    //update traffic light
    for (int i=0; i<5; ++i){
        this->trafficLight[i]->update(!canMove(i));
    }

    if (this->enemies.size() < 10+level)
    {
        if (this->enemySpawnTimer >= this->timeForSpawnEnemy)
        {   
            this->spawnEnemy(window);
            this->enemySpawnTimer = 0.f;
        }
        else
            this->enemySpawnTimer += 0.5f+float(level)/5;
    }

    for (int i = 0; i < enemies.size(); ++i) {
        enemies[i]->setSpeed(float(5+level),0.f);
        //time for swich traffic light
        if (clock.getElapsedTime()>=sf::seconds(1+rand()%5)){ //TODO
            srand(time(NULL));
            for (int i=0; i<5; ++i){
                traffic[i]=rand()%2;
            }
            clock.restart();
        }
        if (canMove(light[i]))
            enemies[i]->update();//TODO
        //out of screen
        if (enemies[i]->shape.getPosition().x > window.getSize().x) {
            this->enemies.erase(this->enemies.begin() + i);
            this->light.erase(this->light.begin() + i);
        }
    }
}

bool TrafficLane::canMove(int _lane) {
    if (traffic[_lane]==1){
        return false;
    }
    return true;
}

void TrafficLane::spawnEnemy(sf::RenderWindow& window) {
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

void TrafficLane::renderEnemies(sf::RenderWindow& window) {
    for (auto& e: this->enemies){
        window.draw(e->shape);
    }
    // window.display();
}

void TrafficLane::renderTrafficLight(sf::RenderWindow& window) {
    for (auto& e: this->trafficLight){
        window.draw(e->getShape());
    }
    // window.display();
}

bool TrafficLane::checkCollision(sf::FloatRect other) {
    for (auto& e : this->enemies){
        if (e->shape.getGlobalBounds().intersects(other)){
            return true; //TODO
            // return false;
        }
    }
    return false;
}

void TrafficLane::resetClock() {
    this->clock.restart();
}




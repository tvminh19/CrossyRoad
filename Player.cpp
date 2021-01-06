#include "Player.h"

Player::Player() {
    this->shape.setSize(sf::Vector2f(50.f, 50.f));
    // this->shape.setOutlineColor(sf::Color::Red);
    // this->shape.setFillColor(sf::Color::White);
    this->shape.setPosition(sf::Vector2f(540, 660));
    this->texture.loadFromFile("frog.png");
    this->shape.setTexture(&texture);
    this->texture.setSmooth(true);
}

void Player::init(){
    this->shape.setSize(sf::Vector2f(50.f, 50.f));
    // this->shape.setOutlineColor(sf::Color::Red);
    // this->shape.setFillColor(sf::Color::White);
    this->shape.setPosition(sf::Vector2f(540, 660));
    this->texture.loadFromFile("frog.png");
    this->shape.setTexture(&texture);
    this->texture.setSmooth(true);
}

void Player::update(sf::RenderWindow& window){
    // time=clock.restart().asSeconds();
    if (this->clock.getElapsedTime()>time){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
            if (canMove(window, sf::Vector2f(-50,0))){
                // this->shape.setRotation(-90);
                this->left();
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
            if (canMove(window, sf::Vector2f(50,0))){
                // this->shape.setRotation(90);
                this->right();
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
            if (canMove(window, sf::Vector2f(0, -50)))
                this->up();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
            if (canMove(window, sf::Vector2f(0, 50))){
                // this->shape.setRotation(180);
                this->down();
            }
        }
        clock.restart();
    }
}

void Player::up() {
    // this->shape.move(0.f, -5.f);
    this->shape.setPosition(this->shape.getPosition()+sf::Vector2f(0, -50));
}

void Player::down() {
    // this->shape.move(0.f, 5.f);
    this->shape.setPosition(this->shape.getPosition()+sf::Vector2f(0, 50));
}

void Player::right() {
    // this->shape.move(5.f, 0.f);
    this->shape.setPosition(this->shape.getPosition()+sf::Vector2f(50, 0));
}

void Player::left() {
    // this->shape.move(-5.f, 0.f);
    this->shape.setPosition(this->shape.getPosition()+sf::Vector2f(-50, 0));
}

void Player::render(sf::RenderWindow& window) {
    window.draw(this->shape);
}

bool Player::canMove(sf::RenderWindow& window, sf::Vector2f trans) {
    sf::Vector2f vec2GlobalPos(this->shape.getPosition()+trans);
    sf::Vector2f vec2LocalPoint;
    sf::Vector2f vec2PointPosition;

    for (unsigned int i = 0; i < this->shape.getPointCount(); i++)
    {
        // set relative position of the current point
        vec2LocalPoint = (this->shape.getPoint(i) - this->shape.getOrigin());
        // Adds the objects global position to the points relitive position to get the points actual position
        vec2PointPosition = (vec2GlobalPos + vec2LocalPoint);

        if (vec2PointPosition.x > window.getSize().x)		{ return false; } // too far left
        else if (vec2PointPosition.y > window.getSize().y)	{ return false; } // too far down
        else if (vec2PointPosition.x < 0)	{ return false; } // too far right
        else if (vec2PointPosition.y < 0)	{ return false; } // too far up
    }
    return true; 
}

sf::RectangleShape Player::getShape() {
    return this->shape;
}

void Player::reset() {
    this->shape.setPosition(sf::Vector2f(540, 660));
}







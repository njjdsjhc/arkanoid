#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

class Paddle;

class Ball {
public:
    Ball();
    void  update(float dt, const Paddle& paddle); 
    void  draw(sf::RenderWindow& win) const; 

    void  launch();
    bool  isLaunched() const { return launched_; }

    void  bounceX()              { vel_.x = -vel_.x; }
    void  bounceY()              { vel_.y = -vel_.y; }

    void  setVel(sf::Vector2f v) { vel_ = v; }
    void  setPos(sf::Vector2f p) { circle_.setPosition(p); }

    void  multiplySpeed(float factor); 
    float speed() const;

    sf::FloatRect bounds() const { return circle_.getGlobalBounds(); } 
    sf::Vector2f  pos()    const { return circle_.getPosition(); }
    sf::Vector2f  vel()    const { return vel_; } 

    bool  alive()   const { return alive_; } 
    void  kill()          { alive_ = false; }
    void  attachTo(const Paddle& paddle); 

    void  stick(); 
    bool  isStuck() const { return stuck_; }
    void  unstick();

private:
    sf::CircleShape circle_;
    sf::Vector2f    vel_{0.f, 0.f}; 
    sf::Vector2f    savedVel_{0.f, 0.f}; 
    bool            launched_ = false;
    bool            alive_    = true;
    bool            stuck_    = false;
};

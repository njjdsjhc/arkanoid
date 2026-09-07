#include "Ball.h"
#include "Paddle.h"
#include <cmath>
#include <algorithm>

Ball::Ball() { 
    circle_.setRadius(BALL_RADIUS);
    circle_.setOrigin(BALL_RADIUS, BALL_RADIUS);
    circle_.setFillColor(sf::Color::White);
    circle_.setPosition((float)WINDOW_W * HALF, PADDLE_Y - BALL_RADIUS - BALL_OFFSET_Y);
}

void Ball::attachTo(const Paddle& p) { 
    circle_.setPosition(p.centerX(), PADDLE_Y - BALL_RADIUS - BALL_OFFSET_Y); 
}

void Ball::launch() { 
    if (!launched_) {
        vel_      = sf::Vector2f(BALL_SPEED * BALL_LAUNCH_VX, -BALL_SPEED); 
        launched_ = true;
        stuck_    = false;
    } else if (stuck_) {
        unstick();
    }
}

void Ball::stick() { 
    savedVel_ = vel_; 
    vel_      = {0.f, 0.f}; 
    stuck_    = true; 
}

void Ball::unstick() { 
    vel_   = savedVel_; 
    if (vel_.y > 0.f) vel_.y = -vel_.y; 
    stuck_ = false;
}

float Ball::speed() const { 
    return std::sqrt(vel_.x * vel_.x + vel_.y * vel_.y);
}

void Ball::multiplySpeed(float factor) { 
    float s = speed();
    if (s < BALL_SPEED_EPS) return;
    float ns = std::clamp(s * factor, BALL_SPEED * BALL_MIN_SPEED_MUL, BALL_MAX_SPEED); 
    vel_ *= (ns / s); 
}

void Ball::update(float dt, const Paddle& paddle) { 
    if (!launched_ || stuck_) { attachTo(paddle); return; }

    circle_.move(vel_ * dt); 

    float x = circle_.getPosition().x;
    float y = circle_.getPosition().y;

    if (x - BALL_RADIUS < 0.f)             { circle_.setPosition(BALL_RADIUS, y);                   vel_.x =  std::abs(vel_.x); } 
    if (x + BALL_RADIUS > (float)WINDOW_W) { circle_.setPosition((float)WINDOW_W - BALL_RADIUS, y); vel_.x = -std::abs(vel_.x); } 
    if (y - BALL_RADIUS < 0.f)             { circle_.setPosition(x, BALL_RADIUS);                   vel_.y =  std::abs(vel_.y); } 
    if (y - BALL_RADIUS > (float)WINDOW_H)   alive_ = false; 
}

void Ball::draw(sf::RenderWindow& win) const { 
    win.draw(circle_);
}

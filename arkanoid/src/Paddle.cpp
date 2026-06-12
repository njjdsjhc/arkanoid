#include "Paddle.h"
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>

Paddle::Paddle() {
    shape_.setSize(sf::Vector2f(PADDLE_W, PADDLE_H));
    shape_.setFillColor(sf::Color(80, 200, 255));
    shape_.setPosition((WINDOW_W - PADDLE_W) * 0.5f, PADDLE_Y);
}

void Paddle::update(float dt) {
    float x = shape_.getPosition().x;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        x -= PADDLE_SPEED * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        x += PADDLE_SPEED * dt;

    float w = shape_.getSize().x;
    x = std::clamp(x, 0.f, (float)WINDOW_W - w);
    shape_.setPosition(x, PADDLE_Y);
}

void Paddle::draw(sf::RenderWindow& win) const {
    win.draw(shape_);
    if (floorActive_) {
        sf::RectangleShape fl(sf::Vector2f((float)WINDOW_W, 4.f));
        fl.setPosition(0.f, (float)WINDOW_H - 4.f);
        fl.setFillColor(sf::Color(255, 220, 50, 200));
        win.draw(fl);
    }
}

void Paddle::grow(float delta) {
    float w = std::clamp(shape_.getSize().x + delta, PADDLE_MIN_W, PADDLE_MAX_W);
    shape_.setSize(sf::Vector2f(w, PADDLE_H));
}

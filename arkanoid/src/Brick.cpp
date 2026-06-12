#include "Brick.h"
#include "Bonus.h"
#include <algorithm>

Brick::Brick(sf::Vector2f pos, sf::Color color) {
    shape_.setSize(sf::Vector2f(BRICK_W, BRICK_H));
    shape_.setPosition(pos);
    shape_.setFillColor(color);
    shape_.setOutlineColor(sf::Color(0, 0, 0, 100));
    shape_.setOutlineThickness(1.f);
}

void Brick::draw(sf::RenderWindow& win) const {
    win.draw(shape_);
}

IndestructibleBrick::IndestructibleBrick(sf::Vector2f pos)
    : Brick(pos, sf::Color(90, 90, 90)) {}

std::unique_ptr<Bonus> IndestructibleBrick::onHit(bool) {
    return nullptr;
}

NormalBrick::NormalBrick(sf::Vector2f pos, int hp, sf::Color color)
    : Brick(pos, color), hp_(hp), maxHp_(hp) {}

std::unique_ptr<Bonus> NormalBrick::onHit(bool) {
    if (--hp_ <= 0) kill();
    return nullptr;
}

void NormalBrick::draw(sf::RenderWindow& win) const {
    win.draw(shape_);
    if (maxHp_ > 1 && hp_ > 0) {
        sf::CircleShape dot(2.5f);
        dot.setFillColor(sf::Color(255, 255, 255, 200));
        float sx = shape_.getPosition().x + 4.f;
        float sy = shape_.getPosition().y + BRICK_H * 0.5f - 2.5f;
        for (int i = 0; i < hp_; ++i) {
            dot.setPosition(sx + i * 7.f, sy);
            win.draw(dot);
        }
    }
}

BonusBrick::BonusBrick(sf::Vector2f pos, int bonusType)
    : NormalBrick(pos, 1, sf::Color(180, 80, 220)), bonusType_(bonusType)
{
    shape_.setOutlineColor(sf::Color(255, 220, 50));
    shape_.setOutlineThickness(2.f);
}

std::unique_ptr<Bonus> BonusBrick::onHit(bool fromAbove) {
    NormalBrick::onHit();
    if (!fromAbove) return nullptr;
    sf::Vector2f center(shape_.getPosition().x + BRICK_W * 0.5f,
                        shape_.getPosition().y + BRICK_H);
    switch (bonusType_) {
        case 0:  return std::make_unique<BonusPaddleGrow>(center);
        case 1:  return std::make_unique<BonusPaddleShrink>(center);
        case 2:  return std::make_unique<BonusSpeedUp>(center);
        case 3:  return std::make_unique<BonusSpeedDown>(center);
        case 4:  return std::make_unique<BonusSticky>(center);
        case 5:  return std::make_unique<BonusFloor>(center);
        default: return std::make_unique<BonusMovingBrick>(center);
    }
}

SpeedBrick::SpeedBrick(sf::Vector2f pos)
    : NormalBrick(pos, 1, sf::Color(255, 140, 20)) {}

MovingBrick::MovingBrick(sf::Vector2f pos)
    : NormalBrick(pos, MOVING_BRICK_HP, sf::Color(50, 200, 100))
    , vx_(MOVING_BRICK_SPEED)
{
    shape_.setOutlineColor(sf::Color(200, 255, 200));
    shape_.setOutlineThickness(2.f);
}

void MovingBrick::update(float dt) {
    shape_.move(vx_ * dt, 0.f);
    float x = shape_.getPosition().x;
    if (x < 0.f) {
        shape_.setPosition(0.f, shape_.getPosition().y);
        vx_ = std::abs(vx_);
    }
    if (x + BRICK_W > (float)WINDOW_W) {
        shape_.setPosition((float)WINDOW_W - BRICK_W, shape_.getPosition().y);
        vx_ = -std::abs(vx_);
    }
}

void MovingBrick::resolveCollisions(const std::vector<std::unique_ptr<Brick>>& others) {
    for (const auto& other : others) {
        if (other.get() == this || !other->alive()) continue;
        if (!shape_.getGlobalBounds().intersects(other->bounds())) continue;
        vx_ = -vx_;
        shape_.move(-vx_ * 0.1f, 0.f);
        break;
    }
}

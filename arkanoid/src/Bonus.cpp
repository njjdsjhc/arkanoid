#include "Bonus.h"
#include "Paddle.h"
#include "Ball.h"
#include "GameField.h"

Bonus::Bonus(sf::Vector2f pos, sf::Color color) { 
    shape_.setSize(sf::Vector2f(BONUS_W, BONUS_H)); 
    shape_.setOrigin(BONUS_W * HALF, 0.f);
    shape_.setPosition(pos);
    shape_.setFillColor(color);
    shape_.setOutlineColor(sf::Color::White);
    shape_.setOutlineThickness(BONUS_OUTLINE);
}

void Bonus::update(float dt) {
    shape_.move(0.f, BONUS_FALL_SPEED * dt); 
    if (shape_.getPosition().y > (float)WINDOW_H) kill(); 
}

void Bonus::draw(sf::RenderWindow& win) const { 
    win.draw(shape_);
}

BonusPaddleGrow::BonusPaddleGrow(sf::Vector2f p)    : Bonus(p, sf::Color(50, 200, 50))   {} 
void BonusPaddleGrow::activate(Paddle& p, Ball&, GameField&)    { p.grow(+BONUS_PADDLE_GROW); }

BonusPaddleShrink::BonusPaddleShrink(sf::Vector2f p) : Bonus(p, sf::Color(200, 50, 50))  {} 
void BonusPaddleShrink::activate(Paddle& p, Ball&, GameField&)  { p.grow(-BONUS_PADDLE_GROW); }

BonusSpeedUp::BonusSpeedUp(sf::Vector2f p)          : Bonus(p, sf::Color(255, 100, 0))   {} 
void BonusSpeedUp::activate(Paddle&, Ball& b, GameField&)       { b.multiplySpeed(BONUS_SPEED_UP); }

BonusSpeedDown::BonusSpeedDown(sf::Vector2f p)      : Bonus(p, sf::Color(0, 180, 255))   {} 
void BonusSpeedDown::activate(Paddle&, Ball& b, GameField&)     { b.multiplySpeed(BONUS_SPEED_DOWN); }

BonusSticky::BonusSticky(sf::Vector2f p)            : Bonus(p, sf::Color(255, 230, 50))  {} 
void BonusSticky::activate(Paddle& p, Ball&, GameField&)        { p.setSticky(true); }

BonusFloor::BonusFloor(sf::Vector2f p)              : Bonus(p, sf::Color(220, 180, 255)) {} 
void BonusFloor::activate(Paddle& p, Ball&, GameField&)         { p.enableFloor(); }

BonusMovingBrick::BonusMovingBrick(sf::Vector2f p)  : Bonus(p, sf::Color(50, 230, 100))  {} 
void BonusMovingBrick::activate(Paddle&, Ball&, GameField& f)   { f.spawnMovingBrick(); }

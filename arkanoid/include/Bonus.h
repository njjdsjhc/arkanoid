#pragma once
#include "GameObject.h"
#include "Constants.h"

class Paddle;
class Ball;
class GameField;

class Bonus : public GameObject {
public:
    Bonus(sf::Vector2f pos, sf::Color color);
    void update(float dt) override;
    void draw(sf::RenderWindow& win) const override;
    virtual void activate(Paddle&, Ball&, GameField&) = 0;
};

class BonusPaddleGrow   : public Bonus { public: explicit BonusPaddleGrow(sf::Vector2f p);   void activate(Paddle&,Ball&,GameField&) override; };
class BonusPaddleShrink : public Bonus { public: explicit BonusPaddleShrink(sf::Vector2f p); void activate(Paddle&,Ball&,GameField&) override; };
class BonusSpeedUp      : public Bonus { public: explicit BonusSpeedUp(sf::Vector2f p);      void activate(Paddle&,Ball&,GameField&) override; };
class BonusSpeedDown    : public Bonus { public: explicit BonusSpeedDown(sf::Vector2f p);    void activate(Paddle&,Ball&,GameField&) override; };
class BonusSticky       : public Bonus { public: explicit BonusSticky(sf::Vector2f p);       void activate(Paddle&,Ball&,GameField&) override; };
class BonusFloor        : public Bonus { public: explicit BonusFloor(sf::Vector2f p);        void activate(Paddle&,Ball&,GameField&) override; };
class BonusMovingBrick  : public Bonus { public: explicit BonusMovingBrick(sf::Vector2f p);  void activate(Paddle&,Ball&,GameField&) override; };

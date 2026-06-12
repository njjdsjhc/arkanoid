#pragma once
#include "GameObject.h"
#include "Constants.h"
#include <memory>
#include <vector>

class Bonus;

class Brick : public GameObject {
public:
    Brick(sf::Vector2f pos, sf::Color color);
    void draw(sf::RenderWindow& win) const override;

    virtual std::unique_ptr<Bonus> onHit(bool hitFromAbove = false) = 0;
    virtual float speedMult() const { return 1.f; }
};

class IndestructibleBrick : public Brick {
public:
    explicit IndestructibleBrick(sf::Vector2f pos);
    std::unique_ptr<Bonus> onHit(bool hitFromAbove = false) override;
};

class NormalBrick : public Brick {
public:
    NormalBrick(sf::Vector2f pos, int hp, sf::Color color);
    std::unique_ptr<Bonus> onHit(bool hitFromAbove = false) override;
    void draw(sf::RenderWindow& win) const override;

protected:
    int hp_;
    int maxHp_;
};

class BonusBrick : public NormalBrick {
public:
    BonusBrick(sf::Vector2f pos, int bonusType);
    std::unique_ptr<Bonus> onHit(bool hitFromAbove = false) override;
private:
    int bonusType_;
};

class SpeedBrick : public NormalBrick {
public:
    explicit SpeedBrick(sf::Vector2f pos);
    float speedMult() const override { return 1.12f; }
};

class MovingBrick : public NormalBrick {
public:
    explicit MovingBrick(sf::Vector2f pos);
    void update(float dt) override;
    void resolveCollisions(const std::vector<std::unique_ptr<Brick>>& others);
private:
    float vx_;
};

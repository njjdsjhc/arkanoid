#pragma once
#include "GameObject.h"
#include "Constants.h"
#include <memory>
#include <vector>
#include <functional>

class Bonus;

using BonusFactory = std::function<std::unique_ptr<Bonus>(sf::Vector2f)>; 
class Brick : public GameObject { 
public:
    Brick(sf::Vector2f pos, sf::Color color);
    void draw(sf::RenderWindow& win) const override; 

    virtual std::unique_ptr<Bonus> onHit(bool fromAbove = false) = 0; 
    virtual float speedMult()    const { return 1.f; } 
    virtual bool  isDestructible() const { return true; }  
    virtual void  resolveMovement(const std::vector<std::unique_ptr<Brick>>&) {} 
};

class IndestructibleBrick : public Brick { 
public:
    explicit IndestructibleBrick(sf::Vector2f pos);
    std::unique_ptr<Bonus> onHit(bool fromAbove = false) override; 
    bool isDestructible() const override { return false; } 
};

class NormalBrick : public Brick {
public:
    NormalBrick(sf::Vector2f pos, int hp, sf::Color color); 
    std::unique_ptr<Bonus> onHit(bool fromAbove = false) override; 
    void draw(sf::RenderWindow& win) const override; 
protected:
    int hp_;
    int maxHp_;
};

class BonusBrick : public NormalBrick {
public:
    BonusBrick(sf::Vector2f pos, BonusFactory factory); 
    std::unique_ptr<Bonus> onHit(bool fromAbove = false) override; 
private:
    BonusFactory factory_; 
};

class SpeedBrick : public NormalBrick { 
public:
    explicit SpeedBrick(sf::Vector2f pos);
    float speedMult() const override { return SPEED_BRICK_MULT; } 
};

class MovingBrick : public NormalBrick { 
public:
    explicit MovingBrick(sf::Vector2f pos);
    void update(float dt) override; 
    void resolveMovement(const std::vector<std::unique_ptr<Brick>>& others) override; 
private:
    float vx_; 
};

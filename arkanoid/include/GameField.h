#pragma once
#include <vector>
#include <memory>
#include "Brick.h"
#include "Bonus.h"

class GameField {
public:
    GameField(); 

    void update(float dt); 
    void draw(sf::RenderWindow& win) const; 
    void spawnMovingBrick(); 
    bool allDestructibleGone() const; 

    void addBonus(std::unique_ptr<Bonus> b) { bonuses_.push_back(std::move(b)); } 

    std::vector<std::unique_ptr<Brick>>& bricks() { return bricks_; } 
    std::vector<std::unique_ptr<Bonus>>& bonuses() { return bonuses_; } 

private:
    void resolveMovingBrickCollisions(); 
    void removeDeadObjects(); 

    std::vector<std::unique_ptr<Brick>> bricks_; 
    std::vector<std::unique_ptr<Bonus>> bonuses_; 
};

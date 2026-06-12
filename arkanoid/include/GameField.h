#pragma once
#include <vector>
#include <memory>
#include "Brick.h"
#include "Bonus.h"
#include "Ball.h"
#include "Paddle.h"

class GameField {
public:
    GameField();
    void update(float dt, Ball& ball, Paddle& paddle, int& score);
    void draw(sf::RenderWindow& win) const;
    void spawnMovingBrick();
    bool allDestructibleGone() const;
    void addBonus(std::unique_ptr<Bonus> b) { bonuses_.push_back(std::move(b)); }

private:
    void collideBallBricks(Ball& ball, int& score);
    void collideBallPaddle(Ball& ball, Paddle& paddle);
    void collideBallFloor(Ball& ball, Paddle& paddle);
    void processBonuses(float dt, Paddle& paddle, Ball& ball);

    std::vector<std::unique_ptr<Brick>> bricks_;
    std::vector<std::unique_ptr<Bonus>> bonuses_;
};

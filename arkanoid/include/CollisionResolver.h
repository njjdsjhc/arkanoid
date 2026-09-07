#pragma once
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include "Bonus.h"
#include <vector>
#include <memory>

class CollisionResolver {
public:
    std::unique_ptr<Bonus> ballVsBricks(
        Ball& ball,
        std::vector<std::unique_ptr<Brick>>& bricks,
        int& score); 

    void ballVsPaddle(Ball& ball, Paddle& paddle); 
    void ballVsFloor(Ball& ball, Paddle& paddle); 

private:
    static std::pair<bool,bool> reflectAxes(sf::Vector2f pos, float r, sf::FloatRect rect); 
    static bool                 hitFromAbove(sf::Vector2f vel, sf::Vector2f pos, sf::FloatRect rect); 
};

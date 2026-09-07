#include "CollisionResolver.h"
#include "Constants.h"
#include <algorithm>
#include <cmath>

std::pair<bool,bool> CollisionResolver::reflectAxes(sf::Vector2f pos, float r, sf::FloatRect rect) { 
    float cx = pos.x, cy = pos.y;
    float nx = std::clamp(cx, rect.left, rect.left + rect.width);
    float ny = std::clamp(cy, rect.top,  rect.top  + rect.height);
    float overlapX = (cx >= nx) ? (cx + r - rect.left) : (rect.left + rect.width  - (cx - r));
    float overlapY = (cy >= ny) ? (cy + r - rect.top)  : (rect.top  + rect.height - (cy - r));
    return {overlapX <= overlapY, overlapX > overlapY};
}

bool CollisionResolver::hitFromAbove(sf::Vector2f vel, sf::Vector2f pos, sf::FloatRect rect) {
    return vel.y > 0.f && pos.y < rect.top + rect.height * HALF;
}

std::unique_ptr<Bonus> CollisionResolver::ballVsBricks( 
    Ball& ball,
    std::vector<std::unique_ptr<Brick>>& bricks,
    int& score)
{
    for (auto& brick : bricks) { 
        if (!brick->alive()) continue; 
        if (!ball.bounds().intersects(brick->bounds())) continue; 

        auto [rx, ry] = reflectAxes(ball.pos(), BALL_RADIUS, brick->bounds());
        if (rx) ball.bounceX(); else ball.bounceY(); 

        ball.multiplySpeed(brick->speedMult()); 
        score += HIT_REWARD; 

        bool fromAbove = hitFromAbove(ball.vel(), ball.pos(), brick->bounds()); 
        return brick->onHit(fromAbove); 
    }
    return nullptr;
}

void CollisionResolver::ballVsPaddle(Ball& ball, Paddle& paddle) { 
    if (!ball.bounds().intersects(paddle.bounds())) return; 
    if (ball.vel().y <= 0.f) return; 
    if (ball.pos().y > paddle.top() + PADDLE_H) return;

    float rel   = std::clamp((ball.pos().x - paddle.left()) / paddle.bounds().width, 0.f, 1.f); 
    float angle = (PADDLE_ANGLE_MIN + rel * PADDLE_ANGLE_RANGE) * DEG_TO_RAD; 
    float spd   = ball.speed();
    ball.setVel({std::cos(angle) * spd, std::sin(angle) * spd}); 
    ball.setPos({ball.pos().x, paddle.top() - BALL_RADIUS - PADDLE_BOUNCE_OFFSET}); 

    if (paddle.isSticky()) {
        ball.stick();
        paddle.setSticky(false);
    }
}

void CollisionResolver::ballVsFloor(Ball& ball, Paddle& paddle) { 
    if (!paddle.hasFloor()) return; 
    if (ball.pos().y + BALL_RADIUS < (float)WINDOW_H - FLOOR_THICKNESS) return; 
    
    paddle.consumeFloor();
    ball.bounceY();
    ball.setPos({ball.pos().x, (float)WINDOW_H - FLOOR_THICKNESS - BALL_RADIUS - FLOOR_BOUNCE_OFFSET});
}

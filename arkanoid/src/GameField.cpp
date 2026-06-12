#include "GameField.h"
#include <random>
#include <algorithm>
#include <cmath>

namespace {
    std::mt19937& rng() { static std::mt19937 g(std::random_device{}()); return g; }

    int randInt(int lo, int hi) {
        return std::uniform_int_distribution<int>(lo, hi)(rng());
    }

    std::pair<bool,bool> reflectAxes(sf::Vector2f pos, float r, sf::FloatRect rect) {
        float cx = pos.x, cy = pos.y;
        float nx = std::clamp(cx, rect.left, rect.left + rect.width);
        float ny = std::clamp(cy, rect.top,  rect.top  + rect.height);

        float overlapX = (cx >= nx) ? (cx + r - rect.left) : (rect.left + rect.width  - (cx - r));
        float overlapY = (cy >= ny) ? (cy + r - rect.top)  : (rect.top  + rect.height - (cy - r));

        bool reflX = (overlapX <= overlapY);
        return {reflX, !reflX};
    }

    bool hitFromAbove(sf::Vector2f vel, sf::Vector2f pos, sf::FloatRect rect) {
        return vel.y > 0.f && pos.y < rect.top + rect.height * 0.5f;
    }
}

GameField::GameField() {
    for (int row = 0; row < BRICK_ROWS; ++row) {
        for (int col = 0; col < BRICK_COLS; ++col) {
            float x = BRICK_OFFSET_X + col * (BRICK_W + BRICK_GAP);
            float y = BRICK_OFFSET_Y + row * (BRICK_H + BRICK_GAP);
            sf::Vector2f pos(x, y);

            int r = randInt(0, 9);
            if (r == 0) {
                bricks_.push_back(std::make_unique<IndestructibleBrick>(pos));
            } else if (r <= 2) {
                bricks_.push_back(std::make_unique<BonusBrick>(pos, randInt(0, 6)));
            } else if (r == 3) {
                bricks_.push_back(std::make_unique<SpeedBrick>(pos));
            } else {
                int hp = randInt(1, 3);
                sf::Color cols[3] = {
                    sf::Color(200, 80,  80),
                    sf::Color(80,  130, 220),
                    sf::Color(220, 200, 60)
                };
                bricks_.push_back(std::make_unique<NormalBrick>(pos, hp, cols[hp-1]));
            }
        }
    }
}

void GameField::update(float dt, Ball& ball, Paddle& paddle, int& score) {
    for (auto& b : bricks_) b->update(dt);

    for (auto& b : bricks_) {
        if (!b->alive()) continue;
        if (auto* mb = dynamic_cast<MovingBrick*>(b.get()))
            mb->resolveCollisions(bricks_);
    }

    if (ball.isLaunched() && ball.alive() && !ball.isStuck()) {
        collideBallBricks(ball, score);
        collideBallPaddle(ball, paddle);
        collideBallFloor(ball, paddle);
    }

    processBonuses(dt, paddle, ball);

    bricks_.erase(
        std::remove_if(bricks_.begin(), bricks_.end(), [](const auto& b){ return !b->alive(); }),
        bricks_.end());
}

void GameField::collideBallBricks(Ball& ball, int& score) {
    for (auto& brick : bricks_) {
        if (!brick->alive()) continue;
        if (!ball.bounds().intersects(brick->bounds())) continue;

        auto [rx, ry] = reflectAxes(ball.pos(), BALL_RADIUS, brick->bounds());
        if (rx) ball.bounceX(); else ball.bounceY();

        ball.multiplySpeed(brick->speedMult());

        score += HIT_REWARD;

        bool fromAbove = hitFromAbove(ball.vel(), ball.pos(), brick->bounds());
        auto bonus = brick->onHit(fromAbove);
        if (bonus) bonuses_.push_back(std::move(bonus));

        break;
    }
}

void GameField::collideBallPaddle(Ball& ball, Paddle& paddle) {
    if (!ball.bounds().intersects(paddle.bounds())) return;
    if (ball.vel().y <= 0.f) return;                        
    if (ball.pos().y > paddle.top() + PADDLE_H) return;   

    float rel   = std::clamp((ball.pos().x - paddle.left()) / paddle.bounds().width, 0.f, 1.f);
    float angle = (-150.f + rel * 60.f) * 3.14159265f / 180.f;
    float spd   = ball.speed();
    ball.setVel({std::cos(angle) * spd, std::sin(angle) * spd});
    ball.setPos({ball.pos().x, paddle.top() - BALL_RADIUS - 1.f});

    if (paddle.isSticky()) {
        ball.stick();
        paddle.setSticky(false);
    }
}

void GameField::collideBallFloor(Ball& ball, Paddle& paddle) {
    if (!paddle.hasFloor()) return;
    if (ball.pos().y + BALL_RADIUS < (float)WINDOW_H - 4.f) return;
    paddle.consumeFloor();
    ball.bounceY();
    ball.setPos({ball.pos().x, (float)WINDOW_H - 4.f - BALL_RADIUS - 1.f});
}

void GameField::processBonuses(float dt, Paddle& paddle, Ball& ball) {
    for (auto& b : bonuses_) {
        if (!b->alive()) continue;
        b->update(dt);
        if (b->bounds().intersects(paddle.bounds())) {
            b->activate(paddle, ball, *this);
            b->kill();
        }
    }
    bonuses_.erase(
        std::remove_if(bonuses_.begin(), bonuses_.end(), [](const auto& b){ return !b->alive(); }),
        bonuses_.end());
}

void GameField::draw(sf::RenderWindow& win) const {
    for (auto& b : bricks_)  b->draw(win);
    for (auto& b : bonuses_) b->draw(win);
}

void GameField::spawnMovingBrick() {
    float x = (float)std::uniform_int_distribution<int>(0, WINDOW_W - (int)BRICK_W)(rng());
    float y  = BRICK_OFFSET_Y + BRICK_ROWS * (BRICK_H + BRICK_GAP) + 30.f;
    bricks_.push_back(std::make_unique<MovingBrick>(sf::Vector2f(x, y)));
}

bool GameField::allDestructibleGone() const {
    for (auto& b : bricks_)
        if (b->alive() && dynamic_cast<const IndestructibleBrick*>(b.get()) == nullptr)
            return false;
    return true;
}

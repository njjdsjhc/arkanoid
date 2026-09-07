#include "GameField.h"
#include "Constants.h"
#include <random>
#include <algorithm>

namespace {
    std::mt19937& rng() { static std::mt19937 g(std::random_device{}()); return g; }

    int randInt(int lo, int hi) {
        return std::uniform_int_distribution<int>(lo, hi)(rng());
    }

    BonusFactory randomBonusFactory() {
        static const std::vector<BonusFactory> factories = {
            [](sf::Vector2f p){ return std::make_unique<BonusPaddleGrow>(p); },
            [](sf::Vector2f p){ return std::make_unique<BonusPaddleShrink>(p); },
            [](sf::Vector2f p){ return std::make_unique<BonusSpeedUp>(p); },
            [](sf::Vector2f p){ return std::make_unique<BonusSpeedDown>(p); },
            [](sf::Vector2f p){ return std::make_unique<BonusSticky>(p); },
            [](sf::Vector2f p){ return std::make_unique<BonusFloor>(p); },
            [](sf::Vector2f p){ return std::make_unique<BonusMovingBrick>(p); },
        };
        return factories[randInt(0, (int)factories.size() - 1)];
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
                bricks_.push_back(std::make_unique<BonusBrick>(pos, randomBonusFactory()));
            } else if (r == 3) { 
                bricks_.push_back(std::make_unique<SpeedBrick>(pos));
            } else {
                int hp = randInt(1, 3);
                sf::Color cols[3] = {
                    sf::Color(200, 80,  80),
                    sf::Color(80,  130, 220),
                    sf::Color(220, 200, 60)
                };
                bricks_.push_back(std::make_unique<NormalBrick>(pos, hp, cols[hp - 1])); // нормис
            }
        }
    }
}

void GameField::update(float dt) { 
    for (auto& b : bricks_) b->update(dt); 

    for (auto& b : bricks_)
        if (b->alive()) b->resolveMovement(bricks_);

    for (auto& b : bonuses_)
        if (b->alive()) b->update(dt);

    removeDeadObjects(); 
}

void GameField::removeDeadObjects() { 
    auto dead = [](const auto& b){ return !b->alive(); };
    bricks_.erase(std::remove_if(bricks_.begin(), bricks_.end(), dead), bricks_.end());
    bonuses_.erase(std::remove_if(bonuses_.begin(), bonuses_.end(), dead), bonuses_.end());
}

void GameField::draw(sf::RenderWindow& win) const { 
    for (auto& b : bricks_)  b->draw(win);
    for (auto& b : bonuses_) b->draw(win);
}

void GameField::spawnMovingBrick() { 
    float x = (float)std::uniform_int_distribution<int>(0, WINDOW_W - (int)BRICK_W)(rng());
    float y  = BRICK_OFFSET_Y + BRICK_ROWS * (BRICK_H + BRICK_GAP) + HINT_Y_OFFSET;
    bricks_.push_back(std::make_unique<MovingBrick>(sf::Vector2f(x, y)));
}

bool GameField::allDestructibleGone() const {
    for (auto& b : bricks_)
        if (b->alive() && b->isDestructible())  
            return false;
    return true;
}

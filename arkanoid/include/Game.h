#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"
#include "GameField.h"
#include "CollisionResolver.h"
#include "HUD.h"

class Game {
public:
    Game(); 
    void run(); 

private:
    void handleEvents(); 
    void update(float dt); 
    void render(); 
    void drawHint(); 
    void drawGameOver(); 
    void reset(); 
    void checkEndCondition(); 
    void processBonuses(); 

    sf::RenderWindow   window_;
    sf::Font           font_;
    Paddle             paddle_;
    Ball               ball_;
    GameField          field_;
    CollisionResolver  collisions_;
    HUD                hud_;

    int  score_    = 0; 
    int  misses_   = 0; 
    bool gameOver_ = false; 
    bool won_      = false; 
};

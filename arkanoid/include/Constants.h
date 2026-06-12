#pragma once

constexpr int   WINDOW_W           = 800;
constexpr int   WINDOW_H           = 600;
constexpr int   FPS                = 60;

constexpr float PADDLE_W           = 100.f;
constexpr float PADDLE_H           = 14.f;
constexpr float PADDLE_Y           = 560.f;
constexpr float PADDLE_SPEED       = 420.f;
constexpr float PADDLE_MIN_W       = 40.f;
constexpr float PADDLE_MAX_W       = 200.f;

constexpr float BALL_RADIUS        = 8.f;
constexpr float BALL_SPEED         = 320.f;
constexpr float BALL_MAX_SPEED     = 700.f;

constexpr int   BRICK_COLS         = 12;
constexpr int   BRICK_ROWS         = 6;
constexpr float BRICK_W            = 58.f;
constexpr float BRICK_H            = 22.f;
constexpr float BRICK_GAP          = 4.f;
constexpr float BRICK_OFFSET_X     = 20.f;
constexpr float BRICK_OFFSET_Y     = 50.f;

constexpr float BONUS_FALL_SPEED   = 130.f;
constexpr float BONUS_W            = 26.f;
constexpr float BONUS_H            = 14.f;

constexpr float MOVING_BRICK_SPEED = 90.f;
constexpr int   MOVING_BRICK_HP    = 3;

constexpr int   MISS_PENALTY       = -3;    
constexpr float MISS_PADDLE_SHRINK = -20.f; 
constexpr int   HIT_REWARD         = 1;     
constexpr int   MAX_MISSES         = 5;

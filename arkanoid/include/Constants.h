#pragma once

constexpr int   WINDOW_W               = 800;
constexpr int   WINDOW_H               = 600;
constexpr int   FPS                    = 60;

constexpr float PADDLE_W               = 100.f;
constexpr float PADDLE_H               = 14.f;
constexpr float PADDLE_Y               = 560.f;
constexpr float PADDLE_SPEED           = 420.f;
constexpr float PADDLE_MIN_W           = 40.f;
constexpr float PADDLE_MAX_W           = 200.f;
constexpr float PADDLE_ANGLE_MIN       = -150.f;
constexpr float PADDLE_ANGLE_RANGE     = 60.f;

constexpr float BALL_RADIUS            = 8.f;
constexpr float BALL_SPEED             = 320.f;
constexpr float BALL_MAX_SPEED         = 700.f;
constexpr float BALL_LAUNCH_VX         = 0.55f;
constexpr float BALL_MIN_SPEED_MUL     = 0.4f;
constexpr float BALL_SPEED_EPS         = 0.001f;  
constexpr float BALL_OFFSET_Y          = 2.f;     

constexpr int   BRICK_COLS             = 12;
constexpr int   BRICK_ROWS             = 6;
constexpr float BRICK_W                = 58.f;
constexpr float BRICK_H                = 22.f;
constexpr float BRICK_GAP              = 4.f;
constexpr float BRICK_OFFSET_X         = 20.f;
constexpr float BRICK_OFFSET_Y         = 50.f;
constexpr float BRICK_OUTLINE_NORMAL   = 1.f;
constexpr float BRICK_OUTLINE_SPECIAL  = 2.f;
constexpr float BRICK_HP_DOT_R         = 2.5f;
constexpr float BRICK_HP_DOT_STEP      = 7.f;
constexpr float BRICK_HP_DOT_OFFSET_X  = 4.f;

constexpr float BONUS_FALL_SPEED       = 130.f;
constexpr float BONUS_W                = 26.f;
constexpr float BONUS_H                = 14.f;
constexpr float BONUS_OUTLINE          = 1.f;
constexpr float BONUS_PADDLE_GROW      = 30.f;
constexpr float BONUS_SPEED_UP         = 1.25f;
constexpr float BONUS_SPEED_DOWN       = 0.75f;

constexpr float MOVING_BRICK_SPEED     = 90.f;
constexpr int   MOVING_BRICK_HP        = 3;
constexpr float MOVING_BRICK_PUSH_BACK = 0.1f;

constexpr float SPEED_BRICK_MULT       = 1.12f;

constexpr float FLOOR_THICKNESS        = 4.f;     
constexpr float FLOOR_BOUNCE_OFFSET    = 1.f;     
constexpr float PADDLE_BOUNCE_OFFSET   = 1.f;     

constexpr int   MISS_PENALTY           = -3;
constexpr float MISS_PADDLE_SHRINK     = -20.f;
constexpr int   HIT_REWARD             = 1;
constexpr int   MAX_MISSES             = 5;

constexpr float PI                     = 3.14159265f;
constexpr float DEG_TO_RAD             = PI / 180.f;
constexpr float HALF                   = 0.5f;

constexpr float DT_MAX                 = 0.05f;

constexpr float HUD_SCORE_X            = 8.f;
constexpr float HUD_Y                  = 8.f;
constexpr float HUD_MISSES_X           = 160.f;
constexpr int   HUD_FONT_SIZE          = 18;

constexpr float HINT_Y_OFFSET          = 30.f;
constexpr float GAMEOVER_Y_OFFSET      = 40.f;
constexpr float GAMEOVER_SUB_Y         = 12.f;
constexpr int   HINT_FONT_SIZE         = 16;
constexpr int   GAMEOVER_FONT_SIZE     = 40;
constexpr int   GAMEOVER_SUB_FONT_SIZE = 20;

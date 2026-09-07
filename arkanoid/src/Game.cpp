#include "Game.h"
#include "Constants.h"
#include <string>
#include <vector>

Game::Game() 
    : window_(sf::VideoMode(WINDOW_W, WINDOW_H), "Arkanoid",
              sf::Style::Titlebar | sf::Style::Close)
    , hud_(font_)
{
    window_.setFramerateLimit(FPS);
    const std::vector<std::string> fontPaths = {
        "C:/Windows/Fonts/arial.ttf",
        "C:/Windows/Fonts/calibri.ttf",
        "C:/Windows/Fonts/tahoma.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf"
    };
    for (const auto& path : fontPaths)
        if (font_.loadFromFile(path)) break;
}

void Game::run() { 
    sf::Clock clock;
    while (window_.isOpen()) {
        float dt = clock.restart().asSeconds(); 
        if (dt > DT_MAX) dt = DT_MAX; 
        handleEvents();
        if (!gameOver_) update(dt);
        render();
    }
}

void Game::handleEvents() { 
    sf::Event ev;
    while (window_.pollEvent(ev)) {
        if (ev.type == sf::Event::Closed) window_.close(); 
        if (ev.type == sf::Event::KeyPressed) {
            if (ev.key.code == sf::Keyboard::Escape) window_.close();
            if (ev.key.code == sf::Keyboard::Space) {
                if (gameOver_) reset();
                else           ball_.launch();
            }
        }
    }
}

void Game::update(float dt) { 
    paddle_.update(dt);
    ball_.update(dt, paddle_);
    field_.update(dt);

    if (ball_.isLaunched() && ball_.alive() && !ball_.isStuck()) {
        auto bonus = collisions_.ballVsBricks(ball_, field_.bricks(), score_); 
        if (bonus) field_.addBonus(std::move(bonus));
        
        collisions_.ballVsPaddle(ball_, paddle_);
        collisions_.ballVsFloor(ball_, paddle_);
    }

    processBonuses(); 

    if (!ball_.alive()) {
        misses_ += 1;
        score_  += MISS_PENALTY;
        paddle_.grow(MISS_PADDLE_SHRINK);
        ball_ = Ball();
        paddle_.setSticky(false);
    }
    checkEndCondition();
}

void Game::processBonuses() {
    for (auto& b : field_.bonuses()) {
        if (!b->alive()) continue;
        if (b->bounds().intersects(paddle_.bounds())) { 
            b->activate(paddle_, ball_, field_); 
            b->kill();
        }
    }
}

void Game::checkEndCondition() { 
    if (field_.allDestructibleGone()) { gameOver_ = true; won_ = true; }
    if (misses_ >= MAX_MISSES)        { gameOver_ = true; won_ = false; }
}

void Game::reset() { 
    score_ = misses_ = 0;
    gameOver_ = won_ = false;
    paddle_ = Paddle();
    ball_   = Ball();
    field_  = GameField();
}

void Game::render() { 
    window_.clear(sf::Color(20, 20, 35));
    field_.draw(window_);
    paddle_.draw(window_);
    if (ball_.alive()) ball_.draw(window_);
    hud_.draw(window_, score_, misses_);
    if (!gameOver_) drawHint();
    if (gameOver_)  drawGameOver();
    window_.display();
}

void Game::drawHint() { 
    sf::Text hint;
    hint.setFont(font_);
    hint.setCharacterSize(HINT_FONT_SIZE);
    if (ball_.isStuck()) {
        hint.setFillColor(sf::Color(255, 230, 50));
        hint.setString("SPACE - release ball");
    } else if (!ball_.isLaunched()) {
        hint.setFillColor(sf::Color(160, 160, 200));
        hint.setString("SPACE - launch ball");
    } else {
        return;
    }
    sf::FloatRect r = hint.getLocalBounds();
    hint.setPosition(((float)WINDOW_W - r.width) * HALF, PADDLE_Y - HINT_Y_OFFSET);
    window_.draw(hint);
}

void Game::drawGameOver() { 
    sf::Text msg;
    msg.setFont(font_);
    msg.setCharacterSize(GAMEOVER_FONT_SIZE);
    msg.setFillColor(won_ ? sf::Color(80, 255, 80) : sf::Color(255, 80, 80));
    msg.setString(won_ ? "YOU WIN!" : "GAME OVER");
    sf::FloatRect r = msg.getLocalBounds();
    msg.setPosition(((float)WINDOW_W - r.width) * HALF, (float)WINDOW_H * HALF - GAMEOVER_Y_OFFSET);
    window_.draw(msg);

    sf::Text sub;
    sub.setFont(font_);
    sub.setCharacterSize(GAMEOVER_SUB_FONT_SIZE);
    sub.setFillColor(sf::Color(200, 200, 200));
    sub.setString("SPACE - restart");
    sf::FloatRect rs = sub.getLocalBounds();
    sub.setPosition(((float)WINDOW_W - rs.width) * HALF, (float)WINDOW_H * HALF + GAMEOVER_SUB_Y);
    window_.draw(sub);
}

#include "HUD.h"
#include "Constants.h"
#include <string>

HUD::HUD(const sf::Font& font) : font_(font) {}

void HUD::draw(sf::RenderWindow& win, int score, int misses) const {
    auto make = [&](const std::string& s, float x, sf::Color c) { 
        sf::Text t;
        t.setFont(font_);
        t.setCharacterSize(HUD_FONT_SIZE);
        t.setFillColor(c);
        t.setString(s);
        t.setPosition(x, HUD_Y);
        win.draw(t);
    };
    make("Score: " + std::to_string(score), HUD_SCORE_X, sf::Color::White);
    make("Misses: " + std::to_string(misses) + "/" + std::to_string(MAX_MISSES),
         (float)WINDOW_W - HUD_MISSES_X, sf::Color(255, 100, 100));
}

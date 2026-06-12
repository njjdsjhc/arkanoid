#include "HUD.h"
#include "Constants.h"
#include <string>

HUD::HUD(const sf::Font& font) : font_(font) {}

void HUD::draw(sf::RenderWindow& win, int score, int misses) const {
    auto make = [&](const std::string& s, float x, float y, sf::Color c) {
        sf::Text t;
        t.setFont(font_);
        t.setCharacterSize(18);
        t.setFillColor(c);
        t.setString(s);
        t.setPosition(x, y);
        win.draw(t);
    };
    make("Score: " + std::to_string(score),   8.f,              8.f, sf::Color::White);
    make("Misses: " + std::to_string(misses)  + "/" + std::to_string(MAX_MISSES),
         (float)WINDOW_W - 160.f, 8.f, sf::Color(255, 100, 100));
}

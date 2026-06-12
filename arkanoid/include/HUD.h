#pragma once
#include <SFML/Graphics.hpp>

class HUD {
public:
    explicit HUD(const sf::Font& font);
    void draw(sf::RenderWindow& win, int score, int misses) const;
private:
    const sf::Font& font_;
};

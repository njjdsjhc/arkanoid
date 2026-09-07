#pragma once
#include <SFML/Graphics.hpp>

class GameObject {
public:
    virtual ~GameObject() = default; 
    virtual void update(float dt) {} 
    virtual void draw(sf::RenderWindow& win) const = 0; 

    sf::FloatRect bounds() const { return shape_.getGlobalBounds(); } 
    bool          alive()  const { return alive_; }
    void          kill()         { alive_ = false; }

protected:
    sf::RectangleShape shape_;
    bool               alive_ = true;
};

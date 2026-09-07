#pragma once
#include "GameObject.h"
#include "Constants.h"

class Paddle : public GameObject {
public:
    Paddle();
    void  update(float dt) override; 
    void  draw(sf::RenderWindow& win) const override; 

    void  grow(float delta);

    void  setSticky(bool s) { sticky_ = s; }
    bool  isSticky()  const { return sticky_; }

    float left()    const { return shape_.getPosition().x; }
    float right()   const { return shape_.getPosition().x + shape_.getSize().x; }
    float top()     const { return shape_.getPosition().y; }

    float centerX() const { return shape_.getPosition().x + shape_.getSize().x * 0.5f; } 

    bool  hasFloor()    const { return floorActive_; } 
    void  enableFloor()       { floorActive_ = true; } 
    void  consumeFloor()      { floorActive_ = false; } 

private:
    bool sticky_      = false; 
    bool floorActive_ = false;
};

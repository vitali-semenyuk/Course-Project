#pragma once
#include "Global.h"

class Player {
public:
    double dx, dy;
    sf::FloatRect rect;
    bool onSurface;
    sf::Sprite sprite;
    double currentFrame;

    Player(sf::Texture &image);

    void update(double time);
    void collision(Direction dir);

};
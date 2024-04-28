#ifndef PACMAN_H
#define PACMAN_H

#include "GameEntity.h"

class Pacman : public GameEntity {
public:
    Pacman(float x, float y, float r, float g, float b) : GameEntity(x, y, r, g, b) {
    }

    void draw() override {
        GameEntity::draw();  
    }

    void move() override {
        GameEntity::move();  
    }

    void changeDirection() override {
        GameEntity::changeDirection();  
    }
};

#endif
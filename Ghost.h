#ifndef GHOST_H
#define GHOST_H

#include "GameEntity.h"

class Ghost : public GameEntity {
public:
    Ghost(float x, float y, float r, float g, float b) : GameEntity(x, y, r, g, b) {
        
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
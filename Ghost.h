#ifndef GHOST_H
#define GHOST_H
#include "Pacman.h"
#include <utility> 

enum Direction { UP, DOWN, LEFT, RIGHT };

class Ghost {
public:
    Direction direction;
    float x;
    float y;
    float angle;
    float color[3]; 

    Ghost(float r, float g, float b) : x(0.0), y(0.0), angle(0.0) {
        color[0] = r;
        color[1] = g;
        color[2] = b;
    }

    void draw();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    void move();
    void changeDirection();

    float getX();
    float getY();

};

#endif
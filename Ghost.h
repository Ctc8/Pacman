#ifndef GHOST_H
#define GHOST_H
#include "Pacman.h"

enum Direction { UP, DOWN, LEFT, RIGHT };

class Ghost {
public:
    Direction direction;
    float x;
    float y;
    float angle;

    Ghost() : x(0.0), y(0.0), angle(0.0) {}

    void draw();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    void move();
    void changeDirection();

};

#endif
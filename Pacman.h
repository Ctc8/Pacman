#ifndef PACMAN_H
#define PACMAN_H

#define PI 3.1415926535897932384626433832795
#include <math.h>

class Pacman {
public:
    float x;
    float y;
    float angle;

    Pacman() : x(0.0), y(0.0), angle(0.0) {}

    void draw();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
};

#endif 
#ifndef GHOST_H
#define GHOST_H

class Ghost {
public:
    float x;
    float y;
    float angle;

    Ghost() : x(0.0), y(0.0), angle(0.0) {}

    void draw();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
};

#endif
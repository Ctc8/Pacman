#ifndef PACMAN_H
#define PACMAN_H

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#define PI 3.1415926535897932384626433832795
#include <math.h>

class Pacman {
public:
    float x;
    float y;
    float angle;
    float radius;
    int** maze;

    Pacman(int** maze) : maze(maze) {}

    Pacman() : x(0.0), y(0.5), angle(0.0) {}

    void draw();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    float getX();
    float getY();
};

#endif 
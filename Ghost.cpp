#define GL_SILENCE_DEPRECATION
#include "Ghost.h"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <math.h>
#include <stdlib.h> 

#define PI 3.1415926535897932384626433832795

void Ghost::draw() {
    float size = 0.04; 
    glColor3f(color[0], color[1], color[2]);

    glBegin(GL_QUADS);
    glVertex2f(x - size, y - size);
    glVertex2f(x + size, y - size);
    glVertex2f(x + size, y + size); 
    glVertex2f(x - size, y + size); 
    glEnd();
}

void Ghost::move() {
    float speed = 0.01; 
    float size = 0.03; 

    switch (direction) {
        case UP:
            if (y + size + speed <= 1) 
                y += speed;
            break;
        case DOWN:
            if (y - size - speed >= -1)  
                y -= speed;
            break;
        case LEFT:
            if (x - size - speed >= -1) 
                x -= speed;
            break;
        case RIGHT:
            if (x + size + speed <= 1) 
                x += speed;
            break;
    }
}

void Ghost::changeDirection() {
    int random = rand() % 4; 

    switch (random) {
        case 0:
            direction = Direction::UP;
            break;
        case 1:
            direction = Direction::DOWN;
            break;
        case 2:
            direction = Direction::LEFT;
            break;
        case 3:
            direction = Direction::RIGHT;
            break;
    }
}

float Ghost::getX() {
    return x;
}

float Ghost::getY() {
    return y;
}
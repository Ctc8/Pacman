#include "Pellet.h"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

void Pellet::eat() {
    isEaten = true;
}

float Pellet::getX() const {
    return x;
}

float Pellet::getY() const {
    return y;
}



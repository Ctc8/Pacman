#include "Pellet.h"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

Pellet::Pellet(float x, float y) : x(x), y(y), isEaten(false) {}

float Pellet::getX() const {
    return x;
}

float Pellet::getY() const {
    return y;
}

bool Pellet::getIsEaten() const {
    return isEaten;
}

void Pellet::eat() {
    isEaten = true;
}

void Pellet::draw() const {
    if (!isEaten) {
        glColor3f(1.0, 1.0, 1.0); 
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y); 
        for(int i = 0; i <= 50; i++) {
            float angle = 2.0f * 3.1415926f * float(i) / float(50);
            float dx = 0.01f * cosf(angle);
            float dy = 0.01f * sinf(angle);
            glVertex2f(x + dx, y + dy);
        }
        glEnd();
    }
}
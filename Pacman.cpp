#define GL_SILENCE_DEPRECATION
#include "Pacman.h"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

void Pacman::draw() {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 1.0, 0.0); // Yellow
    glVertex2f(x, y); // center of circle
    for (int i = angle + 30; i <= angle + 320; i++){
        float degInRad = i*PI/180;
        glVertex2f(x + cos(degInRad)*0.05, y + sin(degInRad)*0.05);
    }
    glEnd();
}

void Pacman::moveUp() {
    y += 0.01;
    angle = 90;
}

void Pacman::moveDown() {
    y -= 0.01;
    angle = 270;
}

void Pacman::moveLeft() {
    x -= 0.01;
    angle = 180;
}

void Pacman::moveRight() {
    x += 0.01;
    angle = 0;
}
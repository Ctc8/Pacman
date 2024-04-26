#define GL_SILENCE_DEPRECATION
#include "Pacman.h"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <utility>

void Pacman::draw() {
    float radius = 0.04; 

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 1.0, 0.0); 
    glVertex2f(x, y); 
    for (int i = 0; i <= 360; i++){
        float degInRad = i*PI/180;
        glVertex2f(x + cos(degInRad)*radius, y + sin(degInRad)*radius);
    }
    glEnd();
}

void getPosition();

void Pacman::moveUp() {
    y = y + 0.011;
    angle = 90; 
}

void Pacman::moveDown() {
    y = y - 0.011;
    angle = 270; 
}

void Pacman::moveLeft() {
    x = x - 0.011;
    angle = 180; 
}

void Pacman::moveRight() {
    x = x + 0.011;
    angle = 0; 
}

float Pacman::getX() {
    return x;
}

float Pacman::getY() {
    return y;
}
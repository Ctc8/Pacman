#define GL_SILENCE_DEPRECATION
#include "Ghost.h"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <math.h>

#define PI 3.1415926535897932384626433832795

void Ghost::draw() {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 0.0, 0.0); // Red color for the ghost
    glVertex2f(x, y); // center of circle
    for (int i = 0; i <= 360; i++){
        float degInRad = i*PI/180;
        glVertex2f(x + cos(degInRad)*0.045, y + sin(degInRad)*0.045); 
    }
    glEnd();
}
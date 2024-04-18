#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <math.h>

#include "Pacman.h"
#include "Ghost.h"

#define PI 3.1415926535897932384626433832795

Pacman pacman;
Ghost ghost;
char currentDirection = ' ';

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    pacman.draw();
    ghost.draw();

    glutSwapBuffers();
}

void timer(int) {
    switch (currentDirection) {
        case 'w':
            pacman.moveUp();
            break;
        case 's':
            pacman.moveDown();
            break;
        case 'a':
            pacman.moveLeft();
            break;
        case 'd':
            pacman.moveRight();
            break;
    }

    // Redraw the scene
    glutPostRedisplay();

    // Set the timer to call this function again after 20 milliseconds
    glutTimerFunc(20, timer, 0);
}

void keyboard(unsigned char key, int x, int y) {
    currentDirection = key;
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(1000, 1000);

    glutCreateWindow("Pacman Game");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    init();

    glutTimerFunc(0, timer, 0);

    glutMainLoop();
}
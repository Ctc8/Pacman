#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <math.h>

#include "Pacman.h"
#include "Ghost.h"

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

    static int changeDirectionCounter = 0;
    if (changeDirectionCounter++ % 80 == 0) { 
        ghost.changeDirection();
    }
    ghost.move();

    glutPostRedisplay();

    glutTimerFunc(20, timer, 0);
}



void keyboard(unsigned char key, int x, int y) {
    currentDirection = key;
}

void init() {
    glClearColor(0.5, 0.5, 0.5, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(700, 700);

    glutCreateWindow("Pacman Game");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    init();

    glutTimerFunc(0, timer, 0);

    glutMainLoop();
}
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <math.h>

#include "Pacman.h"
#include "Ghost.h"

Pacman pacman;
Ghost redGhost(1.0, 0.0, 0.0); // Red ghost
Ghost greenGhost(0.0, 1.0, 0.0); // Green ghost
Ghost blueGhost(0.0, 0.0, 1.0); // Blue ghost

char currentDirection = ' ';

bool gameOver = false;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    if (gameOver) {
        const char *gameOverText = "Game Over";
        glColor3f(1.0, 0.0, 0.0); // Set color to red
        glRasterPos2f(-0.1, 0); // Adjust position as needed
        for (const char *c = gameOverText; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
        }
    } 
    else {
        pacman.draw();
        redGhost.draw();
        greenGhost.draw();
        blueGhost.draw();
    }

    glutSwapBuffers();
}

bool checkCollision(Pacman pacman, Ghost ghost) {
    float threshold = 0.03; 
    return abs(pacman.getX() - ghost.getX()) <= threshold && abs(pacman.getY() - ghost.getY()) <= threshold;
}

void timer(int) {
    if (gameOver) {
        return;
    }

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
    if (changeDirectionCounter++ % 65 == 0) { 
        redGhost.changeDirection();
        greenGhost.changeDirection();
        blueGhost.changeDirection();
    }
    redGhost.move();
    greenGhost.move();
    blueGhost.move();

    if (checkCollision(pacman, redGhost) || checkCollision(pacman, greenGhost) || checkCollision(pacman, blueGhost)) {
        gameOver = true;
    }

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
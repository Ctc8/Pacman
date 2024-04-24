#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <math.h>
#include <vector>


#include "Pacman.h"
#include "Ghost.h"
#include "Pellet.h" // Include the Pellet class
// #include "Score.h" // Include the Score class

Pacman pacman;
Ghost redGhost(1.0, 0.0, 0.0); // Red ghost
Ghost greenGhost(0.0, 1.0, 0.0); // Green ghost
Ghost blueGhost(0.0, 0.0, 1.0); // Blue ghost

std::vector<Pellet> pellets; // Create a vector to hold the pellets
// Score score; // Create a Score object

char currentDirection = ' ';

bool gameOver = false;

void display() {
    glClearColor(135/255.0, 255/255.0, 153/255.0, 1.0); // Set clear color to (135, 255, 153)
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

        for (const Pellet &pellet : pellets) {
            pellet.draw();
        }

        // Display the score
        // score.display();
    }

    glutSwapBuffers();
}

bool checkCollision(Pacman pacman, Ghost ghost) {
    float threshold = 0.03; 
    return abs(pacman.getX() - ghost.getX()) <= threshold && abs(pacman.getY() - ghost.getY()) <= threshold;
}

bool isColliding(Pacman pacman, Pellet pellet) {
    float threshold = 0.03; // Adjust as needed
    return abs(pacman.getX() - pellet.getX()) <= threshold && abs(pacman.getY() - pellet.getY()) <= threshold;
}

void timer(int) {
    if (gameOver) {
        return;
    }

    for (Pellet &pellet : pellets) {
    if (isColliding(pacman, pellet)) {
        pellet.eat();
    }
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

    srand(static_cast<unsigned>(time(0)));

    for (int i = 0; i < 20; i++) {
        float x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f - 1.0f;
        float y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f - 1.0f;

        pellets.push_back(Pellet(x, y));
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(800, 800);

    glutCreateWindow("Pacman Game");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    init();

    glutTimerFunc(0, timer, 0);

    glutMainLoop();
}
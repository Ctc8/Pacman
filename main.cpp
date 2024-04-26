#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <math.h>
#include <vector>
#include <sstream>
#include <iostream>


#include "Pacman.h"
#include "Ghost.h"
#include "Pellet.h" 
#include "Score.h" 

Pacman pacman;
Ghost redGhost(1.0, 0.0, 0.0); 
Ghost greenGhost(0.0, 1.0, 0.0); 
Ghost blueGhost(0.0, 0.0, 1.0); 
Ghost orangeGhost(1.0, 0.5, 0.0); 

std::vector<Pellet> pellets; 
Score score; 

int currentLevel = 1;

char currentDirection = ' ';

bool gameOver = false;


void display() {
    glClearColor(135/255.0, 255/255.0, 153/255.0, 1.0); 
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    if (gameOver) {
        const char *gameOverText = "Game Over";
        glColor3f(1.0, 0.0, 0.0); 
        glRasterPos2f(-0.1, 0);
        for (const char *c = gameOverText; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }
        
    } 
    else {
        pacman.draw();
        redGhost.draw();
        greenGhost.draw();
        blueGhost.draw();
        orangeGhost.draw();

        for (const Pellet &pellet : pellets) {
            pellet.draw();
        }
    }
    std::stringstream ss;
    ss << "Score: " << score.getScore();
    std::string scoreString = ss.str();
    const char *scoreText = scoreString.c_str();
    glColor3f(1.0, 0.0, 0.0); 
    glRasterPos2f(-0.9, 0.9);
    for (const char *c = scoreText; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    std::ostringstream levelStr;
    levelStr << "Level: " << currentLevel;
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(-0.9, -0.9);
    const char *levelText = levelStr.str().c_str();
    for (const char *c = levelText; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glutSwapBuffers();
}

void resetGameLose() {
    std::cout << "lost the game. Resetting game..." << std::endl;
    currentLevel = 1;

    pacman = Pacman(); 
    redGhost = Ghost(1.0, 0.0, 0.0); 
    greenGhost = Ghost(0.0, 1.0, 0.0); 
    blueGhost = Ghost(0.0, 0.0, 1.0); 
    orangeGhost = Ghost(1.0, 0.5, 0.0); 

    pellets.clear(); 
    for (int i = 0; i < 20; i++) { 
        float x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f - 1.0f;
        float y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f - 1.0f;
        pellets.push_back(Pellet(x, y));
    }

    score = Score();
    currentDirection = 'w'; 
    gameOver = false; 

    std::cout << "Game reset." << std::endl;

    glutPostRedisplay(); 
}

void resetGameWin() {
    std::cout << "won the game. going to next level" << std::endl;
    currentLevel++;

    pacman = Pacman(); 
    redGhost = Ghost(1.0, 0.0, 0.0); 
    greenGhost = Ghost(0.0, 1.0, 0.0); 
    blueGhost = Ghost(0.0, 0.0, 1.0); 
    orangeGhost = Ghost(1.0, 0.5, 0.0); 

    pellets.clear(); 
    for (int i = 0; i < 20; i++) { 
        float x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f - 1.0f;
        float y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f - 1.0f;
        pellets.push_back(Pellet(x, y));
    }

    currentDirection = 'w'; 
    gameOver = false; 

    std::cout << "Game reset." << std::endl;

    glutPostRedisplay(); 
}

bool checkCollision(Pacman pacman, Ghost ghost) {
    float threshold = 0.03; 
    return abs(pacman.getX() - ghost.getX()) <= threshold && abs(pacman.getY() - ghost.getY()) <= threshold;
}

bool checkCollisionWithPellet(Pacman pacman, Pellet pellet) {
    float threshold = 0.03; 
    return abs(pacman.getX() - pellet.getX()) <= threshold && abs(pacman.getY() - pellet.getY()) <= threshold;
}

void timer(int) {
    for (Pellet &pellet : pellets) {
    if (checkCollisionWithPellet(pacman, pellet)) {
        pellet.eat();
        score.increase(1);
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
        orangeGhost.changeDirection();
    }
    redGhost.move();
    greenGhost.move();
    blueGhost.move();
    orangeGhost.move();

    if (checkCollision(pacman, redGhost) || checkCollision(pacman, greenGhost) || checkCollision(pacman, orangeGhost) || checkCollision(pacman, blueGhost)) {
        gameOver = true;
    }

for (int i = 0; i < pellets.size(); i++) {
    if (checkCollisionWithPellet(pacman, pellets[i])) {
        pellets[i].eat();
        score.increase(1);
        pellets.erase(pellets.begin() + i);
        break;
    }
}

    if (pellets.empty()) {
        resetGameWin();

    }

    glutPostRedisplay();

    glutTimerFunc(20, timer, 0);
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

void keyboard(unsigned char key, int x, int y) {
    if (key == 'r' || key == 'R') {
        if (gameOver) {
            resetGameLose();
            std::cout << "keyboard func" << std::endl;
        }
    } else {
        currentDirection = key;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(1100, 1100);

    glutCreateWindow("Pacman Game");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    init();

    glutTimerFunc(0, timer, 0);

    glutMainLoop();
}




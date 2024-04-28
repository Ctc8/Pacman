#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <math.h>
#include <vector>
#include <sstream>
#include <iostream>

#include "Ghost.h"
#include "Pacman.h"
#include "Pellet.h" 
#include "Score.h" 
#include "GameEntity.h"

std::vector<GameEntity*> entities;
GameEntity* pacman = new Pacman(0.0, 0.0, 1.0, 1.0, 0.0);

GameEntity* redGhost = new Ghost(-0.8, 0.0, 1.0, 0.0, 0.0); 
GameEntity* greenGhost = new Ghost(-0.6, 0.0, 0.0, 1.0, 0.0); 
GameEntity* blueGhost = new Ghost(-0.4, 0.0, 0.0, 0.0, 1.0); 
GameEntity* orangeGhost = new Ghost(-0.2, 0.0, 1.0, 0.5, 0.0); 

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
        pacman->draw();
        redGhost->draw();
        greenGhost->draw();
        blueGhost->draw();
        orangeGhost->draw();

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


    GameEntity pacman(0.0, 0.0, 1.0, 1.0, 0.0);
    GameEntity redGhost(-0.8, 0.0, 1.0, 0.0, 0.0); 
    GameEntity greenGhost(-0.6, 0.0, 0.0, 1.0, 0.0); 
    GameEntity blueGhost(-0.4, 0.0, 0.0, 0.0, 1.0); 
    GameEntity orangeGhost(-0.2, 0.0, 1.0, 0.5, 0.0); 

    pellets.clear(); 
    for (int i = 0; i < 15; i++) { 
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

GameEntity pacman(0.0, 0.0, 1.0, 1.0, 0.0);
GameEntity redGhost(-0.8, 0.0, 1.0, 0.0, 0.0); 
GameEntity greenGhost(-0.6, 0.0, 0.0, 1.0, 0.0); 
GameEntity blueGhost(-0.4, 0.0, 0.0, 0.0, 1.0); 
GameEntity orangeGhost(-0.2, 0.0, 1.0, 0.5, 0.0); 

    pellets.clear(); 
    for (int i = 0; i < 15; i++) { 
        float x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f - 1.0f;
        float y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f - 1.0f;
        pellets.push_back(Pellet(x, y));
    }

    currentDirection = 'w'; 
    gameOver = false; 

    std::cout << "Game reset." << std::endl;

    glutPostRedisplay(); 
}

bool checkCollisionWithGhost(GameEntity* pacman, GameEntity* ghost) {
    float threshold = 0.03; 
    bool collision = abs(pacman->getX() - ghost->getX()) <= threshold && abs(pacman->getY() - ghost->getY()) <= threshold;
    if (collision) {
        resetGameLose();
    }
    return collision;
}

bool checkCollisionWithPellet(GameEntity* pacman, Pellet* pellet) {
    float threshold = 0.03; 
    bool collision = abs(pacman->getX() - pellet->getX()) <= threshold && abs(pacman->getY() - pellet->getY()) <= threshold;
    
    if (collision) {
        pellet->eat(); // The pellet is eaten when a collision occurs
        score.increase(1); // Increase the score by 1
    }

    return collision;
}

void timer(int) {

    if (checkCollisionWithGhost(pacman, redGhost) ||
        checkCollisionWithGhost(pacman, greenGhost) ||
        checkCollisionWithGhost(pacman, blueGhost) ||
        checkCollisionWithGhost(pacman, orangeGhost)) {
            gameOver = true;
        }

    for (auto it = pellets.begin(); it != pellets.end(); ) {
        if (checkCollisionWithPellet(pacman, &(*it))) {
            it = pellets.erase(it); // Remove the eaten pellet from the game
        } else {
            ++it;
        }
    }


switch (currentDirection) {
    case 'w':
        pacman->move(UP);
        break;
    case 's':
        pacman->move(DOWN);
        break;
    case 'a':
        pacman->move(LEFT);
        break;
    case 'd':
        pacman->move(RIGHT);
        break;
}
    static int changeDirectionCounter = 0;
    if (changeDirectionCounter++ % 65 == 0) { 
        redGhost->changeDirection();
        greenGhost->changeDirection();
        blueGhost->changeDirection();
        orangeGhost->changeDirection();
    }
    redGhost->move();
    greenGhost->move();
    blueGhost->move();
    orangeGhost->move();

    if (pellets.empty()) {
        resetGameWin();
    }

    glutPostRedisplay();

    glutTimerFunc(20, timer, 0);
}

void init() {
    glClearColor(0.5, 0.5, 0.5, 1.0);

    srand(static_cast<unsigned>(time(0)));

    for (int i = 0; i < 15; i++) {
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

    entities.push_back(pacman);
    entities.push_back(redGhost);
    entities.push_back(greenGhost);
    entities.push_back(blueGhost);
    entities.push_back(orangeGhost);

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



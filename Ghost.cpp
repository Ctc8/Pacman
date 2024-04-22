#define GL_SILENCE_DEPRECATION
#include "Ghost.h"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <math.h>
#include <stdlib.h> // For rand()

#define PI 3.1415926535897932384626433832795

void Ghost::draw() {
    float size = 0.03; // Size of the square

    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0); // Red color for the ghost
    glVertex2f(x - size, y - size); // Bottom left corner
    glVertex2f(x + size, y - size); // Bottom right corner
    glVertex2f(x + size, y + size); // Top right corner
    glVertex2f(x - size, y + size); // Top left corner
    glEnd();
}

void Ghost::move() {
    float speed = 0.01; // Adjust speed as needed
    float size = 0.03; // Size of the square

    switch (direction) {
        case UP:
            if (y + size + speed <= 1) // Check if the ghost is not at the top edge
                y += speed;
            break;
        case DOWN:
            if (y - size - speed >= -1) // Check if the ghost is not at the bottom edge
                y -= speed;
            break;
        case LEFT:
            if (x - size - speed >= -1) // Check if the ghost is not at the left edge
                x -= speed;
            break;
        case RIGHT:
            if (x + size + speed <= 1) // Check if the ghost is not at the right edge
                x += speed;
            break;
    }
}

void Ghost::changeDirection() {
    int random = rand() % 4; // Generate a random number between 0 and 3

    switch (random) {
        case 0:
            direction = Direction::UP;
            break;
        case 1:
            direction = Direction::DOWN;
            break;
        case 2:
            direction = Direction::LEFT;
            break;
        case 3:
            direction = Direction::RIGHT;
            break;
    }
}
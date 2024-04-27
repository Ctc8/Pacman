#define GL_SILENCE_DEPRECATION
#include "GameEntity.h"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <math.h>
#include <stdlib.h> 

#define PI 3.1415926535897932384626433832795

void GameEntity::draw() {
  float size = 0.04; 
  glColor3f(color[0], color[1], color[2]);

  glBegin(GL_QUADS);
  glVertex2f(x - size, y - size);
  glVertex2f(x + size, y - size);
  glVertex2f(x + size, y + size); 
  glVertex2f(x - size, y + size); 
  glEnd();
}

void GameEntity::move() {
  float speed = 0.01; 
  float size = 0.03; 

  switch (direction) {
    case UP:
      if (y + size + speed <= 1) 
        y += speed;
      break;
    case DOWN:
      if (y - size - speed >= -1)  
        y -= speed;
      break;
    case LEFT:
      if (x - size - speed >= -1) 
        x -= speed;
      break;
    case RIGHT:
      if (x + size + speed <= 1) 
        x += speed;
      break;
  }
}

void GameEntity::changeDirection() {
  int random = rand() % 6; 

  switch (random) {
    case 0:
      direction = UP;
      break;
    case 1:
      direction = DOWN;
      break;
    case 2:
      direction = LEFT;
      break;
    case 3:
      direction = RIGHT;
      break;
  }
}

float GameEntity::getX() {
  return x;
}

float GameEntity::getY() {
  return y;
}


GameEntity::GameEntity(float x, float y, float r, float g, float b) : x(x), y(y) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
}


void GameEntity::move(Direction direction) {
    switch (direction) {
        case UP:
            y = y + 0.011;
            break;
        case DOWN:
            y = y - 0.011;
            break;
        case LEFT:
            x = x - 0.011;
            break;
        case RIGHT:
            x = x + 0.011;
            break;
    }
}
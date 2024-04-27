#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

enum Direction { UP, DOWN, LEFT, RIGHT };

class GameEntity {
public:
    float x;
    float y;
    Direction direction;
    float speed;
    float color[3];

    GameEntity(float x, float y, float r, float g, float b);

    virtual void draw();
    virtual void move();
    virtual void changeDirection();

    float getX();
    float getY();

    // For pacman
    void move(Direction direction);

    
};

#endif 
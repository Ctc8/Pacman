#ifndef PELLET_H
#define PELLET_H

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <math.h>
#include <vector>
#include <cstdlib> 
#include <ctime> 

class Pellet {
private:
    float x, y;
    bool isEaten; 

public:
    Pellet(float x, float y);

    float getX() const;
    float getY() const;
    bool getIsEaten() const;
    void eat();
    void draw() const;
};

#endif
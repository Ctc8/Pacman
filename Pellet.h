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
    bool isEaten; // Flag to mark pellet as eaten

public:
    Pellet(float x, float y) : x(x), y(y), isEaten(false) {}

    float getX() const {
        return x;
    }

    float getY() const {
        return y;
    }

    bool getIsEaten() const {
        return isEaten;
    }

    void eat() {
        isEaten = true;
    }

  void draw() const {
    if (!isEaten) {
        glColor3f(1.0, 1.0, 1.0); // White
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y); // Center of circle
        for(int i = 0; i <= 50; i++) {
            float angle = 2.0f * 3.1415926f * float(i) / float(50);
            float dx = 0.01f * cosf(angle);
            float dy = 0.01f * sinf(angle);
            glVertex2f(x + dx, y + dy);
        }
        glEnd();
    }
}
};



#endif



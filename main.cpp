#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <math.h>

#define PI 3.1415926535897932384626433832795

float pacman_x = 0.0;
float pacman_y = 0.0;
float pacman_angle = 0.0;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Draw Pacman
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 1.0, 0.0); // Yellow
    glVertex2f(pacman_x, pacman_y); // center of circle
    for (int i = pacman_angle; i <= pacman_angle + 300; i++){
        float degInRad = i*PI/180;
        glVertex2f(pacman_x + cos(degInRad)*0.1, pacman_y + sin(degInRad)*0.1);
    }
    glEnd();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            pacman_y += 0.1;
            pacman_angle = 90;
            break;
        case 's':
            pacman_y -= 0.1;
            pacman_angle = 270;
            break;
        case 'a':
            pacman_x -= 0.1;
            pacman_angle = 180;
            break;
        case 'd':
            pacman_x += 0.1;
            pacman_angle = 0;
            break;
    }
    glutPostRedisplay();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(500, 500);

    glutCreateWindow("Pacman Game");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    init();

    glutMainLoop();
}
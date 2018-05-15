#include <GL/freeglut.h>
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include <vector>
#include <cmath>
#include <iostream>

#include "Point.h"
#include "Utils.h"

#define PI +3.14159265358979323846

using namespace std;

const char fileName[] = "curvaAbierta.in"; 

float eyeX = 0.0f, eyeY = 0.0f, eyeZ = -5.0f, centerX = 0.0f, centerY = 0.0f, centerZ = 0.0f, upX = 0.0f, upY = 1.0f, upZ = 0.0f;
float rotationX = 0.0, rotationY = 0.0, rotationZ = 0.0;

Figure* figure = NULL;

void setHexColor(int color) {
  float r = ((0xFF0000 & color) >> 16) / 255.0;
  float g = ((0x00FF00 & color) >> 8) / 255.0;
  float b = (0x0000FF & color) / 255.0;
  glColor3f(r, g, b);
}

struct Figure {
  vector<Point> points;
  Figure(char* fileName, float revRadius) {
    Utils::readPoints(fileName, points);
  }

  void draw() {
    glPushMatrix();

    glPopMatrix();
  }

};

GLint ancho=800;
GLint alto=800;

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0f, (GLfloat)width/(GLfloat)height, 1.0f, 30.0f);

    glMatrixMode(GL_MODELVIEW);

    ancho = width;
    alto = height;
}

void onKeyPress(unsigned char key, int x, int y) {
  switch (key) {
    case 'w':
    rotationX += 1.0;
    break;
    case 'a':
    rotationY -= 1.0;
    break;
    case 's':
    rotationX -= 1.0;
    break;
    case 'd':
    rotationY += 1.0;
    break;
    case 'q':
    rotationZ -= 1.0;
    break;
    case 'e':
    rotationZ += 1.0;
    break;
  }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

    glRotatef(rotationX, 1, 0, 0);
    glRotatef(rotationY, 0, 1, 0);
    glRotatef(rotationZ, 0, 0, 1);

    glutWireTeapot(1);

    glutSwapBuffers();
}

void init() {
    glClearColor(0,0,0,0);
    ancho = 400;
    alto = 400;
    figure = new Figure();
}


void idle()
{
    display();
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glEnable(GL_DEPTH_TEST);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(ancho, alto);
    glutCreateWindow("Solidos");
    init();


    glutDisplayFunc(display);
    glutKeyboardFunc(onKeyPress);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}

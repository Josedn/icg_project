//#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <vector>
#include <cmath>
#include <iostream>

#define PI +3.14159265358979323846

using namespace std;

struct Point {
  float x, y, z;
  Point(float _x, float _y, float _z) {
    x = _x;
    y = _y;
    z = _z;
  }
};

struct Ellipse {
  float ar, br;

  Ellipse(float a, float b) {
    ar = a;
    br = b;
  }

  Point getPoint(float t) {
    Point p(ar*cos(t), br*sin(t), 0.0);
    return p;
  }

  void draw() {
    glBegin(GL_LINES);
    for(float t = 0.0; t <= 360.0; t+=0.1) {
      float r = t*PI/180.0;
      Point p = getPoint(t);
      glVertex3f(p.x, p.y, p.z);
    }
    glEnd();
  }

};

class SolarElement {
public:
  vector<SolarElement*> children;
  Ellipse *orbit;
  GLfloat orbitCurrentAngle, orbitTranslationIncrement;
  GLfloat rotationCurrentAngle, rotationIncrement, rotationX, rotationY, rotationZ;
  GLfloat scaleX, scaleY, scaleZ;
  GLfloat translateX, translateY, translateZ;

  SolarElement(GLfloat orbitTranslationIncrement, GLfloat rotationIncrement, GLfloat rotationX, GLfloat rotationY, GLfloat rotationZ, GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ, GLfloat translateX, GLfloat translateY, GLfloat translateZ, Ellipse *orbit) {
    this->rotationCurrentAngle = 0.0;
    this->orbitCurrentAngle = 0.0;
    this->orbitTranslationIncrement = orbitTranslationIncrement;
    this->rotationIncrement = rotationIncrement;
    this->rotationX = rotationX;
    this->rotationY = rotationY;
    this->scaleX = scaleX;
    this->scaleY = scaleY;
    this->scaleZ = scaleZ;
    this->translateX = translateX;
    this->translateY = translateY;
    this->translateZ = translateZ;
    this->orbit = orbit;
  }

  void actualTick(GLfloat delta) {
    this->rotationCurrentAngle += this->rotationIncrement;
    this->orbitCurrentAngle += this->orbitTranslationIncrement;
  }

  void tick(GLfloat delta) {
    actualTick(delta);

    int childrenLen = this->children.size();
    for (int i = 0; i < childrenLen; i++) {
      this->children[i]->tick(delta);
    }
  }

  void appendChild(SolarElement *child) {
    children.push_back(child);
  }

  void actualDraw() {
    glTranslatef(translateX, translateY, translateZ);
    orbit->draw();
    Point p = orbit->getPoint(this->orbitCurrentAngle);
    glTranslatef(p.x, p.y, p.z);

    glRotatef(rotationCurrentAngle, 1.0f, 0.0f, 0.0f);
    glScalef(scaleX, scaleY, scaleZ);

    glColor3f(1.0f, 1.0f, 1.0f);
    glutWireTeapot(1.0f);
    glutWireCube(1.5f);
  }

  void draw() {
    glPushMatrix();

    actualDraw();

    int childrenLen = this->children.size();
    for (int i = 0; i < childrenLen; i++) {
      this->children[i]->draw();
    }

    glPopMatrix();
  }
};

GLint ancho=400;
GLint alto=400;

SolarElement *sun = NULL;

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0f, (GLfloat)width/(GLfloat)height, 1.0f, 20.0f);

    glMatrixMode(GL_MODELVIEW);

    ancho = width;
    alto = height;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    float eyeX = 0.0f, eyeY = 0.0f, eyeZ = -8.0f, centerX = 0.0f, centerY = 0.0f, centerZ = 0.0f, upX = 0.0f, upY = 1.0f, upZ = 0.0f;

    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

    if (sun != NULL) {
      sun->tick(0.1);
      sun->draw();
    }


    glFlush();
    glutSwapBuffers();
}

void init()
{
    glClearColor(0,0,0,0);
    ancho = 400;
    alto = 400;
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
    glutCreateWindow("Sistema solar");
    init();

    GLfloat orbitTranslationIncrement = 0.01, rotationIncrement = 0.5, rotationX = 1.0, rotationY = 0.0, rotationZ = 0.0, scaleX = 1.0, scaleY = 1.0, scaleZ = 1.0, translateX = 0.0, translateY = 0.0, translateZ = 0.0;
    Ellipse *sunOrbit = new Ellipse(1.0, 2.0);
    sun = new SolarElement(orbitTranslationIncrement, rotationIncrement, rotationX, rotationY, rotationZ, scaleX, scaleY, scaleZ, translateX, translateY, translateZ, sunOrbit);

    SolarElement *moon = new SolarElement(orbitTranslationIncrement, rotationIncrement, rotationX, rotationY, rotationZ, scaleX / 2, scaleY / 2, scaleZ / 2, translateX, translateY, translateZ, sunOrbit);
    sun->appendChild(moon);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
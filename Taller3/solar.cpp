//#include <GL/glut.h> g++ -w main.cpp -framework GLUT -framework OpenGL
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

void setHexColor(int color) {
  float r = ((0xFF0000 & color) >> 16) / 255.0;
  float g = ((0x00FF00 & color) >> 8) / 255.0;
  float b = (0x0000FF & color) / 255.0;
  glColor3f(r, g, b);
}

void drawCube(int colTop, int colFront, int colRight, int colLeft, int colBottom, int colBack) {
  glBegin(GL_QUADS);
	// top
	setHexColor(colTop);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	glEnd();

	glBegin(GL_QUADS);
	// front
	setHexColor(colFront);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);

	glEnd();

	glBegin(GL_QUADS);
	// right
	setHexColor(colRight);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);

	glEnd();

	glBegin(GL_QUADS);
	// left
	setHexColor(colLeft);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);

	glEnd();

	glBegin(GL_QUADS);
	// bottom
	setHexColor(colBottom);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);

	glEnd();

	glBegin(GL_QUADS);
	// back
	setHexColor(colBack);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	glEnd();
}

void drawPyramidSquareBase(int colA, int colB, int colC, int colD) {
  glBegin(GL_TRIANGLES);

      setHexColor(colA);
      glVertex3f( 0.0f, 1.0f, 0.0f);
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glVertex3f(1.0f, -1.0f, 1.0f);

      setHexColor(colB);
      glVertex3f(0.0f, 1.0f, 0.0f);
      glVertex3f(1.0f, -1.0f, 1.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);

      setHexColor(colC);
      glVertex3f(0.0f, 1.0f, 0.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);

      setHexColor(colD);
      glVertex3f( 0.0f, 1.0f, 0.0f);
      glVertex3f(-1.0f,-1.0f,-1.0f);
      glVertex3f(-1.0f,-1.0f, 1.0f);
   glEnd();
}

// TODO - Translate to origin.
void tetrahedron() {
  glBegin(GL_TRIANGLES);

      glColor3f(1.0f, 0.0f, 0.0f);
      glVertex3f(0.0f, 0.0f, 1.0f);
      glVertex3f(0.0f, 0.0f, 0.0f);
      glVertex3f(1.0f, 0.0f, 0.5f);

      glColor3f(0.0f, 0.0f, 1.0f);
      glVertex3f(0.0f, 0.0f, 1.0f);
      glVertex3f(0.0f, 0.0f, 0.0f);
      glVertex3f(0.5f, 1.0f, 0.5f);

      glColor3f(0.0f, 1.0f, 0.0f);
      glVertex3f(0.0f, 0.0f, 0.0f);
      glVertex3f(1.0f, 0.0f, 0.5f);
      glVertex3f(0.5f, 1.0f, 0.5f);

      glColor3f(1.0f,1.0f,0.0f);
      glVertex3f(0.0f, 0.0f, 1.0f);
      glVertex3f(1.0f, 0.0f, 0.5f);
      glVertex3f(0.5f, 1.0f, 0.5f);
   glEnd();
}

void octahedron() {
  glBegin(GL_TRIANGLES);

      glColor3f(1.0f, 0.0f, 0.0f);
      glVertex3f(0.0f, 0.5f, 0.0f);
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glVertex3f(1.0f, -1.0f, 1.0f);

      glColor3f(0.0f, 0.0f, 1.0f);
      glVertex3f(0.0f, 0.5f, 0.0f);
      glVertex3f(1.0f, -1.0f, 1.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);

      glColor3f(0.0f, 1.0f, 0.0f);
      glVertex3f(0.0f, 0.5f, 0.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);

      glColor3f(1.0f,1.0f,0.0f);
      glVertex3f(0.0f, 0.5f, 0.0f);
      glVertex3f(-1.0f,-1.0f,-1.0f);
      glVertex3f(-1.0f,-1.0f, 1.0f);
   glEnd();
   glBegin(GL_TRIANGLES);

       glColor3f(0.0f, 0.0f, 1.0f);
       glVertex3f(0.0f, -2.5f, 0.0f);
       glVertex3f(-1.0f, -1.0f, 1.0f);
       glVertex3f(1.0f, -1.0f, 1.0f);

       glColor3f(0.0f, 1.0f, 1.0f);
       glVertex3f(0.0f, -2.5f, 0.0f);
       glVertex3f(1.0f, -1.0f, 1.0f);
       glVertex3f(1.0f, -1.0f, -1.0f);

       glColor3f(1.0f, 1.0f, 0.0f);
       glVertex3f(0.0f, -2.5f, 0.0f);
       glVertex3f(1.0f, -1.0f, -1.0f);
       glVertex3f(-1.0f, -1.0f, -1.0f);

       glColor3f(1.0f,0.0f,1.0f);
       glVertex3f(0.0f, -2.5f, 0.0f);
       glVertex3f(-1.0f,-1.0f,-1.0f);
       glVertex3f(-1.0f,-1.0f, 1.0f);
    glEnd();
}

class SolarElement {
public:
  vector<SolarElement*> children;
  Ellipse *orbit;
  GLfloat orbitCurrentAngle, orbitTranslationIncrement;
  GLfloat rotationCurrentAngle, rotationIncrement, rotationX, rotationY, rotationZ;
  GLfloat orbitAngle, orbitRotationX, orbitRotationY, orbitRotationZ;
  GLfloat scaleX, scaleY, scaleZ;
  GLfloat translateX, translateY, translateZ;
  int type;

  SolarElement(GLfloat orbitTranslationIncrement, GLfloat orbitCurrentAngle, GLfloat rotationIncrement, GLfloat rotationX, GLfloat rotationY, GLfloat rotationZ, GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ, GLfloat translateX, GLfloat translateY, GLfloat translateZ, Ellipse *orbit, GLfloat orbiteAngle, GLfloat orbitRotationX, GLfloat orbitRotationY, GLfloat orbitRotationZ, int type) {
    this->rotationCurrentAngle = 0.0;
    this->orbitCurrentAngle = orbitCurrentAngle;
    this->orbitTranslationIncrement = orbitTranslationIncrement;
    this->rotationIncrement = rotationIncrement;
    this->rotationX = rotationX;
    this->rotationY = rotationY;
    this->rotationZ = rotationZ;
    this->scaleX = scaleX;
    this->scaleY = scaleY;
    this->scaleZ = scaleZ;
    this->translateX = translateX;
    this->translateY = translateY;
    this->translateZ = translateZ;
    this->orbit = orbit;
    this->orbitAngle = orbiteAngle;
    this->orbitRotationX = orbitRotationX;
    this->orbitRotationY = orbitRotationY;
    this->orbitRotationZ = orbitRotationZ;
    this->type = type;
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
    glRotatef(orbitAngle, orbitRotationX, orbitRotationY, orbitRotationZ);
    glTranslatef(translateX, translateY, translateZ);
    if (orbit != NULL) {
      orbit->draw();
      Point p = orbit->getPoint(this->orbitCurrentAngle);
      glTranslatef(p.x, p.y, p.z);
    }

    glRotatef(rotationCurrentAngle, rotationX, rotationY, rotationZ);
    glScalef(scaleX, scaleY, scaleZ);

    glColor3f(1.0f, 1.0f, 1.0f);

    switch (type) {
      case 0:
        octahedron();
      break;
      case 1:
        tetrahedron();
      break;
      case 2:
        drawPyramidSquareBase(0xFF0000, 0x0000FF, 0x00FFFF, 0xFFFF00);
      break;
      case 3:
        drawCube(0x00FF00, 0xFF00FF, 0xFF0000, 0x0000FF, 0x00FFFF, 0xFFFF00);
      break;
    }
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

    GLfloat orbitTranslationIncrement = 0.01, rotationIncrement = 0.5, rotationX = 0.0, rotationY = 1.0, rotationZ = 0.0, scaleX = 1.0, scaleY = 1.0, scaleZ = 1.0, translateX = 0.0, translateY = 0.0, translateZ = 0.0;

    sun = new SolarElement(orbitTranslationIncrement, 0, rotationIncrement, rotationX, rotationY, rotationZ, scaleX, scaleY, scaleZ, translateX, translateY, translateZ, NULL, 0.0, 0.0, 0.0, 0.0, 3);

    SolarElement *planet1 = new SolarElement(orbitTranslationIncrement, 1.5, rotationIncrement, rotationX, rotationY, rotationZ, scaleX / 2, scaleY / 2, scaleZ / 2, translateX, translateY, translateZ, new Ellipse(1.5, 2.0), 90.0, 0.0, 0.0, 1.0, 1);
    planet1->appendChild(new SolarElement(orbitTranslationIncrement, 0, rotationIncrement, rotationX, rotationY, rotationZ, scaleX / 2, scaleY / 2, scaleZ / 2, translateX, translateY, translateZ, new Ellipse(2.0, 2.0), 0.0, 0.0, 0.0, 0.0, 0));

    SolarElement *planet2 = new SolarElement(orbitTranslationIncrement, 0, rotationIncrement, 1.0, rotationY, rotationZ, scaleX / 1.5, scaleY / 1.5, scaleZ / 1.5, translateX, translateY, translateZ, new Ellipse(3.5, 2.0), 45.0, 1.0, 0.0, 0.0, 2);
    planet2->appendChild(new SolarElement(orbitTranslationIncrement, 0, rotationIncrement, rotationX, rotationY, rotationZ, scaleX / 2, scaleY / 2, scaleZ / 2, translateX, translateY, translateZ, new Ellipse(2.0, 2.0), 0.0, 0.0, 0.0, 0.0, 0));
    planet2->appendChild(new SolarElement(orbitTranslationIncrement, PI/2, rotationIncrement, rotationX, rotationY, rotationZ, scaleX / 2, scaleY / 2, scaleZ / 2, translateX, translateY, translateZ, new Ellipse(2.0, 2.0), 0.0, 0.0, 0.0, 0.0, 0));

    SolarElement *planet3 = new SolarElement(0.02, 1.2, rotationIncrement, 1.0, rotationY, rotationZ, scaleX / 1.5, scaleY / 1.5, scaleZ / 1.5, translateX, translateY, translateZ, new Ellipse(4.0, 3.0), 75.0, 1.0, 0.0, 0.0, 3);
    planet3->appendChild(new SolarElement(orbitTranslationIncrement, 0, rotationIncrement, rotationX, rotationY, rotationZ, scaleX / 2, scaleY / 2, scaleZ / 2, translateX, translateY, translateZ, new Ellipse(2.0, 2.0), 0.0, 0.0, 0.0, 0.0, 0));
    planet3->appendChild(new SolarElement(orbitTranslationIncrement, PI/2, rotationIncrement, rotationX, rotationY, rotationZ, scaleX / 2, scaleY / 2, scaleZ / 2, translateX, translateY, translateZ, new Ellipse(2.0, 2.0), 0.0, 0.0, 0.0, 0.0, 0));
    planet3->appendChild(new SolarElement(orbitTranslationIncrement, PI/3, rotationIncrement, rotationX, rotationY, rotationZ, scaleX / 2, scaleY / 2, scaleZ / 2, translateX, translateY, translateZ, new Ellipse(2.0, 2.0), 0.0, 0.0, 0.0, 0.0, 0));

    SolarElement *planet4 = new SolarElement(0.02, 1.5, rotationIncrement, 1.0, rotationY, rotationZ, scaleX / 1.5, scaleY / 1.5, scaleZ / 1.5, translateX, translateY, translateZ, new Ellipse(5.0, 4.0), 120.0, 1.0, 0.0, 0.0, 1);
    planet4->appendChild(new SolarElement(orbitTranslationIncrement, 0, rotationIncrement, rotationX, rotationY, rotationZ, scaleX / 2, scaleY / 2, scaleZ / 2, translateX, translateY, translateZ, new Ellipse(2.0, 2.0), 0.0, 0.0, 0.0, 0.0, 0));
    planet4->appendChild(new SolarElement(orbitTranslationIncrement, PI/2, rotationIncrement, rotationX, rotationY, rotationZ, scaleX / 2, scaleY / 2, scaleZ / 2, translateX, translateY, translateZ, new Ellipse(2.0, 2.0), 0.0, 0.0, 0.0, 0.0, 0));
    planet4->appendChild(new SolarElement(orbitTranslationIncrement, PI/3, rotationIncrement, rotationX, rotationY, rotationZ, scaleX / 2, scaleY / 2, scaleZ / 2, translateX, translateY, translateZ, new Ellipse(2.0, 2.0), 0.0, 0.0, 0.0, 0.0, 0));
    planet4->appendChild(new SolarElement(orbitTranslationIncrement, PI/4, rotationIncrement, rotationX, rotationY, rotationZ, scaleX / 2, scaleY / 2, scaleZ / 2, translateX, translateY, translateZ, new Ellipse(2.0, 2.0), 0.0, 0.0, 0.0, 0.0, 0));

    sun->appendChild(planet1);
    sun->appendChild(planet2);
    sun->appendChild(planet3);
    sun->appendChild(planet4);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}

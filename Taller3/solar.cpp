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
  int color;

  Ellipse(float a, float b, int colour) {
    ar = a;
    br = b;
    color = colour;
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

void drawCube(int *colors) {
  glBegin(GL_QUADS);
	// top
	setHexColor(colors[0]);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	glEnd();

	glBegin(GL_QUADS);
	// front
	setHexColor(colors[1]);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);

	glEnd();

	glBegin(GL_QUADS);
	// right
	setHexColor(colors[2]);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);

	glEnd();

	glBegin(GL_QUADS);
	// left
	setHexColor(colors[3]);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);

	glEnd();

	glBegin(GL_QUADS);
	// bottom
	setHexColor(colors[4]);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);

	glEnd();

	glBegin(GL_QUADS);
	// back
	setHexColor(colors[5]);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	glEnd();
}

void drawPyramidSquareBase(int *colors) {
  glBegin(GL_TRIANGLES);

      setHexColor(colors[0]);
      glVertex3f( 0.0f, 1.0f, 0.0f);
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glVertex3f(1.0f, -1.0f, 1.0f);

      setHexColor(colors[1]);
      glVertex3f(0.0f, 1.0f, 0.0f);
      glVertex3f(1.0f, -1.0f, 1.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);

      setHexColor(colors[2]);
      glVertex3f(0.0f, 1.0f, 0.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);

      setHexColor(colors[3]);
      glVertex3f( 0.0f, 1.0f, 0.0f);
      glVertex3f(-1.0f,-1.0f,-1.0f);
      glVertex3f(-1.0f,-1.0f, 1.0f);
   glEnd();
}

// TODO - Translate to origin.
void tetrahedron(int *colors) {
  glBegin(GL_TRIANGLES);

      setHexColor(colors[0]);
      glVertex3f(0.0f, 0.0f, 1.0f);
      glVertex3f(0.0f, 0.0f, 0.0f);
      glVertex3f(1.0f, 0.0f, 0.5f);

      setHexColor(colors[1]);
      glVertex3f(0.0f, 0.0f, 1.0f);
      glVertex3f(0.0f, 0.0f, 0.0f);
      glVertex3f(0.5f, 1.0f, 0.5f);

      setHexColor(colors[2]);
      glVertex3f(0.0f, 0.0f, 0.0f);
      glVertex3f(1.0f, 0.0f, 0.5f);
      glVertex3f(0.5f, 1.0f, 0.5f);

      setHexColor(colors[3]);
      glVertex3f(0.0f, 0.0f, 1.0f);
      glVertex3f(1.0f, 0.0f, 0.5f);
      glVertex3f(0.5f, 1.0f, 0.5f);
   glEnd();
}

void octahedron(int *colors) {
  glBegin(GL_TRIANGLES);

      setHexColor(colors[0]);
      glVertex3f(0.0f, 0.5f, 0.0f);
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glVertex3f(1.0f, -1.0f, 1.0f);

      setHexColor(colors[1]);
      glVertex3f(0.0f, 0.5f, 0.0f);
      glVertex3f(1.0f, -1.0f, 1.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);

      setHexColor(colors[2]);
      glVertex3f(0.0f, 0.5f, 0.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);

      setHexColor(colors[3]);
      glVertex3f(0.0f, 0.5f, 0.0f);
      glVertex3f(-1.0f,-1.0f,-1.0f);
      glVertex3f(-1.0f,-1.0f, 1.0f);
   glEnd();
   glBegin(GL_TRIANGLES);

       setHexColor(colors[0]);
       glVertex3f(0.0f, -2.5f, 0.0f);
       glVertex3f(-1.0f, -1.0f, 1.0f);
       glVertex3f(1.0f, -1.0f, 1.0f);

       setHexColor(colors[1]);
       glVertex3f(0.0f, -2.5f, 0.0f);
       glVertex3f(1.0f, -1.0f, 1.0f);
       glVertex3f(1.0f, -1.0f, -1.0f);

       setHexColor(colors[2]);
       glVertex3f(0.0f, -2.5f, 0.0f);
       glVertex3f(1.0f, -1.0f, -1.0f);
       glVertex3f(-1.0f, -1.0f, -1.0f);

       setHexColor(colors[3]);
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
  int type, *colors;
  GLfloat currentScaleAngle, scaleIncrement, scaleFactor;

  SolarElement(GLfloat scaleIncrement, GLfloat scaleFactor, GLfloat orbitTranslationIncrement, GLfloat orbitCurrentAngle, GLfloat rotationIncrement, GLfloat rotationX, GLfloat rotationY, GLfloat rotationZ, GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ, GLfloat translateX, GLfloat translateY, GLfloat translateZ, Ellipse *orbit, GLfloat orbiteAngle, GLfloat orbitRotationX, GLfloat orbitRotationY, GLfloat orbitRotationZ, int type, int *colors) {
    this->rotationCurrentAngle = 0.0;
    this->currentScaleAngle = 0.0;
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
    this->scaleIncrement = scaleIncrement;
    this->scaleFactor = scaleFactor;
    this->type = type;
    this->colors = colors;
  }

  void actualTick(GLfloat delta) {
    this->rotationCurrentAngle += this->rotationIncrement;
    this->orbitCurrentAngle += this->orbitTranslationIncrement;
    this->currentScaleAngle += this->scaleIncrement;
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
      setHexColor(orbit->color);
      orbit->draw();
      Point p = orbit->getPoint(this->orbitCurrentAngle);
      glTranslatef(p.x, p.y, p.z);
    }
    glScalef(scaleX, scaleY, scaleZ);

    glPushMatrix();
    glRotatef(rotationCurrentAngle, rotationX, rotationY, rotationZ);

    float scaledFactor = scaleFactor + (sin(currentScaleAngle) / 2.0);
    glScalef(scaledFactor, scaledFactor, scaledFactor);

    glColor3f(1.0f, 1.0f, 1.0f);

    switch (type) {
      case 0:
        octahedron(colors);
      break;
      case 1:
        tetrahedron(colors);
      break;
      case 2:
        drawPyramidSquareBase(colors);
      break;
      case 3:
        drawCube(colors);
      break;
    }

    glPopMatrix();
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

GLint ancho=800;
GLint alto=800;

SolarElement *sun = NULL;

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

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    float eyeX = 0.0f, eyeY = 0.0f, eyeZ = -10.0f, centerX = 0.0f, centerY = 0.0f, centerZ = 0.0f, upX = 0.0f, upY = 1.0f, upZ = 0.0f;

    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

    if (sun != NULL) {
      sun->tick(0.1);
      sun->draw();
    }

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
    int sunColors[] = { 0xDBC309, 0xE5B10B, 0xCF8300, 0xE5740B, 0xDB4200, 0xE5420B  };
    sun = new SolarElement(0.01, 1.0, orbitTranslationIncrement, 0, rotationIncrement, rotationX, rotationY, rotationZ, scaleX, scaleY, scaleZ, translateX, translateY, translateZ, NULL, 0.0, 0.0, 0.0, 0.0, 3, sunColors);

    int planet1Colors[] = { 0x0B62E5, 0x0919DB, 0x0095CF, 0x0BE5DC, 0x0BE5DC, 0x14DB46  };
    SolarElement *planet1 = new SolarElement(0.0, 1.0, orbitTranslationIncrement, 1.5, rotationIncrement, rotationX, rotationY, rotationZ, scaleX / 2, scaleY / 2, scaleZ / 2, translateX, translateY, translateZ, new Ellipse(1.5, 2.0, planet1Colors[0]), 90.0, 0.0, 0.0, 1.0, 1, planet1Colors);

    int planet2Colors[] = { 0x0FDB61, 0x05E512, 0x4ECF05, 0xB6E505, 0xDBCE06, 0xDBB011  };
    int planet2Moon1Colors[] = { 0xDB7E8D, 0xE56FCA, 0xBA6ECF, 0xA56FE5, 0x8175DB, 0x93A0DB  };
    SolarElement *planet2 = new SolarElement(0.0, 1.0, orbitTranslationIncrement, 0, rotationIncrement, 1.0, rotationY, rotationZ, scaleX / 1.5, scaleY / 1.5, scaleZ / 1.5, translateX, translateY, translateZ, new Ellipse(3.5, 2.0, planet2Colors[0]), 45.0, 1.0, 0.0, 0.0, 2, planet2Colors);
    planet2->appendChild(new SolarElement(0.0, 1.0, orbitTranslationIncrement, PI/2, rotationIncrement, rotationX, rotationY, rotationZ, scaleX / 2, scaleY / 2, scaleZ / 2, translateX, translateY, translateZ, new Ellipse(2.0, 2.0, planet2Moon1Colors[0]), 0.0, 0.0, 0.0, 0.0, 0, planet2Moon1Colors));

    int planet3Colors[] = { 0xDB540B, 0xE5450B, 0xCF2500, 0xE5200B, 0xDB4200, 0xDB0200  };
    int planet3Moon1Colors[] = { 0xDBB87E, 0xE5B06D, 0xCF9A6D, 0xE59B6D, 0xDB9273, 0xDB8173  };
    SolarElement *planet3 = new SolarElement(0.0, 1.0, 0.02, 1.2, rotationIncrement, 1.0, rotationY, rotationZ, scaleX / 1.5, scaleY / 1.5, scaleZ / 1.5, translateX, translateY, translateZ, new Ellipse(4.0, 3.0, planet3Colors[0]), 75.0, 1.0, 0.0, 0.0, 3, planet3Colors);
    planet3->appendChild(new SolarElement(0.0, 1.0, 0.03, PI/2, rotationIncrement, rotationX, rotationY, rotationZ, scaleX / 2, scaleY / 2, scaleZ / 2, translateX, translateY, translateZ, new Ellipse(2.0, 2.0, planet3Moon1Colors[0]), 0.0, 0.0, 0.0, 0.0, 0, planet3Moon1Colors));

    int planet4Colors[] = { 0x827127, 0xFFE77F, 0xCFB852, 0x1A1B82, 0x5253CF, 0x5778CF  };
    int planet4Moon1Colors[] = { 0x824C22, 0xFFB175, 0x157582, 0x4ABFCF, 0xCF844A, 0x58CFCB  };
    int planet4Moon2Colors[] = { 0xA6DBB5, 0x9CE597, 0xAECF93, 0xDAE596, 0xDBD79C, 0xDBC395  };
    SolarElement *planet4 = new SolarElement(0.0, 1.0, 0.02, 1.5, rotationIncrement, 1.0, rotationY, rotationZ, scaleX / 1.5, scaleY / 1.5, scaleZ / 1.5, translateX, translateY, translateZ, new Ellipse(5.0, 4.0, planet4Colors[0]), 120.0, 1.0, 0.0, 0.0, 0, planet4Colors);
    planet4->appendChild(new SolarElement(0.0, 1.0, orbitTranslationIncrement, 0, rotationIncrement, rotationX, rotationY, rotationZ, scaleX / 2, scaleY / 2, scaleZ / 2, translateX, translateY, translateZ, new Ellipse(2.0, 2.0, planet4Moon1Colors[0]), 0.0, 0.0, 0.0, 0.0, 3, planet4Moon1Colors));
    planet4->appendChild(new SolarElement(0.0, 1.0, orbitTranslationIncrement, PI/2, rotationIncrement, rotationX, rotationY, rotationZ, scaleX / 2, scaleY / 2, scaleZ / 2, translateX, translateY, translateZ, new Ellipse(2.0, 2.0, planet4Moon2Colors[0]), 90.0, 0.0, 1.0, 0.0, 1, planet4Moon2Colors));

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

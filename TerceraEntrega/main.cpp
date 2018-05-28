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
#include <map>
#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>

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

struct Camera {
  float eyeX = 0.0f, eyeY = 0.0f, eyeZ = -10.0f, centerX = 0.0f, centerY = 0.0f, centerZ = 0.0f, upX = 0.0f, upY = 1.0f, upZ = 0.0f;

  Camera() {

  }

  Camera(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ) {
    this->eyeX = eyeX;
    this->eyeY = eyeY;
    this->eyeZ = eyeZ;
    this->centerX = centerX;
    this->centerY = centerY;
    this->centerZ = centerZ;
    this->upX = upX;
    this->upZ = upZ;
    this->upZ = upZ;
  }

  void draw() {
    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
  }
};

struct Walker {
  float currentX, currentY, currentZ;



  Walker(float currentX, float currentY, float currentZ) {
    this->currentX = currentX;
    this->currentY = currentY;
    this->currentZ = currentY;
  }

  void draw() {
    glPushMatrix();

    glTranslatef(this->currentX, this->currentY, this->currentZ);
    glColor3f(1.0, 1.0, 1.0);
    glutWireTeapot(0.1);

    glPopMatrix();

  }

};

struct GaitEngine {
  string fileName;
  //vector<Camera*> cameras;
  Camera *currentCamera = NULL;
  map<string, vector<Point>> coords;
  Walker *walker = NULL;

  GaitEngine(string fileName) {
    this->fileName = fileName;
    this->currentCamera = new Camera();
    //this->cameras.push_back(this->currentCamera);
    this->loadFile();
    walker = new Walker(0.0, 0.0, 0.0);
  }

  void loadFile() {
    ifstream fileStream(fileName);
    string line;

    coords.clear();

    if (fileStream.is_open()) {
      float x, y, z;
      string currentKey = "";
      while(getline(fileStream, line)) {
        if (isalpha(line[0])) {
          currentKey = line;
        } else {
          stringstream ss(line);
           ss >> x;
           ss >> y;
           ss >> z;
           coords[currentKey].push_back(Point(x, y, z));
        }
        //cout << line << endl;
      }
    }
  }

  void tick(GLfloat delta) {

  }

  void draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (currentCamera != NULL) {
      currentCamera->draw();
    }

    if (walker != NULL) {
      walker->draw();
    }


    glutSwapBuffers();
  }

};


GLint ancho=800;
GLint alto=800;

GaitEngine *gaitEngine = NULL;

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
  if (gaitEngine != NULL) {
    gaitEngine->tick(0.1);
    gaitEngine->draw();
  }
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

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glEnable(GL_DEPTH_TEST);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(ancho, alto);
  glutCreateWindow("Gait lab");
  init();

  gaitEngine = new GaitEngine("data.txt");

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}

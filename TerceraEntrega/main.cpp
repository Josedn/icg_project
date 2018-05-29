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

float minX = 0.0, minY = 0.0, minZ = 0.0;
float maxX = 15.0, maxY = 7.0, maxZ = 15.0;

float wx = (maxX - minX) / 5.0, wy = (maxY - minY) / 2.0, wz = (maxZ - minZ) / 2.0;

struct Point {
  float x, y, z;

  Point() {
    x = 0;
    y = 0;
    z = 0;
  }

  Point(float _x, float _y, float _z) {
    x = _x;
    y = _y;
    z = _z;
  }

  void print() {
    std::cout << "x: " << x << " y: " << y << " z: " << z << std::endl;
  }

  float distanceTo(Point p) {
    return sqrt(abs(p.x - this->x) * abs(p.x - this->x) + abs(p.y - this->y) * abs(p.y - this->y) + abs(p.z - this->z) * abs(p.z - this->z));
  }
};

void setHexColor(int color) {
  float r = ((0xFF0000 & color) >> 16) / 255.0;
  float g = ((0x00FF00 & color) >> 8) / 255.0;
  float b = (0x0000FF & color) / 255.0;
  glColor3f(r, g, b);
}

void drawPoint(Point p, float size) {
  glPushMatrix();
    glTranslatef(p.x, p.y, p.z);
    //p.print();
    glutSolidSphere(size, 60, 60);
  glPopMatrix();
}

void drawLine(Point p, Point q, float h, float w) {
  glPushMatrix();

    float distance = p.distanceTo(q);
    float distanceX = q.x - p.x;
    float distanceY = q.y - p.y;
    float distanceZ = q.z - p.z;
    float angleYX = atan(distanceY / distanceX) * 180.0 / PI;
    float angleZX = atan(distanceZ / distanceX) * 180.0 / PI;

    Point center((q.x + p.x) / 2, (q.y + p.y) / 2, (q.z + p.z) / 2);
    glTranslatef(center.x, center.y, center.z);
    glRotatef(angleYX, 0.0, 0.0, 1.0);
    glRotatef(angleZX, 0.0, -1.0, 0.0);
    glScalef(distance, h, w);

    glutSolidCube(1);
  glPopMatrix();
}

/**
  *
  * Draws the floor of the scene by making a prism
  * with a carpet of another color.
  *
  */
void drawFloor() {
  glBegin(GL_QUADS);
  glVertex3f(minX, minY, maxZ);			// Top Right Of The Quad (Left)
  glVertex3f(maxX, minY, maxZ);			// Top Left Of The Quad (Left)
  glVertex3f(maxX, minY, 0.0f);			// Top Left Of The Quad (Left)
  glVertex3f(minX, minY, 0.0f);			// Top Left Of The Quad (Left)
  glEnd();

}

void drawLeftWall() {
  glBegin(GL_QUADS);
  glVertex3f(minX, maxY, minZ);			// Top Right Of The Quad (Left)
  glVertex3f(minX, maxY, maxZ);			// Top Left Of The Quad (Left)
  glVertex3f(minX, minY, maxZ);			// Top Left Of The Quad (Left)
  glVertex3f(minX, minY, minZ);			// Top Left Of The Quad (Left)
  glEnd();
}

void drawBackWall() {
  glBegin(GL_QUADS);
  glVertex3f(minX, maxY, minZ);			// Top Right Of The Quad (Left)
  glVertex3f(maxX, maxY, minZ);			// Top Left Of The Quad (Left)
  glVertex3f(maxX, minY, minZ);			// Top Left Of The Quad (Left)
  glVertex3f(minX, minY, minZ);			// Top Left Of The Quad (Left)
  glEnd();
}

void drawCarpet() {
  glPushMatrix();
  glTranslatef(0, 0, (maxZ - minZ)/3.0);
  glScalef(1.0, 1.0, 1.0/3.0);
  drawFloor();
  glPopMatrix();
}

void showImportantPoints() {
  glColor3f(1.0f, 0.0f, 0.0f); // #FF0000
  glPushMatrix();
  glTranslatef(maxX, maxY, minZ);
  glutWireCube(0.5);
  glPopMatrix();

  glColor3f(0.0f, 1.0f, 0.0f); // #00FF00
  glPushMatrix();
  glTranslatef(minX, maxY, minZ);
  glutWireCube(0.5);
  glPopMatrix();

  glColor3f(0.0f, 0.0f, 1.0f); // #0000FF
  glPushMatrix();
  glTranslatef(minX, maxY, maxZ);
  glutWireCube(0.5);
  glPopMatrix();

  glColor3f(1.0f, 1.0f, 0.0f); // #FFFF00
  glPushMatrix();
  glTranslatef(minX, minY, maxZ);
  glutWireCube(0.5);
  glPopMatrix();

  glColor3f(1.0f, 1.0f, 1.0f); // #FFFFFF
  glPushMatrix();
  glTranslatef(minX, minY, minZ);
  glutWireCube(0.5);
  glPopMatrix();


  glColor3f(0.0f, 1.0f, 1.0f); // #00FFFF
  glPushMatrix();
  glTranslatef(maxX, minY, minZ);
  glutWireCube(0.5);
  glPopMatrix();


  glColor3f(1.0f, 0.0f, 1.0f); // // #FF00FF
  glPushMatrix();
  glTranslatef(maxX, minY, maxZ);
  glutWireCube(0.5);
  glPopMatrix();

}

void pyramid()
{
  glBegin( GL_TRIANGLES );
  glVertex3f( 0.0f, 1.f, 0.0f );
  glVertex3f( -1.0f, -1.0f, 1.0f );
  glVertex3f( 1.0f, -1.0f, 1.0f);

  glVertex3f( 0.0f, 1.0f, 0.0f);
  glVertex3f( -1.0f, -1.0f, 1.0f);
  glVertex3f( 0.0f, -1.0f, -1.0f);

  glVertex3f( 0.0f, 1.0f, 0.0f);
  glVertex3f( 0.0f, -1.0f, -1.0f);
  glVertex3f( 1.0f, -1.0f, 1.0f);

  glVertex3f( -1.0f, -1.0f, 1.0f);
  glVertex3f( 0.0f, -1.0f, -1.0f);
  glVertex3f( 1.0f, -1.0f, 1.0f);
  glEnd();
}

void drawWoody() {
  float wx = 0.0;
  //float wy = 1.0;
  float wz = 0.0;
  //Head
  setHexColor(0xc99c9c);
  glPushMatrix();
  glTranslatef(wx, wy, wz);
  glutSolidSphere(0.5, 100, 100);
  glPopMatrix();

  //Hat
  setHexColor(0x822816);
  glPushMatrix();
  glTranslatef(wx, wy*1.1, wz);
  glRotatef(90, 1.0, 0, 0);
  GLUquadricObj *disk1 = gluNewQuadric();
  gluQuadricDrawStyle (disk1, GLU_FILL);
  gluDisk (disk1, 0.3, 0.8, 40, 40);
  glPopMatrix();
  //Hat
  setHexColor(0x822816);
  glPushMatrix();
  glTranslatef(wx, wy*1.2, wz);
  glRotatef(90, 1.0, 0, 0);
  GLUquadricObj *cyl1 = gluNewQuadric();
  gluQuadricDrawStyle (disk1, GLU_FILL);
  gluCylinder (cyl1, 0.3, 0.6, 0.4, 20, 20);
  glPopMatrix();

  //Neck
  setHexColor(0xc99c9c);
  glPushMatrix();
  glTranslatef(wx, wy/1.2, wz);
  glScalef(1.0/4.0, 1.0, 1.0/4.0);
  glutSolidSphere(0.5, 100, 100);
  glPopMatrix();

  // Hip
  setHexColor(0x1f3480);
  glPushMatrix();
  glTranslatef(wx, wy/2, wz);
  glScalef(1.0/10.0, 1.0/2.0, 1.0);
  glutSolidCube(0.8);
  glPopMatrix();

  //Top
  setHexColor(0x9e6315);
  glPushMatrix();
  glTranslatef(wx, wy/1.5, wz);
  glScalef(1.0/7.0, 1.1, 1.0);
  glutSolidCube(1);
  glPopMatrix();

  // Left Arm
  setHexColor(0x9e6315);
  glPushMatrix();
  glTranslatef(wx, wy/1.36, wz*1.09);
  glRotatef(45.0, 1.0, 0.0, 0.0);
  glScalef(1.0/10.0, 1.0/6.0, 0.7);
  glutSolidCube(1);
  glPopMatrix();

  // Left Arm
  setHexColor(0x9e6315);
  glPushMatrix();
  glTranslatef(wx, wy/1.62, wz*1.12);
  glScalef(1.0/10.0, 0.45, 1.0/6.0);
  glutSolidCube(1);
  glPopMatrix();

  // Left hand
  setHexColor(0xc99c9c);
  glPushMatrix();
  glTranslatef(wx, wy/1.75, wz*1.12);
  glutSolidSphere(0.1, 100, 100);
  glPopMatrix();

  // Right Arm
  setHexColor(0x9e6315);
  glPushMatrix();
  glTranslatef(wx, wy/1.36, wz/1.09);
  glRotatef(-45.0, 1.0, 0.0, 0.0);
  glScalef(1.0/10.0, 1.0/6.0, 0.7);
  glutSolidCube(1);
  glPopMatrix();

  // Right Arm
  setHexColor(0x9e6315);
  glPushMatrix();
  glTranslatef(wx, wy/1.62, wz/1.12);
  glScalef(1.0/10.0, 0.45, 1.0/6.0);
  glutSolidCube(1);
  glPopMatrix();

  // Right Hand
  setHexColor(0xc99c9c);
  glPushMatrix();
  glTranslatef(wx, wy/1.75, wz/1.12);
  glutSolidSphere(0.1, 100, 100);
  glPopMatrix();

}

struct Camera {
  float eyeX = (maxX - minX)/2.0, eyeY = 8.0f, eyeZ = 25.0f, centerX = (maxX - minX)/2.0, centerY = 0.0f, centerZ = 0.0f, upX = 0.0f, upY = 1.0f, upZ = 0.0f;

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

  void setCenter(float x, float y, float z) {
    this->centerX = x;
    this->centerY = y;
    this->centerZ = z;
  }

  void draw() {
    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
  }
};

struct Person {
  map<string, Point> bones;

  Person() {

  }

  void setBone(string id, Point p) {
    bones[id] = p;
  }

  void drawConnection(string first, string second) {
    glPushMatrix();
      drawLine(bones[first], bones[second], 0.3, 0.3);

    glPopMatrix();
  }

  void draw() {
    glPushMatrix();

    setHexColor(0x1f3480);
    drawConnection("SACR", "RASI");
    drawConnection("SACR", "LASI");

    setHexColor(0x1f3480);
    drawConnection("RASI", "RTHI");
    drawConnection("RTHI", "RKNE");
    drawConnection("RKNE", "RTIB");
    drawConnection("RTIB", "RANK");

    setHexColor(0x926226);
    drawConnection("RANK", "RTOE");

    setHexColor(0x1f3480);
    drawConnection("LASI", "LTHI");
    drawConnection("LTHI", "LKNE");
    drawConnection("LKNE", "LTIB");
    drawConnection("LTIB", "LANK");

    setHexColor(0x926226);
    drawConnection("LANK", "LTOE");

    setHexColor(0xFFFF00);
    map<string, Point>::iterator it;
    for (it = bones.begin(); it != bones.end(); ++it) {
      Point p = it->second;
      glPushMatrix();
      drawPoint(p, 0.05);
      //glTranslatef(p.x, p.y, p.z);

      glPopMatrix();
    }

    glPopMatrix();
  }
};

struct GaitEngine {
  string fileName;
  //vector<Camera*> cameras;
  Person *person = NULL;
  Camera *currentCamera = NULL;
  map<string, vector<Point>> coords;

  int maxFrames;
  int currentFrame;
  float rotationX, rotationY, rotationZ, aux = 0;

  GaitEngine(string fileName) {
    this->fileName = fileName;
    this->currentCamera = new Camera();
    //this->cameras.push_back(this->currentCamera);
    this->loadFile();
    this->rotationX = 0;
    this->rotationY = 0;
    this->rotationZ = 0;
    this->currentFrame = 0;
    this->maxFrames = coords[coords.begin()->first].size();
    this->person = new Person();
    map<string, vector<Point>>::iterator it;
    for (it = coords.begin(); it != coords.end(); ++it) {
      this->person->setBone(it->first, Point());
    }
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
          //cout << "Key: " << currentKey << endl;
        } else {
          stringstream ss(line);
           ss >> x;
           ss >> y;
           ss >> z;
           //coords[currentKey].push_back(Point(y / 500, z / 500, x / 500));
           coords[currentKey].push_back(Point(x / 500, y / 500, z / 500));
        }
        //cout << line << endl;
      }
    }
  }

  void tick(GLfloat delta) {

    map<string, vector<Point>>::iterator it;

    for(it = coords.begin(); it != coords.end(); ++it) {
      Point p = coords[it->first][this->currentFrame];
      if (p.x == 0 && p.y == 0 && p.z == 0) {
        this->currentFrame = 0;
      }
      this->person->setBone(it->first, p);
    }

    this->currentCamera->setCenter(this->person->bones["SACR"].x, this->person->bones["SACR"].y, this->person->bones["SACR"].z);

    if (this->currentFrame >= this->maxFrames) {
      this->currentFrame = 0;
    }
    this->currentFrame++;
  }

  void draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (currentCamera != NULL) {
      currentCamera->draw();
    }


    glRotatef(rotationX, 1, 0, 0);
    glRotatef(rotationY, 0, 1, 0);
    glRotatef(rotationZ, 0, 0, 1);

    showImportantPoints();
    setHexColor(0xFFFFFF);
    drawBackWall();

    setHexColor(0x888888);
    drawFloor();

    setHexColor(0xaf2727);
    drawCarpet();

    setHexColor(0xEEEEEE);
    drawLeftWall();

    glPushMatrix();
      glTranslatef(person->bones["SACR"].x + 0.25, 0.5, person->bones["SACR"].z + 5.0);
      drawWoody();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 8.0);

    glRotatef(-90, 1, 0, 0);
    if (person != NULL) {
      person->draw();
    }

    glPopMatrix();

    /*
    map<string, Bone*>::iterator it;drawLeg
    for(it = walkers.begin(); it != walkers.end(); ++it) {
      it->second->draw();
    }*/

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

    gluPerspective(60.0f, (GLfloat)width/(GLfloat)height, 1.0f, 500.0f);

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

void idle() {
    display();
}

void onKeyPress(unsigned char key, int x, int y) {
  if (gaitEngine != NULL) {
    switch (key) {
      case 'w':
      gaitEngine->rotationX += 1.0;
      // cout << "RotationX: " << gaitEngine->rotationX << endl;
      break;
      case 'a':
      gaitEngine->rotationY -= 1.0;
      // cout << "RotationY: " << gaitEngine->rotationY << endl;
      break;
      case 's':
      gaitEngine->rotationX -= 1.0;
      // cout << "RotationX: " << gaitEngine->rotationX << endl;
      break;
      case 'd':
      gaitEngine->rotationY += 1.0;
      // cout << "RotationY: " << gaitEngine->rotationY << endl;
      break;
      case 'q':
      gaitEngine->rotationZ -= 1.0;
      // cout << "RotationZ: " << gaitEngine->rotationZ << endl;
      break;
      case 'e':
      gaitEngine->rotationZ += 1.0;
      // cout << "RotationZ: " << gaitEngine->rotationZ << endl;
      break;


      case 'l':
      gaitEngine->currentCamera->eyeX -= 1.0;
      // cout << "EyeX: " << gaitEngine->currentCamera->eyeX << endl;
      break;

      case 'k':
      gaitEngine->currentCamera->eyeZ += 1.0;
      // cout << "EyeZ: " << gaitEngine->currentCamera->eyeZ << endl;
      break;
      case 'j':
      gaitEngine->currentCamera->eyeX += 1.0;
      // cout << "EyeX: " << gaitEngine->currentCamera->eyeX << endl;
      break;
      case 'i':
      gaitEngine->currentCamera->eyeZ -= 1.0;
      // cout << "EyeZ: " << gaitEngine->currentCamera->eyeZ << endl;
      break;

      case 'z':
      wx += 0.1;
      break;
      case 'x':
      wx -= 0.1;
      break;
    }
  }
}

int main(int argc, char **argv) {
  cout << "Controles: " << endl << endl;
  cout << "- W............... Rotar en +X" << endl;
  cout << "- S............... Rotar en -X" << endl;
  cout << "- A............... Rotar en -Y" << endl;
  cout << "- D............... Rotar en +Y" << endl;
  cout << "- Q............... Rotar en -Z" << endl;
  cout << "- E............... Rotar en +Z" << endl;
  cout << "- I............... Mover camara en -Z" << endl;
  cout << "- K............... Mover camara en +Z" << endl;
  cout << "- J............... Mover camara en +X" << endl;
  cout << "- L............... Mover camara en -X" << endl;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glEnable(GL_DEPTH_TEST);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(ancho, alto);
  glutCreateWindow("Gait lab");
  init();

  gaitEngine = new GaitEngine("data.txt");

  glutDisplayFunc(display);
  glutKeyboardFunc(onKeyPress);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}

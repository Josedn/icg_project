//  introOpenGl.cpp
//  Creado por Andrea Rueda, 01/2018
//

#include <GL/freeglut.h>
// Added this lines for the program to compile on linux and Mac
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include <iostream>

using namespace std;

const int WIDTH = 408;
const int HEIGHT = 640;

void myInit (void) {
  glClearColor(1.0,1.0,1.0,1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 640, 0, 480);
}

void drawLine(int x0, int y0, int xf, int yf ) {
  glBegin(GL_LINES);
  glVertex2i(x0, y0);
  glVertex2i(xf, yf);
  glEnd();
}

void drawPoint(int x, int y) {
  glBegin(GL_POINTS);
  glVertex2i(x,y);
  glEnd();
}

void drawCircle(int xc, int yc, int r) {
  double xk = 0.0;
  double yk = (double)r;
  double pk = (5.0/4.0) - (double)r;
  while(xk <= yk) {
    if(pk < 0.0) {
      xk += 1.0;
      pk = pk + 2.0*xk + 1.0;
    } else {
      xk += 1.0;
      yk -= 1.0;
      pk = pk + 2.0*xk + 1.0 - 2.0*yk;
    }
    drawPoint(xk + xc, yk + yc);
    drawPoint(xk + xc, -yk + yc);
    drawPoint(yk + xc, -xk + yc);
    drawPoint(-yk + xc, -xk + yc);
    drawPoint(-xk + xc, -yk + yc);
    drawPoint(-xk + xc, yk + yc);
    drawPoint(-yk + xc, xk + yc);
    drawPoint(yk + xc, xk + yc);
  }
}

void drawFilledCircle(int xc, int yc, int r) {
  double xk = 0.0;
  double yk = (double)r;
  double pk = (5.0/4.0) - (double)r;
  while(xk <= yk) {
    if(pk < 0.0) {
      xk += 1.0;
      pk = pk + 2.0*xk + 1.0;
    } else {
      xk += 1.0;
      yk -= 1.0;
      pk = pk + 2.0*xk + 1.0 - 2.0*yk;
    }
    drawLine(xc, yc, xk + xc, yk + yc);
    drawLine(xc, yc, xk + xc, -yk + yc);
    drawLine(xc, yc, yk + xc, -xk + yc);
    drawLine(xc, yc, -yk + xc, -xk + yc);
    drawLine(xc, yc, -xk + xc, -yk + yc);
    drawLine(xc, yc, -xk + xc, yk + yc);
    drawLine(xc, yc, -yk + xc, xk + yc);
    drawLine(xc, yc, yk + xc, xk + yc);
  }
}

double feli(double x, double y, double rx, double ry) {
  return ry*ry*x*x+rx*rx*y*y-rx*rx*ry*ry;
}

void drawEllipse(double xc, double yc, double xr, double yr) {
  double xk = 0.0, yk = (double) yr;
  double pk1 = feli(1.0, (double)yr - 0.5, (double)xr, (double)yr);
  while(2.0*(double)yr*(double)yr*xk <= 2.0*(double)xr*(double)xr*yk) {
    xk += 1.0;
    if(pk1 < 0) {
      pk1 = pk1 + 2.0*yr*yr*xk+yr*yr;
    } else {
      pk1 = pk1 + 2.0*yr*yr*xk+yr*yr - 2.0*xr*xr*yk;
      yk -= 1;
    }
    //yk -= (pk1 < 0 ? 0.0 : 1.0);
    drawPoint(xk + xc, yk + yc);
    drawPoint(-xk + xc, -yk + yc);
    drawPoint(-xk + xc, yk + yc);
    drawPoint(xk + xc, -yk + yc);
  }

  // while(2.0*(double)yr*(double)yr*xk > 2.0*(double)xr*(double)xr*yk) {
  //
  // }
}

void drawRect(int x0, int y0, int xf, int yf) {
  glBegin(GL_POLYGON);
  glRecti(x0, y0, xf, yf);
  glEnd();
}

void leftBoot() {
  glBegin (GL_POLYGON);
  glVertex2i(185, 50);
  glVertex2i(185, 30);
  glVertex2i(120, 30);
  glVertex2i(145, 50);
  glEnd();
}

void rightBoot() {
  glBegin (GL_POLYGON);
  glVertex2i(215, 50);
  glVertex2i(215, 30);
  glVertex2i(280, 30);
  glVertex2i(255, 50);
  glEnd();
}

void woodyLowerHalf() {
  // WIDTH = 408; HEIGHT = 640;
  int midHeight = HEIGHT / 2;
  // drawLine(0, midHeight, WIDTH, midHeight); // Weist Line TODO - Delete

  glColor3f(0.0, 1.0, 0.0);
  glPointSize(4.0);
  // drawLine(140, midHeight, 260, midHeight);
  glColor3f(0.07, 0.21, 0.45); // #113572
  glRecti(150, midHeight, 250, midHeight - 5);
  glColor3f(0.55, 0.27, 0.075); // #8B4513
  glRecti(150, midHeight - 5, 250, midHeight - 25);
  glColor3f(0.85, 0.65, 0.13); // #DAA520
  glPointSize(3.0);
  drawFilledCircle(200, midHeight - 15, 10);
  // TODO - Draw a half ellipse for the hips
  glColor3f(0.07, 0.21, 0.45); // #113572
  glRecti(150, midHeight - 25, 250, midHeight - 50);

  /* Start Left Leg */
  glColor3f(0.07, 0.21, 0.45); // #113572
  glRecti(150, midHeight - 25, 180, 160);
  glColor3f(0.24, 0.44, 0.52); // #3d6f84
  glRecti(150, 160, 180, 165);
  glColor3f(0.07, 0.21, 0.45); // #113572
  glRecti(150, 160, 180, 100);
  glColor3f(0.55, 0.27, 0.075); // #8B4513
  glRecti(145, 100, 185, 50);
  leftBoot();
  /* End Left Leg */

  /* Start Rigth Leg */
  glColor3f(0.07, 0.21, 0.45); // #113572
  glRecti(220, midHeight - 25, 250, 160);
  glColor3f(0.24, 0.44, 0.52); // #3d6f84
  glRecti(220, 160, 250, 165);
  glColor3f(0.07, 0.21, 0.45); // #113572
  glRecti(220, 160, 250, 100);
  glColor3f(0.55, 0.27, 0.075); // #8B4513
  glRecti(215, 100, 255, 50);
  rightBoot();
  /* End Right Leg */

}

void setHexColor(int color) {
  float r = ((0xFF0000 & color) >> 16) / 255.0;
  float g = ((0x00FF00 & color) >> 8) / 255.0;
  float b = (0x0000FF & color) / 255.0;
  glColor3f(r, g, b);
}

void rightArm(int x, int y) {
  glBegin (GL_POLYGON);
  glVertex2i(x + 150, y + 150);
  glVertex2i(x + 200, y + 150);
  glVertex2i(x + 200, y + 200);
  glEnd();
}

void woodyUpperHalf() {
  int midHeight = HEIGHT / 2;

  //Top
  setHexColor(0xE8AA0C);
  glRecti(150, midHeight, 250, midHeight + 120);

  //Vest
  setHexColor(0xBBBBBB);
  glRecti(150, midHeight + 20, 150 + 40, midHeight + 100 - 15);
  glRecti(250, midHeight + 20, 250 - 40, midHeight + 100 - 15);

  glRecti(150 + 5, midHeight + 100 - 15, 250 - 5, midHeight + 100 + 20);
  //glRecti(250, midHeight + 20, 250 - 40, midHeight + 100 - 15);


  //Arms
  setHexColor(0xE8AA0C);
  glRecti(150, midHeight + 120, 150 - 120, midHeight + 120 - 30);
  glRecti(250, midHeight + 120, 250 + 120, midHeight + 120 - 30);

  //'Hands'
  setHexColor(0xFFD3B6);
  drawFilledCircle(150 - 120, midHeight + 120 - 30 + 15, 15);
  drawFilledCircle(250 + 120, midHeight + 120 - 30 + 15, 15);

  //Neck : Red thing
  setHexColor(0xAA0000);
  glRecti(180 - 5, midHeight + 100 - 15, 220 + 5, midHeight + 120);
  //Neck
  setHexColor(0xFFD3B6);
  glRecti(180, midHeight + 100, 220, midHeight + 140);

  //Face
  glRecti(150 + 10, midHeight + 140, 250 - 10, midHeight + 240);

  //Eyes
  setHexColor(0xffffff);
  drawFilledCircle(250 - 10 - 20, midHeight + 240 - 40, 13);
  drawFilledCircle(150 + 10 + 20, midHeight + 240 - 40, 13);
  setHexColor(0);
  drawFilledCircle(250 - 10 - 20, midHeight + 240 - 40, 5);
  drawFilledCircle(150 + 10 + 20, midHeight + 240 - 40, 5);

  //Hair
  setHexColor(0x542800);
  glRecti(150 + 10, midHeight + 220, 250 - 10, midHeight + 240);

  //Hat
  setHexColor(0xB87309);
  glRecti(150 - 20, midHeight + 230, 250 + 20, midHeight + 240);
  glRecti(150 + 10, midHeight + 240, 250 - 10, midHeight + 270);
}

void myDisplay (void) {

  glClear(GL_COLOR_BUFFER_BIT);
  glPointSize(2.0);
  glColor3f(1.0, 0.0, 0.0);
  // Start Drwawing
  woodyLowerHalf();
  woodyUpperHalf();
  // End Drwawing

  glFrontFace(GL_CW);
  glFlush();

}


void myResize (int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, w, 0, h);
}


int main (int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Graphics Window");
  glutDisplayFunc(myDisplay);
  glutReshapeFunc(myResize);
  myInit();
  glutMainLoop();
  return 0;
}

//  introOpenGl.cpp
//  Creado por Andrea Rueda, 01/2018
//

#define PI 3.14159265358979323846

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
#include <cmath>

using namespace std;

const int WIDTH = 500;
const int HEIGHT = 500;

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
  //glRecti(x0, y0, xf, yf);
  glVertex2i (x0,y0);
  glVertex2i (x0,yf);
  glVertex2i (xf,yf);
  glVertex2i (xf,y0);
  glEnd();
}

void setHexColor(int color) {
  float r = ((0xFF0000 & color) >> 16) / 255.0;
  float g = ((0x00FF00 & color) >> 8) / 255.0;
  float b = (0x0000FF & color) / 255.0;
  glColor3f(r, g, b);
}

void drawPolygonCircle(int x, int y, int r) {
  glBegin (GL_POLYGON);
  for(double i = 0.0; i <= 360.0; i+=0.1) {
    double angle = (i*PI)/180.0;
    int xi = r*cos(angle) + x;
    int yi = r*sin(angle) + y;
    glVertex2i (xi,yi);
  }
  glEnd ();
}

void drawStar() {
  glBegin (GL_POLYGON);
  glVertex2i (250,480);
  glVertex2i (480,250);
  glVertex2i (20,250);
  glEnd ();
  glBegin (GL_POLYGON);
  glVertex2i (20,250);
  glVertex2i (480,250);
  glVertex2i (250,20);
  glEnd ();
  drawRect(85,410,415,90);
}

void drawSmallStar() {
  setHexColor(0x0DFF7C);
  drawRect(193,306,306,193);
  setHexColor(0xE8DE3B);
  glBegin (GL_POLYGON);
  glVertex2i (250,330);
  glVertex2i (330,250);
  glVertex2i (170,250);
  glEnd ();
  glBegin (GL_POLYGON);
  glVertex2i (170,250);
  glVertex2i (330,250);
  glVertex2i (250,170);
  glEnd ();
}

void drawFlower(int r, int p, int xc, int yc) {
  //glBegin (GL_POLYGON);
  for(double i = 0.0; i <= 360.0; i+=0.1) {
    double angle = (i*PI)/180.0;
    int rad = r*cos(p * angle) + r;
    int xi = rad*cos(angle) + xc;
    int yi = rad*sin(angle) + yc;
    //glVertex2i (xi,yi);
    // drawPoint(xi, yi);
    drawLine(xc,yc,xi,yi);
  }
  //glEnd ();
}

void myDisplay (void) {

  glClear(GL_COLOR_BUFFER_BIT);
  glPointSize(2.0);
  glColor3f(1.0, 0.0, 0.0);
  // Start Drwawing

  setHexColor(0x0CFF25);
  drawPolygonCircle(250,250, 240);
  setHexColor(0xE8B20C);
  drawPolygonCircle(250,250, 230);
  setHexColor(0xFF0000);
  drawRect(170,465,330,35);
  setHexColor(0xFF0000);
  drawRect(465,170,35,330);
  setHexColor(0x0C0DE8);
  drawStar();
  setHexColor(0x596BFF);
  drawPolygonCircle(250,250, 175);
  setHexColor(0xFE25FF);
  drawPolygonCircle(250,250, 165);
  setHexColor(0xFF6141);
  drawFlower(82, 8, 250, 250);
  drawSmallStar();
  setHexColor(0xFF6141);
  drawPolygonCircle(250,250, 50);
  setHexColor(0x41FFE8);
  drawPolygonCircle(250,250, 30);
  setHexColor(0x0200E8);
  drawPolygonCircle(250,300, 15);
  drawPolygonCircle(250,200, 15);
  drawPolygonCircle(300,250, 15);
  drawPolygonCircle(200,250, 15);
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

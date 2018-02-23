//  introOpenGl.cpp
//  Creado por Andrea Rueda, 01/2018
//

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>

using namespace std;


void myInit (void) {

    glClearColor(1.0,1.0,1.0,1.0);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(0, 640, 0, 480);
    //glOrtho(0, 640, 0, 480, 1.0, -1.0);

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

void myDisplay (void) {

  glClear(GL_COLOR_BUFFER_BIT);
  glPointSize(2.0);
  glColor3f(1.0, 0.0, 0.0);
  drawPoint(100, 100);

  drawEllipse(100.0, 100.0, 50.0, 50.0);

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

    glutInitWindowSize(640, 480);

    glutInitWindowPosition(100, 100);

    glutCreateWindow("Graphics Window");

    glutDisplayFunc(myDisplay);

    glutReshapeFunc(myResize);

    myInit();

    glutMainLoop();

    return 0;

}

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
  while (xk <= yk) {
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

void drawElipse(int xc, int yc, double rx, double ry) {
  d
}

void myDisplay (void) {

  glClear(GL_COLOR_BUFFER_BIT);
  glPointSize(0.0);
  glColor3f(1.0, 0.0, 0.0);
  drawPoint(100, 100);

  drawCircle(100, 100, 70);

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

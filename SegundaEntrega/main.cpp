#include <GL/freeglut.h>
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <iostream>

#define WIDTH 800
#define HEIGHT 500

using namespace std;

GLint ancho=WIDTH;
GLint alto=HEIGHT;

GLfloat anguloRotacionX = 0.0f;
GLfloat anguloRotacionY = 0.0f;

float minX = 0.0, minY = 0.0, minZ = 0.0;
float maxX = 15.0, maxY = 7.0, maxZ = 15.0;

float wx = (maxX - minX) / 5.0, wy = (maxY - minY) / 2.0, wz = (maxZ - minZ) / 2.0;

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    //TODO: Check GL_MODELVIEW
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0f, (GLfloat)width/(GLfloat)height, 1.0f, 100.0f);

    glMatrixMode(GL_MODELVIEW);

    ancho = width;
    alto = height;
}

/**
  *
  * Converts a number in hexadecimal to
  * OpenGL color.
  *
  */

void setHexColor(int color) {
  float r = ((0xFF0000 & color) >> 16) / 255.0;
  float g = ((0x00FF00 & color) >> 8) / 255.0;
  float b = (0x0000FF & color) / 255.0;
  glColor3f(r, g, b);
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

void drawWoody() {
  //Head
  setHexColor(0xc99c9c);
  glPushMatrix();
  glTranslatef(wx, wy, wz);
  glutSolidSphere(0.5, 100, 100);
  // glutWireTeapot(10);
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


  //Left leg
  setHexColor(0x1f3480);
  glPushMatrix();
  glTranslatef(wx, wy/2.8, wz*1.031);
  glScalef(1.0/10.0, 0.6, 1.0/3.0);
  glutSolidCube(1);
  glPopMatrix();

  //Left leg
  setHexColor(0x1f3480);
  glPushMatrix();
  glTranslatef(wx, wy/4.0, wz*1.031);
  glScalef(1.0/10.0, 1, 1.0/3.0);
  glutSolidCube(1);
  glPopMatrix();

  // Knee
  setHexColor(0x74cfa3);
  glPushMatrix();
  glTranslatef(wx, wy/4.0, wz*1.031);
  // glScalef(1.0/10.0, 0.45, 1.0/6.0);
  glutSolidSphere(0.12, 100, 100);
  glPopMatrix();

  //Right leg
  setHexColor(0x1f3480);
  glPushMatrix();
  glTranslatef(wx, wy/2.8, wz/1.031);
  glScalef(1.0/10.0, 0.6, 1.0/3.0);
  glutSolidCube(1);
  glPopMatrix();

  //Right leg
  setHexColor(0x1f3480);
  glPushMatrix();
  glTranslatef(wx, wy/4.0, wz/1.031);
  glScalef(1.0/10.0, 1, 1.0/3.0);
  glutSolidCube(1);
  glPopMatrix();

  // Knee
  setHexColor(0x74cfa3);
  glPushMatrix();
  glTranslatef(wx, wy/4.0, wz/1.031);
  // glScalef(1.0/10.0, 0.45, 1.0/6.0);
  glutSolidSphere(0.12, 100, 100);
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

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    //float eyeX = (maxX - minX)/2.0, eyeY = 8.0f, eyeZ = 25.0f, centerX = (maxX - minX)/2.0, centerY = 0.0f, centerZ = 0.0f, upX = 0.0f, upY = 1.0f, upZ = 0.0f;
    // float eyeX = (maxX - minX)/2.0, eyeY = 30.0f, eyeZ = (maxZ - minZ)/2.0, centerX = (maxX - minX)/2.0, centerY = 0.0f, centerZ = (maxZ - minZ)/2.0, upX = 0.0f, upY = 0.0f, upZ = 1.0f;
    //float eyeX = (maxX - minX)/2.0, eyeY = 3.5, eyeZ = 25.0, centerX = wx, centerY = wy, centerZ = wz, upX = 0.0f, upY = 1.0f, upZ = 0.0f;
    float eyeX = 10.0, eyeY = 3.5f, eyeZ = (maxZ - minZ)/2.0, centerX = wx, centerY = wy, centerZ = wz, upX = 0.0f, upY = 1.0f, upZ = 0.0f;
    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

    // glRotatef(anguloRotacionX, 1.0f, 0.0f, 0.0f);
    // glRotatef(anguloRotacionY, 0.0f, 1.0f, 0.0f);

    showImportantPoints();

    setHexColor(0xFFFFFF);
    drawBackWall();

    setHexColor(0x888888);
    drawFloor();

    setHexColor(0xaf2727);
    drawCarpet();

    setHexColor(0xEEEEEE);
    drawLeftWall();


    drawWoody();

    glFlush();
    glutSwapBuffers();

    anguloRotacionX += 0.1f;
    anguloRotacionY += 0.1f;
}


void init() {
    glClearColor(0,0,0,0);
    ancho = WIDTH;
    alto = HEIGHT;
}

void idle() {
    display();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    // glEnable(GL_DEPTH_TEST); // TODO - When compliling in MacOS throws segmentation fault
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(ancho, alto);
    glutCreateWindow("Segunda Entrega Intro. Comp Grafica");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}

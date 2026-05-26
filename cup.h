#ifndef CUP_H
#define CUP_H

#include <GL/glut.h>
#include <GL/glu.h>

inline void drawCup() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glScalef(0.3f, 0.02f, 0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glColor3f(1.0f, 0.6f, 0.1f);
    glPushMatrix();
    glTranslatef(0.0f, 0.01f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    GLUquadric* quad = gluNewQuadric();
    gluCylinder(quad, 0.08f, 0.08f, 0.35f, 20, 20);
    gluDeleteQuadric(quad);
    glPopMatrix();
}

#endif
#ifndef BOOTH_H
#define BOOTH_H

#include <GL/glut.h>

inline void drawBooth() {
    glColor3f(0.6f, 0.2f, 0.25f);
    glPushMatrix();
    glTranslatef(0.0f, 0.25f, 0.0f);
    glScalef(0.8f, 0.5f, 4.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.25f, 0.9f, 0.0f);
    glScalef(0.3f, 1.2f, 4.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glColor3f(0.8f, 0.7f, 0.5f);
    glPushMatrix();
    glTranslatef(-0.41f, 0.9f, 2.0f);
    glScalef(0.05f, 1.2f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

#endif
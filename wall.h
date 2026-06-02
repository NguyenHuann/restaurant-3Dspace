#ifndef WALL_H
#define WALL_H
#include <GL/glut.h>

inline void drawWall() {
    glColor3f(0.5f, 0.8f, 0.5f);

    // Tường sau
    glPushMatrix();
    glTranslatef(0.0f, 3.0f, -8.1f);
    glScalef(20.2f, 6.0f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Tường trái
    glPushMatrix();
    glTranslatef(-10.1f, 3.0f, 0.9f);
    glScalef(0.2f, 6.0f, 18.2f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Tường phải
    glPushMatrix();
    glTranslatef(10.1f, 3.0f, 0.9f);
    glScalef(0.2f, 6.0f, 18.2f);
    glutSolidCube(1.0f);
    glPopMatrix();
}
#endif
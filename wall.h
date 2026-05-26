#ifndef WALL_H
#define WALL_H

#include <GL/glut.h>

inline void drawWall() {
    glColor3f(0.65f, 0.6f, 0.75f);

    // 1. Bức tường phía sau (Kéo dài từ X = -7.2 đến 7.2)
    glPushMatrix();
    glTranslatef(0.0f, 3.0f, -2.1f); // Lùi ra sau sàn một chút (Z = -2.1)
    glScalef(14.4f, 6.0f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // 2. Bức tường bên trái (Kéo dài từ Z = -2.2 đến 6.0)
    glPushMatrix();
    glTranslatef(-7.1f, 3.0f, 1.9f); // Đặt sát mép trái sàn (X = -7.1)
    glScalef(0.2f, 6.0f, 8.2f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // 3. Bức tường bên phải (Đối xứng tường trái)
    glPushMatrix();
    glTranslatef(7.1f, 3.0f, 1.9f); // Đặt sát mép phải sàn (X = 7.1)
    glScalef(0.2f, 6.0f, 8.2f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

#endif
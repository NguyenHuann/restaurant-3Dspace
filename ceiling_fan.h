#ifndef CEILINGFAN_H
#define CEILINGFAN_H

#include <GL/glut.h>

inline void drawCeilingFan(float angle) {
    // Trục quạt
    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix();
    glTranslatef(0.0f, -0.5f, 0.0f);
    glScalef(0.05f, 1.0f, 0.05f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, -1.0f, 0.0f);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);

    // Bầu quạt (bán kính 0.25)
    glColor3f(0.3f, 0.3f, 0.3f);
    glutSolidSphere(0.25f, 20, 20);

    // 3 Cánh quạt (Tăng độ dài sải cánh và độ rộng)
    glColor3f(0.0f, 1.0f, 0.4f);
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glRotatef(i * 120.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(1.0f, 0.0f, 0.0f);  // Đẩy tâm cánh ra xa hơn (0.6 -> 1.0)
        glScalef(1.8f, 0.02f, 0.35f);    // Cánh dài 1.8 và rộng 0.35 (Cũ: 1.0 và 0.2)
        glutSolidCube(1.0f);
        glPopMatrix();
    }
    glPopMatrix();
}

#endif
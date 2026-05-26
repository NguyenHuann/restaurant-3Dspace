#ifndef LAMP_H
#define LAMP_H

#include <GL/glut.h>
#include <math.h>

inline void drawGradientFrustum(float baseRadius, float topRadius, float height,
    float r1, float g1, float b1,
    float r2, float g2, float b2)
{
    int slices = 30;
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= slices; i++) {
        float angle = 2.0f * 3.14159265f * i / slices;
        float cx = cos(angle);
        float cz = sin(angle);

        glNormal3f(cx, 0.0f, cz);

        glColor3f(r1, g1, b1);
        glVertex3f(cx * baseRadius, 0.0f, cz * baseRadius);

        glColor3f(r2, g2, b2);
        glVertex3f(cx * topRadius, height, cz * topRadius);
    }
    glEnd();
}

inline void drawLamp() {
    glPushMatrix();

    // 1. Đế đèn ốp trần (Thu nhỏ scale X và Z)
    glColor3f(0.95f, 0.9f, 0.85f);
    glPushMatrix();
    glTranslatef(0.0f, -0.05f, 0.0f);
    glScalef(0.2f, 0.05f, 0.2f); // Cũ: 0.4, 0.1, 0.4
    glutSolidCube(1.0f);
    glPopMatrix();

    // 2. Thân đèn (Bóp mảnh bán kính lại, giữ nguyên chiều dài 1.5)
    glPushMatrix();
    glTranslatef(0.0f, -1.6f, 0.0f);
    drawGradientFrustum(0.04f, 0.04f, 1.5f, // Bán kính giảm từ 0.08 xuống 0.04
        0.7f, 0.9f, 0.2f,
        0.0f, 0.8f, 0.8f);
    glPopMatrix();

    // 3. Chụp đèn (Giảm mạnh bán kính mở rộng và chiều cao)
    glPushMatrix();
    glTranslatef(0.0f, -2.4f, 0.0f); // Dịch lên một chút vì chụp đèn ngắn đi
    drawGradientFrustum(0.4f, 0.15f, 0.8f,  // Đáy: 0.4, Đỉnh: 0.15, Cao: 0.8 (Cũ: 0.7, 0.3, 1.0)
        1.0f, 1.0f, 1.0f,
        0.1f, 0.1f, 0.1f);
    glPopMatrix();

    glPopMatrix();
}

#endif
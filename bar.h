#ifndef BAR_H
#define BAR_H
#include <GL/glut.h>
#include <GL/glu.h>
#include "lamp.h" // Kế thừa hàm vẽ dải màu gradient

// 1. Vẽ chai thủy tinh Gradient
inline void drawBottle(float r1, float g1, float b1, float r2, float g2, float b2) {
    glPushMatrix();
    // Thân chai
    drawGradientFrustum(0.12f, 0.12f, 0.4f, r1, g1, b1, r2, g2, b2);
    // Cổ chai thuôn nhỏ
    glPushMatrix();
    glTranslatef(0.0f, 0.4f, 0.0f);
    drawGradientFrustum(0.12f, 0.04f, 0.2f, r2, g2, b2, r2, g2, b2);
    glPopMatrix();
    glPopMatrix();
}

// 2. Vẽ Kệ rượu gắn tường
inline void drawShelf() {
    // Tấm ốp lưng gỗ
    glColor3f(0.8f, 0.6f, 0.4f);
    glPushMatrix();
    glTranslatef(0.0f, 3.0f, -0.1f);
    glScalef(8.0f, 3.0f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // 2 Đợt kệ ngang màu đen
    glColor3f(0.1f, 0.1f, 0.1f);
    for (float y = 2.0f; y <= 3.5f; y += 1.5f) {
        glPushMatrix();
        glTranslatef(0.0f, y, 0.4f);
        glScalef(8.0f, 0.1f, 1.0f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }

    // Đặt các chai lên kệ dưới
    float bx = -3.5f;
    for (int i = 0; i < 5; i++) {
        glPushMatrix(); glTranslatef(bx, 2.05f, 0.4f); drawBottle(0.0f, 0.8f, 1.0f, 1.0f, 0.5f, 0.0f); glPopMatrix(); bx += 0.8f;
        glPushMatrix(); glTranslatef(bx, 2.05f, 0.4f); drawBottle(1.0f, 1.0f, 1.0f, 0.2f, 0.2f, 0.2f); glPopMatrix(); bx += 0.8f;
    }

    // Đặt các chai lên kệ trên
    bx = -3.5f;
    for (int i = 0; i < 5; i++) {
        glPushMatrix(); glTranslatef(bx, 3.55f, 0.4f); drawBottle(1.0f, 0.5f, 0.0f, 0.2f, 0.2f, 0.2f); glPopMatrix(); bx += 0.8f;
        glPushMatrix(); glTranslatef(bx, 3.55f, 0.4f); drawBottle(0.0f, 0.8f, 1.0f, 1.0f, 1.0f, 1.0f); glPopMatrix(); bx += 0.8f;
    }
}

// 3. Vẽ Tủ lạnh góc
inline void drawFridge() {
    glColor3f(0.8f, 0.2f, 0.2f); // Đỏ
    glPushMatrix();
    glTranslatef(0.0f, 2.0f, 0.0f);
    glScalef(1.5f, 4.0f, 1.5f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Cánh tủ màu trắng
    glColor3f(0.9f, 0.9f, 0.9f);
    glPushMatrix();
    glTranslatef(0.76f, 2.0f, 0.0f); // Nhô ra mặt trước
    glScalef(0.05f, 3.8f, 1.3f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

// 4. Vẽ Mặt bàn quầy Bar dài
inline void drawBarCounter() {
    // Đế quầy (Màu be)
    glColor3f(0.85f, 0.75f, 0.55f);
    glPushMatrix();
    glTranslatef(0.0f, 0.6f, 0.0f);
    glScalef(1.8f, 1.2f, 12.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Mặt quầy (màu xám)
    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();
    glTranslatef(0.0f, 1.25f, 0.0f);
    glScalef(2.0f, 0.1f, 12.2f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

// 5. Vẽ Ghế Bar (Chân kim loại, mặt ghế Gradient)
inline void drawStool() {
    GLUquadric* quad = gluNewQuadric();

    // Chân cột & Đế
    glColor3f(0.7f, 0.9f, 0.7f); // Màu xanh kim loại nhạt (như trong ảnh)
    glPushMatrix();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Dựng đứng trụ
    gluCylinder(quad, 0.3f, 0.3f, 0.05f, 20, 20); // Đế đĩa tròn
    gluCylinder(quad, 0.05f, 0.05f, 1.0f, 20, 20); // Trục ghế
    glPopMatrix();

    // Mặt đệm ghế (Gradient Xanh Cyan lên Vàng)
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 0.0f);
    drawGradientFrustum(0.4f, 0.4f, 0.15f,
        0.0f, 0.8f, 1.0f,   // Đáy: Cyan
        1.0f, 0.9f, 0.1f);  // Đỉnh: Vàng chanh

    // Đậy nắp phẳng mặt ghế màu vàng
    glColor3f(1.0f, 0.9f, 0.1f);
    glTranslatef(0.0f, 0.15f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluDisk(quad, 0.0f, 0.4f, 20, 1);
    glPopMatrix();

    gluDeleteQuadric(quad);
}
#endif
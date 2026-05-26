#ifndef FLOOR_H
#define FLOOR_H

#include <GL/glut.h>

inline void drawFloor() {
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);

    float tileSize = 1.0f; // Chỉnh kích thước gạch nhỏ lại để chia chẵn theo phòng

    // Giới hạn chiều ngang: từ -7 đến 7
    // Giới hạn chiều sâu: từ -2 (sát tường sau) đến 6 (mặt tiền mở)
    for (int i = -7; i < 7; i++) {
        for (int j = -2; j < 6; j++) {
            if ((i + j) % 2 == 0) {
                glColor3f(0.95f, 0.95f, 0.9f); // Trắng ngà
            }
            else {
                glColor3f(0.02f, 0.02f, 0.02f); // Đen
            }
            glVertex3f(i * tileSize, 0.0f, j * tileSize);
            glVertex3f((i + 1) * tileSize, 0.0f, j * tileSize);
            glVertex3f((i + 1) * tileSize, 0.0f, (j + 1) * tileSize);
            glVertex3f(i * tileSize, 0.0f, (j + 1) * tileSize);
        }
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

#endif
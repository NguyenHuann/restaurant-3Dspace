#ifndef FLOOR_H
#define FLOOR_H
#include <GL/glut.h>

inline void drawFloor() {
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);
    float tileSize = 1.0f;
    // Thu hẹp trục X từ -10 đến 10, trục Z lùi về sau tới -8
    for (int i = -10; i < 10; i++) {
        for (int j = -8; j < 10; j++) {
            if ((i + j) % 2 == 0) glColor3f(0.95f, 0.95f, 0.9f);
            else glColor3f(0.02f, 0.02f, 0.02f);
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
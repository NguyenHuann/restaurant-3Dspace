#ifndef TABLE_H
#define TABLE_H
#include <GL/glut.h>
#include <stdio.h>

// Hàm load file BMP sử dụng chuẩn an toàn fopen_s của Visual Studio
inline GLuint loadBMP(const char* filename) {
    unsigned char header[54];
    FILE* file;

    // Dùng fopen_s thay cho fopen. 
    // Nếu hàm trả về khác 0 nghĩa là mở file thất bại.
    if (fopen_s(&file, filename, "rb") != 0 || !file) {
        printf("Khong the mo file anh texture: %s\n", filename);
        return 0;
    }

    if (fread(header, 1, 54, file) != 54 || header[0] != 'B' || header[1] != 'M') {
        fclose(file);
        return 0;
    }

    int dataPos = *(int*)&(header[0x0A]), width = *(int*)&(header[0x12]);
    int height = *(int*)&(header[0x16]), imageSize = *(int*)&(header[0x22]);
    if (!imageSize) imageSize = width * height * 3;
    if (!dataPos) dataPos = 54;

    unsigned char* data = new unsigned char[imageSize];
    fseek(file, dataPos, SEEK_SET);
    fread(data, 1, imageSize, file);
    fclose(file);

    for (int i = 0; i < imageSize; i += 3) {
        unsigned char tmp = data[i]; data[i] = data[i + 2]; data[i + 2] = tmp;
    }

    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    delete[] data; return texID;
}

// Truyền texID vào hàm drawTable
inline void drawTable(GLuint texID) {
    // 1. Vẽ khối bàn như bình thường (không texture)
    glDisable(GL_TEXTURE_2D);
    glColor3f(0.85f, 0.75f, 0.55f);
    glPushMatrix();
    glTranslatef(0.0f, 0.95f, 0.0f);
    glScalef(2.0f, 0.1f, 4.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glColor3f(0.95f, 0.95f, 0.9f);
    float lx = 0.85f, lz = 1.85f;
    float legs[4][3] = { {-lx, 0.45f, -lz}, {lx, 0.45f, -lz}, {-lx, 0.45f, lz}, {lx, 0.45f, lz} };
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(legs[i][0], legs[i][1], legs[i][2]);
        glScalef(0.15f, 0.9f, 0.15f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }

    // 2. Dán lớp vân gỗ đè lên trên cùng mặt bàn
    if (texID > 0) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texID);
        glColor3f(1.0f, 1.0f, 1.0f); // Phải để màu trắng để ảnh không bị ám màu

        glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);
        float y = 1.001f; // Đặt mặt phẳng vân gỗ nhô cao hơn mặt khối hộp đúng 0.001 đơn vị
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, y, -2.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, y, 2.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, y, 2.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, y, -2.0f);
        glEnd();

        glDisable(GL_TEXTURE_2D);
    }
}
#endif
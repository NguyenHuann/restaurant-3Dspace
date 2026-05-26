#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>   // Thư viện toán học tính hướng nhìn Camera
#include <stdlib.h> // Thư viện chứa hàm exit()

// Nhúng trực tiếp các file Header-only
#include "floor.h"
#include "wall.h"
#include "table.h"
#include "booth.h"
#include "cup.h"
#include "ceiling_fan.h"
#include "lamp.h"

#define PI 3.14159265f

// CÁC BIẾN TOÀN CỤC ĐIỀU KHIỂN & MÔI TRƯỜNG
GLuint tableTexID;
float fanAngle = 0.0f;

// Trạng thái tương tác
bool isFanOn = true;         // Phím G: Quạt chạy
bool isAutoRotate = false;   // Phím F: Camera tự động xoay
float autoRotateAngle = 0.0f;// Góc xoay tự động

// Các biến của Camera
float camX = 10.0f, camY = 7.0f, camZ = 16.0f; // Vị trí Camera ban đầu
float lookX = 0.0f, lookY = 0.0f, lookZ = -1.0f; // Vector hướng nhìn
float yaw = -120.0f; // Góc xoay trái phải (Góc nhìn ban đầu hướng chéo vào giữa phòng)
float pitch = -15.0f; // Góc ngẩng/cúi
float moveSpeed = 0.5f;

// Biến theo dõi thao tác chuột
bool isRightMouseDown = false;
int lastMouseX = -1, lastMouseY = -1;

// HÀM TÍNH TOÁN HƯỚNG NHÌN CAMERA
void updateCameraDirection() {
    lookX = cos(yaw * PI / 180.0f) * cos(pitch * PI / 180.0f);
    lookY = sin(pitch * PI / 180.0f);
    lookZ = sin(yaw * PI / 180.0f) * cos(pitch * PI / 180.0f);
}

// HÀM BẮT SỰ KIỆN CHUỘT
void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN) {
            isRightMouseDown = true;
            lastMouseX = x;
            lastMouseY = y;
        }
        else if (state == GLUT_UP) {
            isRightMouseDown = false;
        }
    }
}

void mouseMotion(int x, int y) {
    if (isRightMouseDown) {
        float xOffset = x - lastMouseX;
        float yOffset = lastMouseY - y; // Đảo ngược y vì trục Y của chuột hướng xuống
        lastMouseX = x;
        lastMouseY = y;

        float sensitivity = 0.2f; // Độ nhạy chuột
        yaw += xOffset * sensitivity;
        pitch += yOffset * sensitivity;

        // Giới hạn góc ngẩng/cúi để không bị lộn ngược Camera
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        updateCameraDirection();
        glutPostRedisplay();
    }
}

// HÀM BẮT SỰ KIỆN BÀN PHÍM
void keyboard(unsigned char key, int x, int y) {
    // Nếu đang chế độ tự động xoay, vô hiệu hóa W A S D E R
    if (!isAutoRotate) {
        if (key == 'w' || key == 'W') { camX += lookX * moveSpeed; camY += lookY * moveSpeed; camZ += lookZ * moveSpeed; }
        if (key == 's' || key == 'S') { camX -= lookX * moveSpeed; camY -= lookY * moveSpeed; camZ -= lookZ * moveSpeed; }

        // Strafe (Di chuyển ngang) sử dụng tích có hướng (Cross Product)
        if (key == 'a' || key == 'A') {
            float rx = -lookZ, rz = lookX; // Vector vuông góc với hướng nhìn trên mặt phẳng XZ
            float len = sqrt(rx * rx + rz * rz);
            camX -= (rx / len) * moveSpeed; camZ -= (rz / len) * moveSpeed;
        }
        if (key == 'd' || key == 'D') {
            float rx = -lookZ, rz = lookX;
            float len = sqrt(rx * rx + rz * rz);
            camX += (rx / len) * moveSpeed; camZ += (rz / len) * moveSpeed;
        }

        // Di chuyển trục Y (Lên/Xuống)
        if (key == 'e' || key == 'E') { camY += moveSpeed; }
        if (key == 'r' || key == 'R') { camY -= moveSpeed; }
    }

    // Tương tác môi trường
    if (key == 'g' || key == 'G') { isFanOn = !isFanOn; }
    if (key == 'f' || key == 'F') { isAutoRotate = !isAutoRotate; }
    if (key == 27) { exit(0); } // 27 là mã ASCII của phím ESC

    glutPostRedisplay();
}

// CÁC HÀM CỐT LÕI
void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    GLfloat lightPos[] = { 5.0f, 10.0f, 10.0f, 0.0f };
    GLfloat ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    tableTexID = loadBMP("resource/van-go-lim.bmp");

    // Khởi tạo hướng nhìn ban đầu
    updateCameraDirection();
}

void buildTableSet(float xPosition, GLuint texID) {
    glPushMatrix();
    glTranslatef(xPosition, 0.0f, 1.0f);
    drawTable(texID);

    glPushMatrix(); glTranslatef(0.0f, 1.0f, 0.5f); drawCup(); glPopMatrix();
    glPushMatrix(); glTranslatef(-1.5f, 0.0f, 0.0f); drawBooth(); glPopMatrix();
    glPushMatrix(); glTranslatef(1.5f, 0.0f, 0.0f); glScalef(-1.0f, 1.0f, 1.0f); drawBooth(); glPopMatrix();

    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Hệ thống Camera logic kép
    if (isAutoRotate) {
        // Chế độ Cinematic: Trượt vòng tròn quanh phòng
        float radius = 18.0f;
        float rX = sin(autoRotateAngle * PI / 180.0f) * radius;
        float rZ = cos(autoRotateAngle * PI / 180.0f) * radius;
        gluLookAt(rX, 8.0f, rZ,           // Vị trí Camera quay vòng tròn
            0.0f, 2.0f, 0.0f,       // Luôn nhìn vào giữa phòng
            0.0f, 1.0f, 0.0f);
    }
    else {
        // Chế độ Free Camera: Di chuyển bằng phím/chuột
        gluLookAt(camX, camY, camZ,
            camX + lookX, camY + lookY, camZ + lookZ,
            0.0f, 1.0f, 0.0f);
    }

    drawFloor();
    drawWall();

    buildTableSet(-4.5f, tableTexID);
    buildTableSet(0.0f, tableTexID);
    buildTableSet(4.5f, tableTexID);

    glPushMatrix();
    glTranslatef(0.5f, 6.0f, 3.0f);
    drawCeilingFan(fanAngle);
    glPopMatrix();

    glPushMatrix(); glTranslatef(-4.5f, 6.0f, 1.0f); drawLamp(); glPopMatrix();
    glPushMatrix(); glTranslatef(0.0f, 6.0f, 1.0f); drawLamp(); glPopMatrix();
    glPushMatrix(); glTranslatef(4.5f, 6.0f, 1.0f); drawLamp(); glPopMatrix();

    glutSwapBuffers();
}

void timer(int value) {
    if (isFanOn) {
        fanAngle += 4.0f;
        if (fanAngle > 360.0f) fanAngle -= 360.0f;
    }

    if (isAutoRotate) {
        autoRotateAngle += 0.5f;
        if (autoRotateAngle > 360.0f) autoRotateAngle -= 360.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float ratio = (float)w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0f, ratio, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("Interactive 3D Restaurant");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);

    // Đăng ký các hàm bắt sự kiện tương tác
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMotion);

    glutMainLoop();
    return 0;
}
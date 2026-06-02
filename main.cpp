#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include <stdlib.h>

#include "floor.h"
#include "wall.h"
#include "table.h"
#include "booth.h"
#include "cup.h"
#include "ceiling_fan.h"
#include "lamp.h"
#include "bar.h" 

#define PI 3.14159265f

GLuint tableTexID;
float fanAngle = 0.0f;
bool isFanOn = true, isAutoRotate = false;
float autoRotateAngle = 0.0f;

// Camera đặt vị trí chéo góc giống ảnh mẫu
float camX = -3.0f, camY = 6.0f, camZ = 12.0f;
float lookX = 0.0f, lookY = 0.0f, lookZ = -1.0f;
float yaw = -75.0f, pitch = -15.0f, moveSpeed = 0.5f;

bool isRightMouseDown = false;
int lastMouseX = -1, lastMouseY = -1;

void updateCameraDirection() {
    lookX = cos(yaw * PI / 180.0f) * cos(pitch * PI / 180.0f);
    lookY = sin(pitch * PI / 180.0f);
    lookZ = sin(yaw * PI / 180.0f) * cos(pitch * PI / 180.0f);
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN) { isRightMouseDown = true; lastMouseX = x; lastMouseY = y; }
        else if (state == GLUT_UP) isRightMouseDown = false;
    }
}

void mouseMotion(int x, int y) {
    if (isRightMouseDown) {
        yaw += (x - lastMouseX) * 0.2f;
        pitch += (lastMouseY - y) * 0.2f;
        lastMouseX = x; lastMouseY = y;
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;
        updateCameraDirection();
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (!isAutoRotate) {
        if (key == 'w' || key == 'W') { camX += lookX * moveSpeed; camY += lookY * moveSpeed; camZ += lookZ * moveSpeed; }
        if (key == 's' || key == 'S') { camX -= lookX * moveSpeed; camY -= lookY * moveSpeed; camZ -= lookZ * moveSpeed; }
        if (key == 'a' || key == 'A') { float rx = -lookZ, rz = lookX; float len = sqrt(rx * rx + rz * rz); camX -= (rx / len) * moveSpeed; camZ -= (rz / len) * moveSpeed; }
        if (key == 'd' || key == 'D') { float rx = -lookZ, rz = lookX; float len = sqrt(rx * rx + rz * rz); camX += (rx / len) * moveSpeed; camZ += (rz / len) * moveSpeed; }
        if (key == 'e' || key == 'E') camY += moveSpeed;
        if (key == 'r' || key == 'R') camY -= moveSpeed;
    }
    if (key == 'g' || key == 'G') isFanOn = !isFanOn;
    if (key == 'f' || key == 'F') isAutoRotate = !isAutoRotate;
    if (key == 27) exit(0);
    glutPostRedisplay();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // màu nền xanh rêu tối 

    GLfloat lightPos[] = { 5.0f, 10.0f, 10.0f, 0.0f };
    GLfloat ambientLight[] = { 0.6f, 0.6f, 0.6f, 1.0f };
    GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    tableTexID = loadBMP("resource/van-go-lim.bmp");
    updateCameraDirection();
}


// BỔ SUNG: Hàm vẽ tủ nhỏ dưới tường
void drawCabinet() {
    glColor3f(0.2f, 0.3f, 0.4f); // Màu xanh biển đậm
    glPushMatrix(); glTranslatef(0.0f, 1.0f, 0.0f); glScalef(2.5f, 2.0f, 1.5f); glutSolidCube(1.0f); glPopMatrix();
    glColor3f(0.8f, 0.8f, 0.8f);
    for (float y = 0.5f; y <= 1.5f; y += 0.5f) {
        glPushMatrix(); glTranslatef(0.0f, y, 0.76f); glScalef(2.0f, 0.05f, 0.05f); glutSolidCube(1.0f); glPopMatrix();
    }
}

// THÊM THAM SỐ zPosition ĐỂ XẾP BÀN THEO CHIỀU DỌC
void buildTableSet(float xPosition, float zPosition, GLuint texID) {
    glPushMatrix();
    glTranslatef(xPosition, 0.0f, zPosition);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    drawTable(texID);
    glPushMatrix(); glTranslatef(0.0f, 1.0f, 0.5f); drawCup(); glPopMatrix();
    glPushMatrix(); glTranslatef(-1.5f, 0.0f, 0.0f); drawBooth(); glPopMatrix();
    glPushMatrix(); glTranslatef(1.5f, 0.0f, 0.0f); glScalef(-1.0f, 1.0f, 1.0f); drawBooth(); glPopMatrix();
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (isAutoRotate) {
        float rX = sin(autoRotateAngle * PI / 180.0f) * 15.0f;
        float rZ = cos(autoRotateAngle * PI / 180.0f) * 15.0f;
        gluLookAt(rX, 8.0f, rZ, 0.0f, 2.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    }
    else {
        gluLookAt(camX, camY, camZ, camX + lookX, camY + lookY, camZ + lookZ, 0.0f, 1.0f, 0.0f);
    }

    drawFloor();
    drawWall();

    // 1. CHI TIẾT TRANG TRÍ MỚI (Tủ xanh)
    glPushMatrix(); glTranslatef(2.0f, 0.0f, -7.2f); drawCabinet(); glPopMatrix(); // Tủ xanh

    // QUẠT TRẦN
    glPushMatrix();
    glTranslatef(3.5f, 6.25f, 0.0f); // Tọa độ treo quạt trên trần (bên phải phòng)
    drawCeilingFan(fanAngle);
    glPopMatrix();

    // 2. KHU VỰC BÀN ĂN (Xếp dọc theo trục Z bên phải)
    buildTableSet(6.0f, -3.0f, tableTexID);
    buildTableSet(6.0f, 1.0f, tableTexID);
    buildTableSet(6.0f, 5.0f, tableTexID);

    // 3. KHU VỰC QUẦY BAR VÀ GHẾ (Bên Trái)
    glPushMatrix();
    glTranslatef(-4.0f, 0.0f, 0.0f); // Tâm quầy bar đặt tại X = -4
    drawBarCounter();
    glPushMatrix(); glTranslatef(0.0f, 1.3f, -2.0f); drawCup(); glPopMatrix();
    glPushMatrix(); glTranslatef(0.0f, 1.3f, 2.0f); drawCup(); glPopMatrix();
    glPopMatrix();

    // Dãy ghế Bar (Dịch lại gần quầy bar ở X = -2.0)
    for (float z = -3.5f; z <= 3.5f; z += 1.4f) {
        glPushMatrix(); glTranslatef(-2.0f, 0.0f, z); drawStool(); glPopMatrix();
    }

    // Đèn thả trên quầy Bar
    for (float z = -2.0f; z <= 2.0f; z += 2.0f) {
        glPushMatrix(); glTranslatef(-4.0f, 6.0f, z); drawLamp(); glPopMatrix();
    }

    // 4. KỆ CHAI RƯỢU VÀ TỦ LẠNH 
    glPushMatrix(); glTranslatef(-8.5f, 0.0f, -6.5f); drawFridge(); glPopMatrix(); // Góc sau trái

    glPushMatrix();
    glTranslatef(-9.8f, 0.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    drawShelf();
    glPopMatrix();

    glutSwapBuffers();
}

void timer(int value) {
    if (isFanOn) { fanAngle += 4.0f; if (fanAngle > 360.0f) fanAngle -= 360.0f; }
    if (isAutoRotate) { autoRotateAngle += 0.5f; if (autoRotateAngle > 360.0f) autoRotateAngle -= 360.0f; }
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    gluPerspective(50.0f, (float)w / h, 0.1f, 100.0f);
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
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMotion);

    glutMainLoop();
    return 0;
}
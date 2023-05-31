//#include "graph.h"
//#include <glut.h>
//#include <iostream>
//using namespace std;
//int windowWidth = 800;
//int windowHeight = 800;
//void display() {
//    glClear(GL_COLOR_BUFFER_BIT);  // ������� ������ �����
//
//    // ��������� �������� �����
//
//
//    // ����������� ������ ����� � �������
//    float centerX = 0.0f;
//    float centerY = 0.0f;
//    float radius = 0.1f;
//
//    const int numSegments = 100;  // ���������� ��������� ��� ������������� ����������
//
//    // ��������� �����
//    glBegin(GL_TRIANGLE_FAN);
//    glVertex2f(centerX, centerY);  // ����� �����
//
//    for (int i = 0; i <= numSegments; i++) {
//        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
//        float x = radius * cosf(theta);
//        float y = radius * sinf(theta);
//        glVertex2f(centerX + x, centerY + y);
//    }
//
//    glEnd();
//
//    glFlush();  // �������������� ���������� ������ ����������
//}
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitWindowSize(windowWidth, windowHeight);  // ��������� �������� �������� ����
//    glutInitWindowPosition(550, 150);  // ��������� ������� ���� �� ������
//    glutCreateWindow("Graph");
//    glutReshapeWindow(windowWidth, windowHeight);
//    glutDisplayFunc(display);
//    glutMainLoop();
//    return 0;
//}
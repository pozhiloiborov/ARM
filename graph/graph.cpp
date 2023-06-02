#include "graph.h"

int  main(int argc, char* argv[])
{
    thread console(menu); // Запуск потока для работы с консолью
    makegraph();
    setlocale(LC_ALL, "Russian");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Графы");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutDisplayFunc(display);
    glutMainLoop();
    console.join();
    return 0;
}
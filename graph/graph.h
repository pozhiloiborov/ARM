#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <glut.h>
#include <string>
#include <thread>
using namespace std;

const int maxSize = 8;
class Graph
{
private:
    vector<int> vertList;
    int adjMatrix[maxSize][maxSize];
public:
    Graph();
    bool isEmpty();//�������� �� ������� �����
    bool isFull();//�������� �� �������������
    int getVertText(int i);//��������� ������ �������
    vector<int> getVertList();//��������� ������ ������                                 //
    int getAdjMatrixElem(int i, int j);//��������� �������� �� �������                    //
    void getAdjMatrix(int(&matrix)[maxSize][maxSize]);
    int getAmountVerts();//��������� ���������� ������
    int getVertPos(const int& vertex);//��������� ������� �������
    int getAmountEdges();//��������� ���������� �����                                 //
    void changeWeight(int i, int j,int weight);//��������� ���� �����                //
    void insertVertex(const int& vertex);//���������� �������
    void insertEdge(const int& vertex1, const int& vertex2, int weight);//���������� ������������� �����
    void insertEdgeWO(const int& vertex1, const int& vertex2, int weight);//���������� ��������������� �����
    void print();//������ �������
    void eraseEdge(const int& vertex1, const int& vertex2);//�������� �����
    void eraseVertex(const int& vertex); //�������� �������
    void dijkstra(int startVertex); // ��������
    void BFS(int startVertex); // ����� � ������
    void DFS(int startVertex); // ����� � �������
    void dfsRec(vector<bool>& visited, int currVertex, const vector<int>& vertList, int adjMatrix[][maxSize]); //�������� ��� ������ � �������
    void drawGraph();
    int komivoya(int startVertex, vector<int>& optimalPath);
    void komivoyaRec(int currVertex, int level, int pathLength, int& minPathLength, vector<bool>& visited, vector<int>& optimalPath);
    vector<int> visitedIndices(const vector<bool>& visited);
};
void drawCircle(int x, int y, int R);
void display();
void drawVertex(int n);
void setCoords(int i, int n);
void drawLine(int text, int x0, int y0, int x1, int y1, int start, int end,bool f);
void drawText(int text, int x1, int y1,bool f);
void menu();
void makegraph();
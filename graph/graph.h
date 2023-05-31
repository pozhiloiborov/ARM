#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <glut.h>
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
    vector<int> getVertList();//��������� ������ ������
    int getAdjMatrixElem(int i, int j);//��������� �������� �� �������
    int getAmountVerts();//��������� ���������� ������
    int getVertPos(const int& vertex);//��������� ������� �������
    int getAmountEdges();//��������� ���������� �����
    void changeWeight(int i, int j,int weight);//��������� ���� �����
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
    int komivoya(int startVertex,vector<int>& optimalPath); //������� ������ �����������
    void komivoyaRec(int currVertex, int level, int pathLength, int& minPathLength, vector<bool>& visited, vector<int>& optimalPath); // ��������������� ����������� ������� ��� ������� ������ �����������
    vector<int> visitedIndices(const vector<bool>& visited); // ��������������� ������� ��� ��������� �������� ���������� ������
};
Graph::Graph() {
    for (int i = 0; i < maxSize; i++)
        for (int j = 0; j < maxSize; j++)
            adjMatrix[i][j] = 0;
}
bool Graph::isEmpty() {
    return (vertList.size() == 0);
} 
bool Graph::isFull() {
    return (vertList.size() == maxSize);
}
int Graph::getVertText(int i) {
    return vertList[i];
}
vector<int> Graph::getVertList() {
    return vertList;
}
int Graph::getAdjMatrixElem(int i, int j) {
    return adjMatrix[i][j];
}
int Graph::getAmountVerts() {
    return vertList.size();
}
int Graph::getVertPos(const int& vertex) {
    for (int i = 0; i < vertList.size(); i++)
        if (vertList[i] == vertex)
            return i;

    return -1;
}
int Graph::getAmountEdges() {
    int amount = 0;
    for (int i = 0; i < vertList.size(); i++) {
        for (int j = 0; j < vertList.size(); j++) {
            if (adjMatrix[i][j] > 0) {
                amount++;
            }
        }
    }
    return amount;
}
void Graph::changeWeight(int i, int j,int weight) {
    adjMatrix[i][j] = adjMatrix[j][i] = weight;
}
void Graph::insertVertex(const int& vertex) {
    if (isFull()) {
        cout << "����� ������ ���������" << endl;
        return;
    }
    vertList.push_back(vertex);
}
void Graph::insertEdge(const int& vertex1, const int& vertex2, int weight) {
    if (weight < 1) {
        cout << "������ ������ �������� ������ 1! " << endl;
        return;
    }
    if (getVertPos(vertex1) == -1 || getVertPos(vertex2) == -1) {
        cout << "����� ��� ����� ������ �� ���������� " << endl;
        return;
    }
    int vertPos1 = getVertPos(vertex1);
    int vertPos2 = getVertPos(vertex2);
    if (adjMatrix[vertPos1][vertPos2] != 0) {
        cout << " ����� ��� ���� " << endl;
        return;
    }
    adjMatrix[vertPos1][vertPos2] = weight;
}
void Graph::insertEdgeWO(const int& vertex1, const int& vertex2, int weight) {
    if (weight < 1) {
        cout << "������ ������ �������� ������ 1! " << endl;
        return;
    }
    if (getVertPos(vertex1) == -1 || getVertPos(vertex2) == -1) {
        cout << "����� ��� ����� ������ �� ���������� " << endl;
        return;
    }
    int vertPos1 = getVertPos(vertex1);
    int vertPos2 = getVertPos(vertex2);
    if (adjMatrix[vertPos1][vertPos2] != 0) {
        cout << " ����� ��� ���� " << endl;
        return;
    }
    adjMatrix[vertPos1][vertPos2] = weight;
    adjMatrix[vertPos2][vertPos1] = weight;
}
void Graph::print() {
    if (isEmpty()) {
        cout << "���� ���� " << endl;
        return;
    }
    cout << "     ";
    for (int i = 0; i < vertList.size();i++)
    cout << vertList[i] << "  ";
    cout << endl;
    for (int i = 0; i < vertList.size(); i++) {
        cout << vertList[i] << "|   ";
        for (int j = 0; j < vertList.size(); j++)
            cout << adjMatrix[i][j]<<"  ";
        cout << endl;
    }
}
void Graph::eraseEdge(const int& vertex1, const int& vertex2) {
    if (getVertPos(vertex1) == -1 || getVertPos(vertex2) == -1) {
        cout << "����� ��� ����� ������ �� ���������� " << endl;
        return;
    }

    int vertPos1 = getVertPos(vertex1);
    int vertPos2 = getVertPos(vertex2);
    if (adjMatrix[vertPos1][vertPos2] == 0) {
        cout << " ����� � ��� ����" << endl;
        return;
    }
    adjMatrix[vertPos1][vertPos2] = 0;
}
void Graph::eraseVertex(const int& vertex)
{
    auto it = find(vertList.begin(), vertList.end(), vertex);
    if (it == vertList.end()) {
        cout << "������� �� �������" << endl;
        return;
    }
    int index = distance(vertList.begin(), it);
    vertList.erase(it);
    for (int i = index; i < vertList.size(); i++) {
        for (int j = 0; j < vertList.size(); j++) {
            adjMatrix[i][j] = adjMatrix[i + 1][j];
            adjMatrix[j][i] = adjMatrix[j][i + 1];
        }
    }
    for (int i = 0; i < vertList.size(); i++) {
        adjMatrix[vertList.size()][i] = 0;
        adjMatrix[i][vertList.size()] = 0;
    }
}
void Graph::dijkstra(int startVertex)
{
    int n = vertList.size();
    vector<int> distance(n, INT_MAX);
    vector<bool> visited(n, false);
    distance[startVertex] = 0; 
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, startVertex });
    while (!pq.empty()) {
        int currVertex = pq.top().second;
        pq.pop();
        if (visited[currVertex])
            continue;
        visited[currVertex] = true;
        for (int i = 0; i < n; i++) {
            if (adjMatrix[currVertex][i] != 0) {
                int nextVertex = i;
                int weight = adjMatrix[currVertex][i];
                if (!visited[nextVertex] && distance[currVertex] != INT_MAX && distance[currVertex] + weight < distance[nextVertex]) {
                    distance[nextVertex] = distance[currVertex] + weight;
                    pq.push({ distance[nextVertex], nextVertex });
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << "����� �������� ���� �� " << vertList[startVertex] << " �� " << vertList[i] << ": ";
        if (distance[i] == INT_MAX)
            cout << " ���� ��� ";
        else
            cout << distance[i];
        cout << endl;
    }
}
void Graph::BFS(int startVertex)
{
    if (isEmpty()) {
        cout << "���� ����" << endl;
        return;
    }
    int n = vertList.size();
    vector<bool> visited(n, false);
    queue<int> q;
    visited[startVertex] = true;
    q.push(startVertex);
    while (!q.empty()) {
        int currVertex = q.front();
        q.pop();
        cout << this->getVertText(currVertex)<<" ";

        for (int i = 0; i < n; i++) {
            if (adjMatrix[currVertex][i] != 0 && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    cout << endl;
}
void Graph::DFS(int startVertex) {
    if (isEmpty()) {
        cout << "���� ����" << endl;
        return;
    }
    int n = vertList.size();
    vector<bool> visited(n, false);
    cout << "����� � �������: ";
    dfsRec(visited, startVertex, vertList, adjMatrix);
    cout << endl;
}
void Graph::dfsRec(vector<bool>& visited, int currVertex, const vector<int>& vertList, int adjMatrix[][maxSize]) {
    visited[currVertex] = true;
    cout << this->getVertText(currVertex) << " ";
    for (int i = 0; i < vertList.size(); i++) {
        if (adjMatrix[currVertex][i] != 0 && !visited[i]) {
            dfsRec(visited, i, vertList, adjMatrix);
        }
    }
}
int Graph::komivoya(int startVertex,vector<int>& optimalPath)
{
    int n = vertList.size();
    vector<bool> visited(n, false);
    visited[startVertex] = true; 
    int pathLength = 0; 
    int minPathLength = INT_MAX;
    int currVertex = 0; 
    int level = 0; 
    komivoyaRec(currVertex, level, pathLength, minPathLength, visited, optimalPath);
    return minPathLength;
}
void Graph::komivoyaRec(int currVertex, int level, int pathLength, int& minPathLength, vector<bool>& visited, vector<int>& optimalPath)
{
    int n = vertList.size();

    // ���� ���������� ��������� �������
    if (level == n - 1) {
        if (adjMatrix[currVertex][0] != 0) { // ���������, ��� ���� ����� �� ��������� ������� � ���������
            int totalPathLength = pathLength + adjMatrix[currVertex][0]; // ����� ����� ����
            if (totalPathLength < minPathLength) {
                minPathLength = totalPathLength; // ��������� ����������� ����� ����
                optimalPath = visitedIndices(visited); // ���������� ����������� ����
            }
        }
        return;
    }

    // �������� �� ���� ��������
    for (int i = 0; i < n; i++) {
        if (!visited[i] && adjMatrix[currVertex][i] != 0) { // ���� ������� �� �������� � ���� �����
            visited[i] = true; // �������� �������
            komivoyaRec(i, level + 1, pathLength + adjMatrix[currVertex][i], minPathLength, visited, optimalPath); // ����������� ����� ��� ��������� �������
            visited[i] = false; // �������� ��������� ������� (��� ��������� ��������)
        }
    }
}
vector<int> Graph::visitedIndices(const vector<bool>& visited)
{
    vector<int> indices;
    for (int i = 0; i < visited.size(); i++) {
        if (visited[i]) {
            indices.push_back(i);
        }
    }
    return indices;
}
void menu()
{
    vector<int> komi;
    Graph graph;
    graph.insertVertex(1);
    graph.insertVertex(2);
    graph.insertVertex(3);
    graph.insertVertex(4);
    graph.insertVertex(5);
    graph.insertVertex(6);

    graph.insertEdgeWO(1, 2, 6);
    graph.insertEdgeWO(1, 3, 4);
    graph.insertEdgeWO(1, 4, 8);
    graph.insertEdgeWO(1, 5, 7);
    graph.insertEdgeWO(1, 6, 14);

    graph.insertEdgeWO(2, 3, 7);
    graph.insertEdgeWO(2, 4, 11);
    graph.insertEdgeWO(2, 5, 7);
    graph.insertEdgeWO(2, 6, 10);

    graph.insertEdgeWO(3, 4, 4);
    graph.insertEdgeWO(3, 5, 3);
    graph.insertEdgeWO(3, 6, 10);

    graph.insertEdgeWO(4, 5, 5);
    graph.insertEdgeWO(4, 6, 11);

    graph.insertEdgeWO(5, 6, 7);
    while (true)
    {
        cout << "1. ����� � ������ " << endl; //BFS
        cout << "2. ����� � ������� " << endl; //DFS
        cout << "3. �������� �������� " << endl; // dijkstra
        cout << "4. ������ ����������� " << endl;
        cout << "5. �������� ������� " << endl; //insertVertex
        cout << "6. ������� ������� " << endl;//eraseVertex
        cout << "7. ������ ������� " << endl; //print
        cout << "8. �������� ������������ ����� " << endl; //insertEdge
        cout << "9. ������� ����� " << endl; //eraseEdge
        int n, temp, temp1, temp2;
        bool f = true;
        cin >> n;
        switch (n)
        {
        case 1:
            graph.print();
            cout << " ������� ��������� ������� " << endl; cin >> temp2;
            temp = graph.getVertPos(temp2);
            if (temp != -1)
                graph.BFS(temp);
            break;
        case 2:
            graph.print();
            cout << " ������� ��������� ������� " << endl; cin >> temp2;
            temp = graph.getVertPos(temp2);
            if (temp != -1)
                graph.DFS(temp);
            break;
        case 3:
            graph.print();
            cout << " ������� ��������� ������� " << endl; cin >> temp2;
            temp = graph.getVertPos(temp2);
            if (temp != -1)
                graph.dijkstra(temp);
            break;
        case 4:
            graph.print();
            cout << " ������� ��������� ������� " << endl; cin >> temp2;
            temp = graph.getVertPos(temp2);
            temp1 = graph.komivoya(temp, komi);
            if (temp1 != -1) {
                cout << "����������� ����: ";
                for (int i = 0; i < komi.size(); i++) {
                    temp2 = komi[i]; cout << graph.getVertText(temp2) << " ";
                }
                temp2 = komi[temp];
                cout << graph.getVertText(temp) << endl;
                cout << "����� ����: " << temp1 << endl;
            }
            break;
        case 5:
            graph.print();
            while (f)
            {
                cout << "������� ����� ������� " << endl; cin >> temp;
                if (graph.getVertPos(temp) != -1) cout << " ��� ���� ������� � ����� ������� " << endl;
                else f = false;
            }
            graph.insertVertex(temp);
            f = true;
            break;
        case 6:
            graph.print();
            cout << "������� ����� ������� " << endl; cin >> temp;
            graph.eraseVertex(temp);
            break;
        case 7:
            graph.print();
            break;
        case 8:
            graph.print();
            cout << "������� ������ ������� "; cin >> temp;
            cout << "������� ������ ������� "; cin >> temp1;
            cout << "������� ��� ����� "; cin >> temp2;
            graph.insertEdge(temp, temp1, temp2);
            break;
        case 9:
            graph.print();
            cout << "������� ������ ������� "; cin >> temp;
            cout << "������� ������ ������� "; cin >> temp1;
            graph.eraseEdge(temp, temp1);
            break;
        default:
            cout << "�������� ����" << endl;
            break;
        }
        system("pause");
        system("cls");
    }
}
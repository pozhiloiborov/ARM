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
    bool isEmpty();//проверка на пустоту графа
    bool isFull();//проверка на заполненность
    int getVertText(int i);//получение номера вершины
    vector<int> getVertList();//получение списка вершин
    int getAdjMatrixElem(int i, int j);//получение элемента из матрицы
    int getAmountVerts();//получение количества вершин
    int getVertPos(const int& vertex);//получение позиции вершины
    int getAmountEdges();//получение количества ребер
    void changeWeight(int i, int j,int weight);//изменение веса ребра
    void insertVertex(const int& vertex);//добавление вершины
    void insertEdge(const int& vertex1, const int& vertex2, int weight);//добавление направленного ребра
    void insertEdgeWO(const int& vertex1, const int& vertex2, int weight);//добавление ненаправленного ребра
    void print();//печать матрицы
    void eraseEdge(const int& vertex1, const int& vertex2);//удаление ребра
    void eraseVertex(const int& vertex); //удаление вершины
    void dijkstra(int startVertex); // дейкстра
    void BFS(int startVertex); // обход в ширину
    void DFS(int startVertex); // обход в глубину
    void dfsRec(vector<bool>& visited, int currVertex, const vector<int>& vertList, int adjMatrix[][maxSize]); //рекурсия для обхода в глубину
    int komivoya(int startVertex,vector<int>& optimalPath); //решение задачи коммивояжёра
    void komivoyaRec(int currVertex, int level, int pathLength, int& minPathLength, vector<bool>& visited, vector<int>& optimalPath); // Вспомогательная рекурсивная функция для решения задачи коммивояжёра
    vector<int> visitedIndices(const vector<bool>& visited); // Вспомогательная функция для получения индексов посещенных вершин
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
        cout << "Лимит вершин достигнут" << endl;
        return;
    }
    vertList.push_back(vertex);
}
void Graph::insertEdge(const int& vertex1, const int& vertex2, int weight) {
    if (weight < 1) {
        cout << "Нельзя ввести значение меньше 1! " << endl;
        return;
    }
    if (getVertPos(vertex1) == -1 || getVertPos(vertex2) == -1) {
        cout << "Одной или обеих вершин не существует " << endl;
        return;
    }
    int vertPos1 = getVertPos(vertex1);
    int vertPos2 = getVertPos(vertex2);
    if (adjMatrix[vertPos1][vertPos2] != 0) {
        cout << " Ребро уже есть " << endl;
        return;
    }
    adjMatrix[vertPos1][vertPos2] = weight;
}
void Graph::insertEdgeWO(const int& vertex1, const int& vertex2, int weight) {
    if (weight < 1) {
        cout << "Нельзя ввести значение меньше 1! " << endl;
        return;
    }
    if (getVertPos(vertex1) == -1 || getVertPos(vertex2) == -1) {
        cout << "Одной или обеих вершин не существует " << endl;
        return;
    }
    int vertPos1 = getVertPos(vertex1);
    int vertPos2 = getVertPos(vertex2);
    if (adjMatrix[vertPos1][vertPos2] != 0) {
        cout << " Ребро уже есть " << endl;
        return;
    }
    adjMatrix[vertPos1][vertPos2] = weight;
    adjMatrix[vertPos2][vertPos1] = weight;
}
void Graph::print() {
    if (isEmpty()) {
        cout << "Граф пуст " << endl;
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
        cout << "Одной или обоих вершин не существует " << endl;
        return;
    }

    int vertPos1 = getVertPos(vertex1);
    int vertPos2 = getVertPos(vertex2);
    if (adjMatrix[vertPos1][vertPos2] == 0) {
        cout << " Ребра и так нету" << endl;
        return;
    }
    adjMatrix[vertPos1][vertPos2] = 0;
}
void Graph::eraseVertex(const int& vertex)
{
    auto it = find(vertList.begin(), vertList.end(), vertex);
    if (it == vertList.end()) {
        cout << "Вершина не найдена" << endl;
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
        cout << "Самый короткий путь из " << vertList[startVertex] << " до " << vertList[i] << ": ";
        if (distance[i] == INT_MAX)
            cout << " пути нет ";
        else
            cout << distance[i];
        cout << endl;
    }
}
void Graph::BFS(int startVertex)
{
    if (isEmpty()) {
        cout << "Граф пуст" << endl;
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
        cout << "Граф пуст" << endl;
        return;
    }
    int n = vertList.size();
    vector<bool> visited(n, false);
    cout << "Обход в глубину: ";
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

    // Если достигнута последняя вершина
    if (level == n - 1) {
        if (adjMatrix[currVertex][0] != 0) { // Проверяем, что есть ребро из последней вершины в начальную
            int totalPathLength = pathLength + adjMatrix[currVertex][0]; // Общая длина пути
            if (totalPathLength < minPathLength) {
                minPathLength = totalPathLength; // Обновляем минимальную длину пути
                optimalPath = visitedIndices(visited); // Запоминаем оптимальный путь
            }
        }
        return;
    }

    // Проходим по всем вершинам
    for (int i = 0; i < n; i++) {
        if (!visited[i] && adjMatrix[currVertex][i] != 0) { // Если вершина не посещена и есть ребро
            visited[i] = true; // Посещаем вершину
            komivoyaRec(i, level + 1, pathLength + adjMatrix[currVertex][i], minPathLength, visited, optimalPath); // Рекурсивный вызов для следующей вершины
            visited[i] = false; // Отменяем посещение вершины (для следующих итераций)
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
        cout << "1. Обход в ширину " << endl; //BFS
        cout << "2. Обход в глубину " << endl; //DFS
        cout << "3. Алгоритм Дейкстры " << endl; // dijkstra
        cout << "4. Задача коммивояжёра " << endl;
        cout << "5. Добавить вершину " << endl; //insertVertex
        cout << "6. Удалить вершину " << endl;//eraseVertex
        cout << "7. Печать матрицы " << endl; //print
        cout << "8. Добавить направленное ребро " << endl; //insertEdge
        cout << "9. Удалить ребро " << endl; //eraseEdge
        int n, temp, temp1, temp2;
        bool f = true;
        cin >> n;
        switch (n)
        {
        case 1:
            graph.print();
            cout << " Введите стартовую вершину " << endl; cin >> temp2;
            temp = graph.getVertPos(temp2);
            if (temp != -1)
                graph.BFS(temp);
            break;
        case 2:
            graph.print();
            cout << " Введите стартовую вершину " << endl; cin >> temp2;
            temp = graph.getVertPos(temp2);
            if (temp != -1)
                graph.DFS(temp);
            break;
        case 3:
            graph.print();
            cout << " Введите стартовую вершину " << endl; cin >> temp2;
            temp = graph.getVertPos(temp2);
            if (temp != -1)
                graph.dijkstra(temp);
            break;
        case 4:
            graph.print();
            cout << " Введите стартовую вершину " << endl; cin >> temp2;
            temp = graph.getVertPos(temp2);
            temp1 = graph.komivoya(temp, komi);
            if (temp1 != -1) {
                cout << "Оптимальный путь: ";
                for (int i = 0; i < komi.size(); i++) {
                    temp2 = komi[i]; cout << graph.getVertText(temp2) << " ";
                }
                temp2 = komi[temp];
                cout << graph.getVertText(temp) << endl;
                cout << "Длина пути: " << temp1 << endl;
            }
            break;
        case 5:
            graph.print();
            while (f)
            {
                cout << "Введите номер вершины " << endl; cin >> temp;
                if (graph.getVertPos(temp) != -1) cout << " уже есть вершина с таким номером " << endl;
                else f = false;
            }
            graph.insertVertex(temp);
            f = true;
            break;
        case 6:
            graph.print();
            cout << "Введите номер вершины " << endl; cin >> temp;
            graph.eraseVertex(temp);
            break;
        case 7:
            graph.print();
            break;
        case 8:
            graph.print();
            cout << "Введите первую вершину "; cin >> temp;
            cout << "Введите вторую вершину "; cin >> temp1;
            cout << "Введите вес ребра "; cin >> temp2;
            graph.insertEdge(temp, temp1, temp2);
            break;
        case 9:
            graph.print();
            cout << "Введите первую вершину "; cin >> temp;
            cout << "Введите вторую вершину "; cin >> temp1;
            graph.eraseEdge(temp, temp1);
            break;
        default:
            cout << "Неверный ввод" << endl;
            break;
        }
        system("pause");
        system("cls");
    }
}
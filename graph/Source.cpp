#include "graph.h"
struct vertCoord {
    int x, y;
};
int WinW = 800;
int WinH = 800;
vertCoord vertC[maxSize];
Graph graph;
int R = 50;
vector<int> komivoyaPath;
using namespace std;
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
void Graph::getAdjMatrix(int(&matrix)[maxSize][maxSize])
{
    for (int i = 0; i < maxSize; i++) {
        for (int j = 0; j < maxSize; j++) {
            matrix[i][j] = adjMatrix[i][j];
        }
    }
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
void Graph::changeWeight(int i, int j, int weight) {
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
            cout << adjMatrix[i][j] << "  ";
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
        cout << this->getVertText(currVertex) << " ";
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
void Graph::drawGraph() {
    int n = getAmountVerts();
    for (int i = 0; i < n; i++) {
        setCoords(i, n);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int a = adjMatrix[i][j];
            if (a == 0)
                continue; 
            bool isPath = false;
            drawLine(a, vertC[i].x, vertC[i].y, vertC[j].x, vertC[j].y, j, i,isPath);
        }
    }
    drawVertex(n);
    glutPostRedisplay();
}
int Graph::komivoya(int startVertex, vector<int>& optimalPath)
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

    if (level == n - 1) {
        if (adjMatrix[currVertex][0] != 0) { 
            int totalPathLength = pathLength + adjMatrix[currVertex][0];
            if (totalPathLength < minPathLength) {
                minPathLength = totalPathLength; 
                optimalPath = visitedIndices(visited);
            }
        }
        return;
    }

    // Ïðîõîäèì ïî âñåì âåðøèíàì
    for (int i = 0; i < n; i++) {
        if (!visited[i] && adjMatrix[currVertex][i] != 0) {
            visited[i] = true; 
            komivoyaRec(i, level + 1, pathLength + adjMatrix[currVertex][i], minPathLength, visited, optimalPath);
            visited[i] = false;
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
void makegraph()
{
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
    
    /*graph.insertVertex(1);
    graph.insertVertex(2);
    graph.insertVertex(3);
    graph.insertVertex(4);
    graph.insertVertex(5);
    graph.insertVertex(6);
    graph.insertEdge(1, 2, 10);
    graph.insertEdge(2,3, 10);
    graph.insertEdge(3, 4, 10);
    graph.insertEdge(4, 5, 10);
    graph.insertEdge(5, 6, 10);
    graph.insertEdge(6, 1, 10);*/
}
void menu()
{
    while (true)
    {
        cout << "1. Обход в ширину " << endl; //BFS
        cout << "2. Обход в глубину " << endl; //DFS
        cout << "3. Алгоритм Дейкстры " << endl; // dijkstra
        cout << "4. Задача коммивояжёра " << endl; //komivoya
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
            if (temp != -1)
            {
                temp1 = graph.komivoya(temp, komivoyaPath);
               cout << "Оптимальный путь: ";
                for (int vertex : komivoyaPath) {
                    std::cout << vertex << " ";
                }
                temp2 = komivoyaPath[temp];
                cout << graph.getVertText(temp) << endl;
                cout << " длина пути " << temp1 << endl;
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
void drawText(int text, int x1, int y1,bool f) {
    if (f) glColor3f(0.0f, 0.0f, 1.0f);//синий для веса ребра
    else glColor3f(0.0f, 0.0f, 0.0f);//черный для номера вершины
    GLvoid* font = GLUT_BITMAP_TIMES_ROMAN_24;
    string s = to_string(text);
    glRasterPos2i(x1 - 5, y1 - 5);
    for (size_t j = 0; j < s.length(); j++)
        glutBitmapCharacter(font, s[j]);
}
void drawLine(int text, int x0, int y0, int x1, int y1, int start, int end,bool f) {
    if (f) glColor3f(1.0, 0.0, 0.0);
    else glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2i(x0, y0);
    glVertex2i(x1, y1);
    glEnd();
    int textX = (x1 - x0) / 4 + x0; 
    int textY = (y1 - y0) / 4 + y0; 
    drawText(text, textX, textY,true); // вес ребра у начала стрелки
    if (f) glColor3f(1.0, 0.0, 0.0);
    else glColor3f(0.0, 0.0, 0.0);
    float vx = x0 - x1;
    float vy = y0 - y1;
    float s = 1.0f / sqrt(vx * vx + vy * vy);
    vx *= s;
    vy *= s;
    x1 = x1 + R * vx;
    y1 = y1 + R * vy;
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x1 + 10 * (vx + vy), y1 + 10 * (vy - vx));//стрелки
    glVertex2f(x1 + 10 * (vx - vy), y1 + 10 * (vy + vx));
    glEnd();
}
void setCoords(int i, int n) {
    int R_;
    int x0 = WinW / 2;
    int y0 = WinH / 2;
    R = 5 * (WinW / 13) / n;
    R_ = WinW / 2 - R - 10;
    float theta = 2.0f * 3.1415926f * i / n;
    int x1 = R_ * sin(theta) + x0;
    int y1 = R_ * cos(theta) + y0;
    vertC[i].x = x1;
    vertC[i].y = y1;
}
void drawVertex(int n) {
    for (int i = 0; i < n; i++) {
        drawCircle(vertC[i].x, vertC[i].y, R);
        glColor3f(0.0f, 0.0f, 0.0f);
        drawText(graph.getVertText(i), vertC[i].x, vertC[i].y,false);
    }
}
void display() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WinW, 0, WinH);
    glViewport(0, 0, WinW, WinH);
    glClear(GL_COLOR_BUFFER_BIT);
    graph.drawGraph();
    glutSwapBuffers();
}
void drawCircle(int x, int y, int R) {
    glColor3f(1.0f, 1.0f, 1.0f);
    float x1, y1;
    glBegin(GL_POLYGON); // Начинаем рисование многоугольника (окружности).
    for (int i = 0; i < 360; i++) { // Итерируемся по углам от 0 до 360 градусов.
        float theta = 2.0f * 3.1415926f * float(i) / float(360); // Вычисляем угол в радианах.
        x1 = R * sin(theta) + x; // Вычисляем координату x текущей точки окружности.
        y1 = R * cos(theta) + y; // Вычисляем координату y текущей точки окружности.
        glVertex2f(x1, y1); // Устанавливаем точку в текущих координатах.
    }
    glEnd(); // Завершаем рисование многоугольника (окружности).
    glColor3f(0.0f, 0.0f, 0.0f);
    float x2, y2;
    glBegin(GL_LINE_LOOP); // Начинаем рисование линии контура окружности.
    for (int i = 0; i < 360; i++) { // Итерируемся по углам от 0 до 360 градусов.
        float theta = 2.0f * 3.1415926f * float(i) / float(360); // Вычисляем угол в радианах.
        x2 = R * sin(theta) + x; // Вычисляем координату x текущей точки контура окружности.
        y2 = R * cos(theta) + y; // Вычисляем координату y текущей точки контура окружности.
        glVertex2f(x2, y2); // Устанавливаем точку в текущих координатах.
    }
    glEnd(); // Завершаем рисование линии контура окружности.
}
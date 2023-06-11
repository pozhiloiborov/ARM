#include "graph.h"
struct vertCoord {
    int x, y;
};
int WinW = 800;
int WinH = 800;
vertCoord coord[maxSize];
Graph graph;
int R = 50;
vector<pair<int, int>> RightWay;
bool komivoya;
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
            if (komivoya)
            for (int k = 0; k < RightWay.size();k++) if ((getVertPos(RightWay[k].first) == i) && (getVertPos(RightWay[k].second) == j)) {
                isPath = true;
                break;
            }
            drawLine(a, coord[i].x, coord[i].y, coord[j].x, coord[j].y, j, i,isPath);
        }
    }
    drawVertex(n);
    glutPostRedisplay();
}
int** get_Matrix() {
    int n = graph.getAmountVerts();
    int** m = new int* [n];
    for (int i = 0; i < n; i++)
        m[i] = new int[n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int element = graph.getAdjMatrixElem(i, j);
            if (element == 0 || i == j)
                m[i][j] = -1;
            else
                m[i][j] = element;
        }
    }
    return m;
}
int* searchMinElem(int* line, int n) {
    int min = INT_MAX;
    for (int j = 0; j < n; j++)
        if (line[j] >= 0 && line[j] < min)
            min = line[j];

    for (int j = 0; j < n; ++j)
        if (line[j] >= 0)
            line[j] -= min;
    return line;
}
int** reductMatrix(int** oldm) {
    int** m = oldm;
    int n = graph.getAmountVerts();
    for (int i = 0; i < n; i++)
        m[i] = searchMinElem(m[i], n);
    for (int i = 0; i < n; i++) {
        int min = 10000000;
        for (int j = 0; j < n; j++) {
            if (m[j][i] >= 0 && m[i][j] < min)
                min = m[j][i];
        }
        for (int j = 0; j < n; j++) {
            if (m[j][i] >= 0)
                m[j][i] -= min;
        }
    }
    return m;
}
int** highZero(int** oldm) {
    int n = graph.getAmountVerts();
    int** m = reductMatrix(oldm);
    int max = -1;
    int i_line = 0, j_line = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (m[i][j] == 0)
            {
                int mini_line = 10000000;
                int minj_line = 10000000;
                for (int k = 0; k < n; k++) {
                    if (m[i][k] == -1 || k == j || m[i][k] >= mini_line)
                        break;

                    mini_line = m[i][k];
                }
                for (int k = 0; k < n; k++) {
                    if (m[k][j] == -1 || k == i || m[k][j] >= minj_line)
                        break;

                    minj_line = m[k][j];
                }

                if (max < minj_line + mini_line) {
                    max = minj_line + mini_line;
                    i_line = i;
                    j_line = j;
                }
            }
        }
    }
    pair<int, int> p;
    p.first = i_line + 1;
    p.second = j_line + 1;
    RightWay.push_back(p);
    m[i_line][j_line] = -1;
    m[j_line][i_line] = -1;
    for (int i = 0; i < n; i++) {
        m[i_line][i] = -1;
        m[i][j_line] = -1;
    }
    cout << endl;
    cout << " Найденные пути " << endl;
    for (int i = 0; i < RightWay.size(); i++)
        cout << RightWay[i].first << " -> " << RightWay[i].second << "    ";
    cout << endl;
    return m;
}
void printResult() {
    int sum = 0;
    for (int i = 0; i < RightWay.size(); i++) {
        int i_line = RightWay[i].first - 1;
        int j_line = RightWay[i].second - 1;
        sum += graph.getAdjMatrixElem(i_line, j_line);
    }
    cout << endl << "Длина пути " << sum << endl;
}
void makegraph()
{
    graph.insertVertex(1);
    graph.insertVertex(2);
    graph.insertVertex(3);
    graph.insertVertex(4);
    graph.insertVertex(5);
    graph.insertVertex(6);
    graph.insertEdge(1, 2, 6);
    graph.insertEdge(1, 3, 4);
    graph.insertEdge(1, 4, 8);
    graph.insertEdge(1, 5, 7);
    graph.insertEdge(1, 6, 14);
    graph.insertEdge(2, 3, 7);
    graph.insertEdge(2, 4, 11);
    graph.insertEdge(2, 5, 7);;
    graph.insertEdge(2, 6, 10);
    graph.insertEdge(3, 4, 4);
    graph.insertEdge(3, 5, 3);
    graph.insertEdge(3, 6, 10);
    graph.insertEdge(4, 5, 5);
    graph.insertEdge(4, 6, 11);
    graph.insertEdge(5, 6, 7);
    graph.insertEdge(6, 1, 8);
};
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
        int** matrix;
        komivoya = false;
        RightWay.clear();
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
            komivoya = true;
            matrix = get_Matrix();
            temp = graph.getAmountVerts();
            while (RightWay.size() < temp) {
                matrix = highZero(matrix);
            }
            cout << endl;
            printResult();
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
    if (f) glColor3f(1.0, 0.0, 0.0);// if true draw komivoyager path
    else glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2i(x0, y0);
    glVertex2i(x1, y1);
    glEnd();
    int textX = (x1 - x0) / 4 + x0; 
    int textY = (y1 - y0) / 4 + y0; 
    drawText(text, textX, textY,true); // вес ребра у начала стрелки
    if (f) glColor3f(1.0, 0.0, 0.0);// if true draw komivoyager path
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
    int Rcalc;
    int x0 = WinW / 2;
    int y0 = WinH / 2;
    R = 5 * (WinW / 13) / n;
    Rcalc = WinW / 2 - R - 10;
    float theta = 2.0f * 3.1415926f * i / n;
    int x1 = Rcalc * sin(theta) + x0;
    int y1 = Rcalc * cos(theta) + y0;
    coord[i].x = x1;
    coord[i].y = y1;
}
void drawVertex(int n) {
    for (int i = 0; i < n; i++) {
        drawCircle(coord[i].x, coord[i].y, R);
        glColor3f(0.0f, 0.0f, 0.0f);
        drawText(graph.getVertText(i), coord[i].x, coord[i].y,false);
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
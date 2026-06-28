#include <iostream>

using namespace std;

// функция для задачи А: список ребер -> матрица смежности
void za(){
    int n, m;          // количество вершин и ребер
    int i, j;          // счетчики
    int u, v;          // номера вершин ребра
    int adj[101][101]; // матрица смежности, максимум 100 вершин

    cin >> n >> m;

    // заполняем матрицу нулями
    for (i = 1; i <= n; i += 1) {
        for (j = 1; j <= n; j += 1) {
            adj[i][j] = 0;
        }
    }

    // читаем ребра и ставим 1
    for (i = 1; i <= m; i += 1) {
        cin >> u >> v;
        adj[u][v] = 1;
    }

    // выводим матрицу
    for (i = 1; i <= n; i += 1) {
        for (j = 1; j <= n; j += 1) {
            cout << adj[i][j];
            if (j != n) cout << ' '; // пробел между числами
        }
        cout << endl; // переход на новую строку
    }
}

void zb(){
    int n, m, i, u, v;
    int deg[101]; // степени вершин, макс 100
    cin >> n >> m;
    // обнуляем степени
    for (i = 1; i <= n; i = i + 1) {
        deg[i] = 0;
    }
    // читаем рёбра и увеличиваем степени
    for (i = 1; i <= m; i = i + 1) {
        cin >> u >> v;
        deg[u] = deg[u] + 1;
        deg[v] = deg[v] + 1;
    }
    // выводим степени
    for (i = 1; i <= n; i = i + 1) {
        cout << deg[i];
        if (i != n) cout << ' ';
    }
    cout << endl;
}

void zc(){
    int n, s, i, j;
    int adj[101][101];
    bool visited[101];
    int stack[101];
    int top, count, v, u;

    cin >> n >> s;

    for (i = 1; i <= n; i = i + 1) {
        for (j = 1; j <= n; j = j + 1) {
            cin >> adj[i][j];
        }
    }

    for (i = 1; i <= n; i = i + 1) {
        visited[i] = false;
    }

    top = 0;
    stack[top] = s;
    top = top + 1;
    visited[s] = true;
    count = 0;

    while (top != 0) {
        top = top - 1;
        v = stack[top];
        count = count + 1;

        for (u = 1; u <= n; u = u + 1) {
            if (adj[v][u] == 1 and visited[u] == false) {
                visited[u] = true;
                stack[top] = u;
                top = top + 1;
            }
        }
    }

    cout << count << endl;
}

int main(){
    //za();
    //zb();
    //zc();
    return 0;
}
#include <iostream>

using namespace std;

void za(){
    int a= 1, b= 1, c, i, n;
    cin >> n;
    if (n == 1 or n == 2) {
        cout << 1 << endl;
        return;
    }
    for (i = 3; i <= n; i += 1) {
        c = a + b;
        a = b;
        b = c;
    }
    cout << b << endl;
}

void zb(){
    int n, i, cost[101], dp[101];
    cin >> n;
    for (i = 1; i <= n; i += 1) {
        cin >> cost[i];
    }
    if (n == 1) {
        cout << cost[1] << endl;
        return;
    }
    dp[1] = cost[1];
    dp[2] = cost[2];
    for (i = 3; i <= n; i += 1) {
        if (dp[i - 1] < dp[i - 2]) {
            dp[i] = cost[i] + dp[i - 1];
        } else {
            dp[i] = cost[i] + dp[i - 2];
        }
    }
    cout << dp[n] << endl;
}

void zc(){
    int n, m, i, j; // размеры таблицы
    int a[101][101]; // исходные числа
    int dp[101][101]; // макс суммы до клетки
    int dir[101][101]; // откуда пришли: 0 - сверху, 1 - слева
    cin >> n >> m;
    // считываем таблицу
    for (i = 1; i <= n; i += 1) {
        for (j = 1; j <= m; j += 1) {
            cin >> a[i][j];
        }
    }
    // начальная клетка
    dp[1][1] = a[1][1];
    // заполняем первую строку - только справа
    for (j = 2; j <= m; j += 1) {
        dp[1][j] = dp[1][j-1] + a[1][j];
        dir[1][j] = 1; // пришли слева
    }
    // заполняем первый столбец - только сверху
    for (i = 2; i <= n; i += 1) {
        dp[i][1] = dp[i-1][1] + a[i][1];
        dir[i][1] = 0; // пришли сверху
    }
    // для всех остальных клеток выбираем лучший путь
    for (i = 2; i <= n; i += 1) {
        for (j = 2; j <= m; j += 1) {
            int from_top = dp[i-1][j];
            int from_left = dp[i][j-1];
            if (from_top >= from_left) {
                dp[i][j] = from_top + a[i][j];
                dir[i][j] = 0; // сверху выгодней
            } else {
                dp[i][j] = from_left + a[i][j];
                dir[i][j] = 1; // слева выгодней
            }
        }
    }
    // выводим максимальную сумму
    cout << dp[n][m] << endl;
    // восстанавливаем путь
    char route[205]; // максимум 199 шагов + 1
    int len = 0;
    i = n;
    j = m;
    while (i != 1 or j != 1) {
        if (dir[i][j] == 0) { // шли сверху
            route[len] = 'D';
            len += 1;
            i -= 1;
        } else { // шли слева
            route[len] = 'R';
            len += 1;
            j -= 1;
        }
    }
    // выводим маршрут задом наперед
    for (int k = len - 1; k >= 0; k -= 1) {
        cout << route[k];
        if (k != 0) cout << ' ';
    }
    cout << endl;
}

int main(){
    //za();
    //zb();
    //zc();
    return 0;
}
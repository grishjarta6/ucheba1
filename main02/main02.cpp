#include <iostream>
#include <cmath> //используеться для модулей
using namespace std;

//if
void task_1_1() {
    int a, b;
    cin >> a >> b;
    if (a == b) {
        cout << b << a << endl;
    }
}

void task_1_2() {
    int a, b;
    cin >> a >> b;
    if (a == b) {
        cout << a + 1 << " " << b + 2 << endl;
    }
    else {
        cout << a << " " << b << endl;
    }
}
void task_1_3() {
    int a;
    cin >> a;
    if (a >= 0) {
        cout << a + 1 << endl;

    }
    else {
        cout << a << endl;
    }
}
void task_1_4() {
    int s;
    cin >> s;
    if (s == 0) {
        cout << "LOSE" << endl;
    }
    if (s == 1) {
        cout << "DRAW" << endl;
    }
    if (s == 3) {
        cout << "WIN" << endl;
    }
    else {
        cout << "no";
    }
}
void task_1_5() {
    int a, b, c;
    cin >> a >> b >> c;
    if (a > 0) {
        a = a * a;
    }
    if (b > 0) {
        b = b * b;
    }
    if (c > 0) {
        c = c * c;
    }
    cout << a << " " << b << " " << c << endl;

}
void task_1_6() {
    int a, b, c;
    cin >> a >> b >> c;
    int tmp = 0;
    if (a > 0) {
        tmp += a;
    }
    if (b > 0) {
        tmp += b;
    }
    if (c > 0) {
        tmp += c;
    }
    cout << tmp << endl;

}
void task_1_7() {
    int a, b, c;
    cin >> a >> b >> c;
    if (a > b) {
        if (a > c) {
            cout << a - 5 << b << c;
        }
    }
    if (b > a) {
        if (b > c) {
            cout << a << b - 5 << c;
        }
    }
    if (c > a) {
        if (c > b) {
            cout << a << b << c - 5;
        }
    }
}

void task_1_8() {
    int a, b, c;
    cin >> a >> b >> c;
    if ((a < b) and (b < c)) {
        cout << a * a << " " << b * b << " " << c * c << endl;
    }
    if ((a > b) and (b > c)) {
        cout << a << " " << a << " " << a << endl;
    }
    if (not(((a < b) and (b < c)) or ((a > b) and (b > c)))) {
        cout << a * (-1) << " " << b * (-1) << " " << c * (-1) << endl;
    }
}

void task_1_9() {
    int n, m, nn, mm;
    cin >> n >> m;
    nn = n;
    mm = m;
    if (n < 0) {
        nn = n * -1;
        if (m < 0) {
            mm = m * -1;
            if (nn > mm) {
                cout << n - 100 << " " << m << endl;
            }
            else {
                cout << n << " " << m << endl;
            }
        }
        else {
            if (nn > mm) {
                cout << n - 100 << " " << m << endl;
            }
            else {
                cout << n << " " << m << endl;
            }
        }
        }
    else {
        if (m < 0) {
            mm = m * -1;
            if (nn > mm) {
                cout << n - 100 << " " << m << endl;
            }
            else {
                cout << n << " " << m << endl;
            }
        }
        else {
            if (nn > mm) {
                cout << n - 100 << " " << m << endl;
            }
            else {
                cout << n << " " << m << endl;
            }
        }
    }
    }
    
void task_1_10() {
    int n, m, x, y;
    cin >> n >> m >> x >> y;
    int ans = x;
    if (n - x < ans) ans = n - x;
    if (y < ans) ans = y;
    if (m - y < ans) ans = m - y;
    cout << ans << endl;
}

//if else
void task_2_1() {
    int n;
    cin >> n;
    if ((n > 999) and (n % 5 == 0)) cout << "FAILURE" << endl;
    else cout << "SUCCESS" << endl;
}

void task_2_2() {
    int n, m;
    cin >> n >> m;
    if (n < m) {
        cout << 1 << endl;
    }
    else {
        cout << 2 << endl;
    }
}
void task_2_3() {
    int a, b, c;
    cin >> a >> b >> c;
    if ((a == b) and (b == c)) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
}
void task_2_4() {
    int a, b, c;
    cin >> a >> b >> c;
    if ((abs(a) == abs(b)) and (abs(b) == abs(c))) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
}

//bool

void task_3_1() {
    int b;
    cin >> b;
    if (abs(b) % 2 == 0) {
        cout << "1" << endl;
    }
    else {
        cout << "0" << endl;
    }
}

void task_3_2() {
    int b;
    cin >> b;
    if (abs(b) % 2 != 0) {
        cout << "1" << endl;
    }
    else {
        cout << "0" << endl;
    }
}

void task_3_3() {
    int x;
    cin >> x;
    if (x >= 150) {
        cout << "1" << endl;
    }
    else {
        cout << "0" << endl;
    }
}

void task_3_4() {
    int a, b, c;
    cin >> a >> b >> c;
    if ((abs(a) % 2 == 0) and (abs(b) % 2 == 0) and (abs(a) % 2 == 0)) {
        cout << "0";
    }
    else {
        cout << "1" << endl;
    }
}

void task_3_5() {
    int h;
    cin >> h;
    if (h >= 8 and h < 11) {
        cout << "1" << endl;
    }
    if (h >= 11 and h < 18) {
        cout << "2" << endl;
    }
    else {
        cout << "3" << endl;
    }
}

void task_3_6() {
    int a, b;
    cin >> a >> b;
    if ((a > 23) or (b > 59)) {
        cout << "0" << endl;
    }
    else {
        cout << "1" << endl;
    }
}

void task_3_7() {
    int x, y;
    cin >> x;
    cin >> y;
    if ((x > 1) and (x < 4) and (y < 7) and (y > 2)) {
        cout << "1" << endl;
    }
    else {
        cout << "0" << endl;
    }
}

void task_1_9_2() {
    int n, m, nn, mm;
    cin >> n >> m;
    if ((n < 0)) {
        nn = n * -1;
    }
    if (m < 0) {
        mm = m * -1;
    }
    if (nn > mm) {
        cout << n - 100 << " " << m << endl;
    }
    else {
        cout << n << " " << m << endl;
    }
}

void task_3_1_1() {
    int b;
    cin >> b;
    cout << (abs(b) % 2 == 0);
    if (abs(b) % 2 == 0) {
        cout << "1" << endl;
    }
    else {
        cout << "0" << endl;
    }
}

void ts1() {
    int n;
    bool a, b;
    cin >> n;
    a = (n > 0) ? 1 : 0;
    if (a == 1) {
        b = (n % 2) ? 1 : 0;
        cout << b;
    }
    else {
        n = -n;
        b = (n % 2) ? 1 : 0;
        cout << b;
    }
}


int main() {

    // task_1_1();
    // task_1_2();
    // task_1_3();
    // task_1_4();
    // task_1_5();
    // task_1_6();
    // task_1_7();
    //task_1_8();
    // task_1_9();
    // task_1_10();
    // task_2_1();
    // task_2_2();
    // task_2_3();
    // task_2_4();
    // task_3_1();
    // task_3_3();
    // task_3_4();
    // task_3_5();

    return 0;
}
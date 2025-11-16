#include <iostream>
#include <string>

using namespace std;

//switch for03 задания 1.1
void ts1() {
    int n;
    cin >> n;
    switch (n) {
    case 1:
        cout << "GOLD" << endl;
        break;
    case 2:
        cout << "SILVER" << endl;
        // break;
    case 3:
        cout << "BRONZE" << endl;
        break;
    default:
        cout << "NO MEDAL" << endl;
        break;
    }
}
//switch for задание 1.2
void ts2() {
    int n;
    cin >> n;
    switch (n) {
    case 1:
        cout << "ciclop";
        break;
    case 2:
        cout << "human";
        break;
    default:
        cout << "multi";
        break;
    }

}
//switch for задание 1.3
void ts3() {
    int n;
    cin >> n;
    switch (n) {
    case 5:
        cout << "ex";
        break;
    case 4:
        cout << "g";
        break;
    case 3:
        cout << "sat";
        break;
    case 2:
        cout << "lts";
        break;
    case 1:
        cout << "v p";
        break;
    default:
        cout << "error";
        break;
    }
}
// switch for задание 1.4
void ts4() {
    int n;
    cin >> n;
    switch (n) {
    case 1:
        cout << "mon";
        break;
    case 2:
        cout << "tus";
        break;
    case 3:
        cout << "wed";
        break;
    case 4:
        cout << "thu";
        break;
    case 5:
        cout << "fri";
        break;
    case 6:
        cout << "sat";
        break;
    case 7:
        cout << "sun";
        break;
    default:
        cout << "error";
        break;
    }
}
//switch for задание 1.5
void ts5() {
    int m;
    cin >> m;

    switch (m) {
    case 12:
    case 1:
    case 2:
        cout << "WINTER" << endl;
        break;
    case 3:
    case 4:
    case 5:
        cout << "SPRING" << endl;
        break;
    case 6:
    case 7:
    case 8:
        cout << "SUMMER" << endl;
        break;
    case 9:
    case 10:
    case 11:
        cout << "AUTUMN" << endl;
        break;
    default:
        cout << "NO SEASON" << endl;
        break;
    }
}
//switch for задание 1.6
void ts6() {
    int t;
    cin >> t;
    int cycle_position = t % 6;

    switch (cycle_position) {
    case 0:
    case 1:
    case 2:
        cout << "GREEN" << endl;
        break;
    case 3:
        cout << "YELLOW" << endl;
        break;
    case 4:
    case 5:
        cout << "RED" << endl;
        break;
    }

}
//тренарные операцие 2.3
void trrr1() {
    int a, b;
    cin >> a >> b;
    int max = (a > b) ? a : b;
    cout << max << endl;

}
//тренарные операцие 2.4
void ts7() {
    int a, b, c;
    std::string t = "yes";
    std::string f = "no";
    cin >> a >> b >> c;
    int m1 = (a > b) ? a : b;
    int m2 = (b > c) ? b : c;
    int m = (m1 > m2) ? m1 : m2;
    int min1 = (a < b) ? a : b;
    int min2 = (b < c) ? b : c;

    //тесты
    //int min = (min1 < min2) ? min1 : min2;
    //cout << m << endl << min;

    int d = (min1 + min2) * 2;
    std::string an = (d < m) ? t : f;
    cout << an;
}


//тренарные операцие 2.5
void ts8() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    // ч=1 б=2
    int ag = (a % 2 == 0) ? 1 : 0;
    int bg = (b % 2 == 0) ? 1 : 0;
    int g1 = ((ag + bg) % 2 == 0) ? 1 : 0;
    int cg = (a % 2 == 0) ? 1 : 0;
    int dg = (b % 2 == 0) ? 1 : 0;
    int g2 = ((cg + dg) % 2 == 0) ? 1 : 0;
    cout << ((g1 == g2) ? "yes" : "no");
}

//тренарные операцие 2.6
void ts9() {
    int n, m, k;
    std::string t = "yes", f = "no", an;
    cin >> n >> m >> k;
    //s = n * m;
    //an = (s - k == 0) ? t : f;
    //cout << an;
    bool q11 = (n <= k) ? 1 : 0;
    bool q12 = (m >= (k - n) or n == k) ? 1 : 0;
    bool q1 = (q11 and q12) ? 1 : 0;
    bool q21 = (m <= k) ? 1 : 0;
    bool q22 = (n >= (k - m) or m == k) ? 1 : 0;
    bool q2 = (q21 and q22) ? 1 : 0;
    an = (q1 or q2) ? t : f;
    cout << an;
}

// for 1.1
void ts10() {
    int n, i;
    cin >> n;
    std::string num = "number of pigs: ";
    for (i = 1; i <= n; i += 1) {
        cout << num << i << endl;
    }
}
// for 1.2
void ts11() {
    int n, i;
    cin >> n;
    for (i = 1; i <= n; i += 1) {
        cout << "[_]";
    }
}
// for 1.3
void ts12() {
    int n, i;
    cin >> n;
    for (i = 1; i < n; i += 1) {
        cout << i << " ";
    }
}
// for 1.4
void ts13() {
    int x, n, i;
    cin >> x >> n;
    for (i = 1; i <= n; i += 1) {
        x = x * 2;
    }
    cout << x;
}
// for 1.5
void ts14() {
    int x, n = 50, i;
    cin >> x;
    i = x;
    for (i; i >= n; i = i - 5) {
        cout << i << endl;
    }
}
// for 1.6
void ts15() {
    int n, i, an = 0;
    cin >> n;
    for (i = 1; i <= n; i += 1) {
        an = an + i;
        //cout << an << endl;
    }
    cout << an << endl;
}
// for 1.7
void ts16() {
    int n, i;
    cin >> n;
    for (i = 1; i <= n; i++) {
        if (n % i == 0) {
            cout << i;
        }
    }
}
//for 1.8
void ts17() {
    int k, n, i, an = 0, c = 0;
    cin >> n;
    for (i = 1; i <= n; i++) {
        cout << "torg" << i;
        cin >> k;
        if (k >= 1000) {
            an = an + k;
            c += 1;
        }
    }
    cout << c << endl << an << endl;
}
//for 1.8
void ts18() {
    int n, p, i, c = 0, pr = 0, nott = 0, ub = 0;
    cin >> n;
    for (i = 1; i <= n; i++) {
        cin >> p;
        if (p > 0) {
            pr += 1;
        }
        if (p == 0) {
            nott += 1;
        }
        if (p < 0) {
            ub += 1;
        }
        c = c + p;
    }
    cout << pr << " " << nott << " " << ub << endl;
    cout << c;
}
// for 1.9
void ts19() {
    int n, a, d, ao = 0, dol = 0, i, c = 0;
    cin >> n;
    for (i = 1; i <= n; i++) {
        cout << i << " age " << "dengi ";
        cin >> a >> d;
        if (a >= 12) {
            if ((a >= ao) or ((dol - d) <= 130000)) {
                c = i;
                ao = a;
                dol = d;
            }
        }

    }
    cout << "answer " << c;
}

int main() {
    //ts1();
    //ts2();
    //ts3();
    //ts4();
    //ts5();
    //ts6();
    //trrr1();
    //ts7();
    //ts8();
    //ts9();
    //ts10();
    //ts11();
    //ts12();
    //ts13();
    //ts14();
    //ts15();
    //ts16();
    //ts17();
    //ts18();
    ts19();
    //[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
    return 0;
    //комит с планшета
}
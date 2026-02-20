#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
using namespace std;

int fac(int n) {
    if (n <= 1) {
        return 1;
    }
    else {
        return n * fac(n - 1);
    }
}

void ts1() {
    int x;
    cin >> x;
    cout << fac(x);
}

int cd(int n) {
    if (n < 10) {
        return 1;
    }
    else {
        return 1 + cd(n / 10);
    }
}

void ts2() {
    int x;
    cin >> x;
    cout << cd(x);
}

int sd(int n) {
    if (n < 10) {
        return n;
    }
    else {
        return (n % 10) + sd(n / 10);
    }
}

void ts3() {
    int x;
    cin >> x;
    cout << sd(x);

}

int ts41(int n) {
    if (n < 10) {
        return n;
    }
    else {
        return (n % 10) + sd(n / 10);
    }
}

int ts42(int a) {
    int s;
    s = ts41(a);
    if (s < 10) { return s;}
    else {
        return ts41(s);
    }
}

void ts4() {
    int x;
    cin >> x;
    cout << ts42(x);
}

void ts5() {
    //я не понял
}

int ts61(int a, int b) {
    b += 1;
    if ((a % b == 0) and (b != a)) {
        return 0;
    }
    if (a == b) {
        return 1;
    }
    else {
        ts61(a, b);
    }
}

void ts6() {
    int x, q = 1, a;
    cin >> x;
    a = ts61(x, q);
    if (a == 1) { cout << "yes"; }
    else {cout << "no";}
}

void ts71(int n) {
    if (n > 1) {
        ts71(n / 2);
    }
    cout << (n % 2);
}


void ts7() {
    int x;
    cin >> x;
    if (x == 0) { cout << 0; }
    else { ts71(x); }
}

int ts81(int n) {
    if (n == 1 or n == 2) {
        return 1;
    }
    else {
        return ts81(n - 1) + ts81(n - 2);
    }
}

void ts8() {
    int x;
    cin >> x;
    cout << ts81(x);
}

void ts91(int n) {
    if (n < 10) {
        cout << n;
    }
    else {
        cout << n % 10 << " ";
        ts91(n / 10);
    }
}

void ts9() {
    int n;
    cin >> n;
    ts91(n);

}

int ts121(int a, int b) {
    if (b == 0) {
        return a;
    }
    return ts121(b, a % b);
}

void ts12() {
    int a, b;
    cin >> a >> b;
    cout << ts121(a, b);
}

int ts131(int a, int b) {
    if (b == 0) {
        return a;
    }
    return ts131(b, a % b);
}

void ts13() {
    int a, b, c, s;
    cin >> a >> b >> c;
    s = ts131(a, ts131(b, c));
    cout << s;
}

int main() {
    //ts1();
    //ts2();
    //ts3();
    //ts4();

    //ts6();
    //ts7();
    //ts8();
    //ts9();
    //ts10(); 

    //ts12();
    ts13();
}
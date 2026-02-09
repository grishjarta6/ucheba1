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

int ts71(int n) {
    if (n < 10) { return n; }
    else {
        
        cout << n % 2;
        return ts71(n / 10);
    }
}

int b(int b) {
    if (b == 0) { return b; }
    b
}

void f() {
    int n;
    cin >> n;
    if (n == 0) { return ; }
    f();
    cout << n;
}

void ts7() {
    int x;
    cin >> x;
    cout << ts71(x);
}

int main() {
    //ts1();
    //ts2();
    //ts3();
    //ts4();

    //ts6();
    //ts7();
    //f();
}
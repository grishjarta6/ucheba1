#include <iostream>
#include <cmath>
#include <iomanip>
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

int main() {
    //ts1();
    //ts2();
    ts3();
}
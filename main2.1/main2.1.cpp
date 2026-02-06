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

void ts2() {

}

int main() {
    //ts1();
}
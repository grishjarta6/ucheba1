#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#define N 100
using namespace std;

void ts1() {
	int n, c = 1, i, d;
	cin >> n;
	int* arr = new int[n];
	for (i = 0; i < n; i += 1) {
		cin >> arr[i];
	}
	d = arr[0];
	for (i = 1; i < n; i += 1) {
		if (d != arr[i]) { c += 1; }
		d = arr[i];
	}
	cout << c;
}

int main() {
	ts1();
}
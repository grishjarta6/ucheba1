#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#define N 100
using namespace std;

void ts1_1() {
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

void ts1_2() {
	int n = 1, c = 0, s = 0, i, cc = 0, m[100], mb[100];
	while (n != 0) {
		cin >> n;
		if (n != 0) {
			m[c] = n;
		}
		else {
			break;
		}
		s += n;
		c += 1;
	}
	s = s / c;
	for (i = 0; i <= c; i += 1) {
		if (m[i] > s) {
			mb[cc] = m[i];
			cc += 1;
		}
	}
	cout << cc << endl;
	for (i = 0; i < cc; i += 1) {
		cout << mb[i] << " ";
	}
}

void ts1_3() {
	int n = 1, c = 0, i, m[100];
	while (n != 0) {
		cin >> n;
		if (n != 0) {
			m[c] = n;
		}
		else {
			break;
		}
		c += 1;
	}
	for (i = (c - 1); i >= 0; i -= 1) {
		cout << m[i] << " ";
	}
}

void ts1_4() {
	int n, a, i, in, min = 1000000000;
	cin >> a;
	int* m = new int[a];
	for (i = 0; i <= a; i += 1) {
		cin >> n;
		m[i] = n;
	}
	for (i = 0; i <= a; i += 1) {
		if (min > m[i]) {
			min = m[i];
			in = i;
		}
	}
	m[in] = m[0];
	m[0] = min;
	for (i = 0; i <= a; i += 1) {
		cout << m[i] << " ";
	}
}

void ts1_5() {
	int n, a, i, ch = 0, cn = 0;
	cin >> a;
	int* m = new int[a];
	for (i = 1; i <= a; i += 1) {
		cin >> n;
		m[i] = n;
	}
	for (i = 1; i <= a; i += 1) {
		if (i % 2 == 0) {
			ch += m[i];
		}
		else {
			cn += m[i];
		}
	}
	if (ch > cn) {
		cout << "yes";
	}
	else {
		cout << "no";
	}
}

void ts1_6() {
	int n, a, i;
	cin >> a;
	int* m = new int[a];
	for (i = 0; i < a; i += 1) {
		cin >> n;
		m[i] = n;
	}
	for (i = 0; i < a; i += 1) {
		if (m[i] % 2 == 0) {
			cout << m[i] << " ";
		}
	}
	for (i = 0; i < a; i += 1) {
		if (m[i] % 2 != 0) {
			cout << m[i] << " ";
		}
	}
	delete[]m;
}

void ts1_7() {
	int n, a, i, k, c = 0;
	cin >> a;
	int* m = new int[a];
	int* mm = new int[a];
	for (i = 0; i < a; i += 1) {
		cin >> n;
		m[i] = n;
	}
	cin >> k;
	for (i = 0; i < a; i += 1) {
		if (m[i] != k) {
			mm[c] = m[i];
			c += 1;
		}
	}
	for (i = 0; i < c; i += 1) {
		cout << mm[i] << " ";
	}
}

int main() {
	//ts1_1();
	//ts1_2();
	//ts1_3();
	//ts1_4();
	//ts1_5();
	//ts1_6();
	//ts1_7();
}
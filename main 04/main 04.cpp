#include <iostream>
using namespace std;

// циклы.пдф

void ts1() {
	int n, i;
	cin >> n;
	for (i = n; i > 0; i --) {
		cout << i << endl;
	}
}

void ts2() {
	int n, i;
	cin >> n;
	for (i = 0; i <= n; i += 1) {
		cout << "*";
	}
}

void ts3() {
	int n, i = 0;
	for (i; i <= 10; i += 1) {
		cin >> n;
		cout << n * n << " " << n * 4 << endl;
	}
}

void ts4() {
	int x;
	cin >> x;
	for (int i = 0; i <= x; i++) {
		cout << "Number of clouds " << i << endl;
	}
}

void ts5() {
	int a, b, c;
	cin >> a >> b >> c;
	for (int i = 0; i >= a and i <= b; i++) {
		if (i % c == 0) {
			cout << i << " ";
		}
	}
}

void ts6() {
	int a;
	cin >> a;
	while (a % 5 == 0) {
		a = a / 5;
	}
	if (a == 1) {
		cout << "YES";
	}
	else {
		cout << "NO";
	}
}

void ts7() {
	int a;
	cin >> a;
	while (a % 19 != 0) {
		a = a + 1;
	}
	cout << a;
}

void ts8() {
	int n, d;
	int z;
	cin >> n >> d;
	for (int x = 1; x <= n; x++) {
		if (x % d == 0) {
			z = x;
		}
	} 
	cout << z;

}

void ts9() {
	int a;
	for (int i = 1; i <= 10; i++){
		cin >> a;
		cout << (a * a) * 2 << endl;
	}
}

void ts10() {
	int n, i;
	for (i = 0; i <= 10; i += 1) {
		cin >> n;
		cout << (n * n) * 2 << endl;
	}
}

void ts11() {
	int a;
	for (int i = 0; i <= 10; i++) {
		cin >> a;
		cout << 25 + abs(a) << endl;
	}
}

void ts13() {
	int a, b;
	cin >> a >> b;
	if (a <= b) {
		for (int i = a; i <= b; i++) {
			cout << i << " ";
		}
	}
	else {
		for (int i = b; i <= b; i++) {
			cout << i << " ";
		}
	}
}

int main() {
	//ts1();
	//ts2();
	//ts3();
	//ts4();
	//ts5();
	//ts6();
	//ts7();
	//ts8();
	//ts9();
	//ts10();
	//ts11();
	//ts13();
}
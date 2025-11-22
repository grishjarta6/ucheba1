#include <iostream>

using namespace std;

void ts0(){
	cout << "hello world";
}

void ts1() {
	int a, b;
	cin >> a >> b;
	cout << a + b;
}

void ts2() {
	int a, b;
	cin >> a >> b;
	cout << b - a;
}

void ts3() {
	int a, b;
	cin >> b >> a;
	cout << b - (a * 3);
}

void ts4() {
	int a, b;
	cin >> a >> b;
	cout << a * b << endl << a * 2 + b * 2;
}

void ts5() {
	int a, b;
	cin >> a >> b;
	cout << a - b;
}

void ts6() {
	int s, n, h;
	cin >> s >> n >> h;
	cout << (s + n) * h;
}

void ts7() {
	int n;
	cin >> n;
	cout << n << std::endl;
	cout << "    " << n + 1 << std::endl;
	cout << "        " << n + 2 << std::endl;
}

void ts8() {
	int n, a;
	cin >> n;
	cout << n * n << endl << n * n * n << endl << n * n * n * n * n;
}

void ts9() {
	int a;
	cin >> a;
	cout << "The next number for the number " << a << " " << a + 1 << endl;
	cout << "The previous number for the number " << a << " " << a - 1;
}

void ts10() {
	int x;
	cin >> x;
	cout << 7 * (x * x) - 3 * x + 6;
}

void ts11() {
	int a, b, c, d;
	cin >> a >> b >> c;
	d = a + b - c;
	cout << a << " + " << b << " - " << c << " = " << d;
}

void ts12() {
	int a;
	cin >> a;
	cout << a / 7;
}

void ts14() {
	int x;
	cin >> x;
	cout << 7 * (x * x) - 3 * x + 6;
}

void ts15() {
	int x;
	cin >> x;
	cout << (3 * pow(x, 3) + 18 * pow(x, 2)) * x + 12 * pow(x, 2) - 5 << endl;
}

void ts16() {
	int k;
	cin >> k;
	cout << k % 7 << endl;
}

void ts17() {
	int k, d;
	cin >> k >> d;
	cout << (d + k - 1 - 1) % 7 + 1 << endl;
}

int main() {
	//ts0();
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
	//ts12();
	//ts15();
	//ts16();
	ts17();
	return 0;
}
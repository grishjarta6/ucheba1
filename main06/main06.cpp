#include <iostream>
#include <cmath>
using namespace std;

//ВЛОЖЕННЫЕ ЦИКЛЫ
void ts1_1() {
	int x, y, cx = 0, cy = 0;
	cin >> y >> x;
	while (cy != y) {
		cx = 0;
		while (cx != x) {
			cout << "*";
			cx += 1;
		}
		cout << endl;
		cy += 1;
	}
}

void ts1_2() {
	int n, m, x = 0, y = 0, k = 0;
	cin >> n >> m;
	for (x = n; x <= m; x++) {
		for (y = n; y <= m; y++) {
			for (k = n; k <= m; k++) {
				if ((x * x) + (y * y) == (k * k)) {
					cout << x << " " << y << " " << k << endl;
				}
			}
		}
	}

}

void ts1_3() {
	int x, y, z, n;
	cin >> n;
	for (x = 1; x <= n; x++) {
		for (y = 1; y <= n; y++) {
			for (z = 1; z <= n; z++) {
				if ((x * x) + (y * y) + (z * z) == n) {
					cout << x << " " << y << " " << z << endl;
				}
			}
		}
	}
}

void ts1_4() {
	int n, c = 0, o, t, f, te;
	cin >> n;
	for (o = 0; o <= n; o += 1) {
		for (t = 0; t <= n; t += 2) {
			for (f = 0; f <= n; f += 5) {
				for (te = 0; te <= n; te += 10) {
					if (o + t + f + te == n) { c += 1; }
				}
			}
		}
	}
	cout << c;
}

int del(int k) {
	int i, c = 0;
	//a = k;
	for (i = 1; i < k; i += 1) {
		if (k % i == 0) { c += i;}// cout << i << " " << k << " " << c << endl;
	}
	return c;
}
void ts1_5() {
	int n, x, y;
	cin >> n;
	for (x = 1; x < n; x+=1) {
		for (y = 1; y < n; y += 1) {
			//cout << "y: " << y << "del x: " << del(x) << " x: " << x << " del y: " << del(y) << endl;
			if ( ((x == del(y)) and (y == del(x))) and (x != y) ) {
				cout << "ans: " << x << " " << y << endl;
			}
		}
	}
}

void ts1_6() {
	int n, i;
	float a = 0;
	cin >> n;
	for (i = 1; i <= n; i += 1) {
		//cout << "1";
		a += pow(i, 0.5);
		//cout << a;
	}
	cout << a;
}



//МАССИВЫ
void ts2_1() {
	int n, k, i, s = 10;
	cin >> n >> k;
	int* m = new int[s];
	for (i = 0; i < s; i += 1) {
		n = n + k;
		m[i] = n;
	}
	for (i = 0; i < s; i += 1) {
		cout << m[i] << " ";
	}
}
int main() {
	//ts1_1();
	//ts1_2();
	//ts1_3();
	//ts1_4();
	//ts1_5();
	ts1_6();
	
	//ts2_1();
}
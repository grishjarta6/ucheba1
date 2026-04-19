#include <iostream>
//#include <cmath>
//#include <iomanip>
//#include <string>
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

// двумерного массива/матрицы

void ts2_1() {
	int n, x, y;
	cin >> n;
	int** m = new int* [n];
	for (x = 0; x < n; x += 1) {
		m[x] = new int[n];  
	}
	for (x = 0; x < n; x += 1) {
		for (y = 0; y < n; y += 1) {
			m[x][y] = x + 1;
		}
	}
	for (x = 0; x < n; x += 1) {
		for (y = 0; y < n; y += 1) {
			cout << m[x][y];
		}
		cout << endl;
	}
	for (x = 0; x < n; x += 1) { delete[] m[x]; }
	delete[] m;
}

void ts2_2() {
	int n, m, x, y, xs, ys;
	cin >> n >> m;
	cout << endl;
	int** ar = new int* [n];

	for (x = 0; x < n; x += 1) { ar[x] = new int[m]; }

	for (x = 0; x < n; x += 1) {
		for (y = 0; y < m; y += 1) {
			xs = x - 1;
			ys = y - 1;
			if ((xs < 0) or (ys < 0)) {
				ar[x][y] = 1;
			}
			else {
				xs = ar[x - 1][y];
				ys = ar[x][y - 1];
				ar[x][y] = xs + ys;
			}
		}
	}
	for (x = 0; x < n; x += 1) {
		for (y = 0; y < m; y += 1) {
			cout << ar[x][y] << " ";
		}
		cout << endl;
	}
	for (x = 0; x < n; x += 1) {delete[] ar[x];}
	delete[] ar;
}

void ts2_3() {
	int n, x, y;
	cin >> n;
	int** m = new int* [n];
	for (x = 0; x < n; x += 1) { m[x] = new int[n]; }
	for (x = 0; x < n; x += 1) {
		for (y = 0; y < n; y += 1) {
			if (x % 2 == 0) {
				if (y % 2 == 0) {
					m[x][y] = 1;
				}
				else {
					m[x][y] = 0;
				}
			}
			else {
				if (y % 2 != 0) {
					m[x][y] = 1;
				}
				else {
					m[x][y] = 0;
				}
			}
		}
	}
	for (x = 0; x < n; x += 1) {
		for (y = 0; y < n; y += 1) {
			cout << m[x][y];
		}
		cout << endl;
	}
	for (x = 0; x < n; x += 1) { delete[] m[x]; }
	delete[] m;

}

void ts2_4() {
	int n, m, x, y, c = 1;
	cin >> n >> m;
	cout << endl;
	int** ar = new int* [n];

	for (x = 0; x < n; x += 1) { ar[x] = new int[m]; }

	for (x = 0; x < n; x += 1) {
		for (y = 0; y < m; y += 1) {
			ar[x][y] = c;
			c += 1;
		}
	}
	for (x = 0; x < n; x += 1) {
		for (y = 0; y < m; y += 1) {
			cout << ar[x][y] << " ";
		}
		cout << endl;
	}
	for (x = 0; x < n; x += 1) { delete[] ar[x]; }
	delete[] ar;
}

void ts2_5() {
	int n, x, y, i, c = 0, ci, yi, p;
	cin >> n;
	int** m = new int* [n];
	for (x = 0; x < n; x += 1) { m[x] = new int[n]; }
	for (x = 0; x < n; x += 1) {
		for (y = 0; y < n; y += 1) {
			m[x][y] = y + 1;
		}
		p = n;
		for (i = 0; i < c; i++) {
			ci = m[x][0];
			//cout << ci << endl;
			for (yi = 1; yi < p; yi += 1) {
				m[x][yi - 1] = m[x][yi];
				//p - 1;
			}
			m[x][n - 1] = ci;
		}
		c += 1;
	}
	for (x = 0; x < n; x += 1) {
		for (y = 0; y < n; y += 1) {
			cout << m[x][y] << " ";
		}
		cout << endl;
	}
}

void ts2_6() {
	int n, m, x, y;
	cin >> n >> m;
	cout << endl;
	int** ar = new int* [n];

	for (x = 0; x < n; x += 1) { ar[x] = new int[m]; }

	for (x = 0; x < n; x += 1) {
		for (y = 0; y < m; y += 1) {
			ar[x][y] = (x * y);
		}
	}
	x = 0;
	y = 0;
	for (x = 0; x < n; x += 1) {
		for (y = 0; y < n; y += 1) {
			cout << ar[x][y] << " ";
		}
		cout << endl;
	}//https://github.com/settings/tokens/new?description=VSCodium (read:user repo user:email workflow)&scopes=read:user,repo,user:email,workflow
}

void ts2_7() {
	int n, x, y, c = 1, cx = 0, cy = 0;
	cin >> n;
	int** m = new int* [n];
	for (x = 0; x < n; x += 1) { m[x] = new int [n]; }

	for (x = 0; x < n; x += 1) {
		for (y = 0; y < n; y += 1) {
			m[x][y] = c;
			c += 1;
		}
	}
	for (x = 0; x < n; x += 1) {
		for (y = 0; y < n; y += 1) {
			if (x == y) {
				cout << m[x][y] << " ";
			}
		}
	}
}

void ts2_8() {
	int n, x, y, c = 1, cx = 0, cy = 0;
	cin >> n;
	int** m = new int* [n];
	for (x = 0; x < n; x += 1) { m[x] = new int[n]; }

	for (x = 0; x < n; x += 1) {
		for (y = 0; y < n; y += 1) {
			m[x][y] = c;
			c += 1;
		}
	}
	cy = n - 1;
	for (x = 0; x < n; x += 1) {
		for (y = 0; y < n; y += 1) {
			if (y == cy) {
				cout << m[x][y] << " ";
			}
		}
		cy -= 1;
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

	//ts2_1();
	//ts2_2();
	//ts2_3();
	//ts2_4();
	//ts2_5();
	//ts2_6();
	//ts2_7();
	ts2_8();

}
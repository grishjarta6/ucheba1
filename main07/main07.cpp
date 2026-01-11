#include <iostream>
#include <iomanip>
using namespace std;

//вещ числа
void ts0_6() {
	float a, b, c, r, cen;
	cin >> a >> b >> c;
	r = (a / 100) * b;
	cen = r * c * 2;
	cout << cen;
}

void ts0_7() {
	int H, M, S;
	cin >> H >> M >> S;
	float result = (float(H) * 30.0) + (float(M) / 2.0) + (float(S) / 120.0);
	cout << fixed << setprecision(6) << result << endl;
}
//массивы 1

void ts1_1() {
	int n, a, c, cnt = 0, i;
	int m[1000];
	cin >> n;
	cout << "-------" << endl;
	for (i = 0; i < n; i += 1){
		cin >> a;
		m[i] = a;
	}
	cout << "----------" << endl;
	cin >> c;
	for (i = 0; i < n; i += 1) {
		if (c < m[i]) {
			cnt += m[i];
		}
	}
	cout << "ans: " << cnt;

}

void ts1_2() {
	int n, a, s = 0, p, i, m[100];
	cin >> n;
	for (i = 0; i < n; i += 1) {
		cin >> a;
		m[i] = a;
	}
	for (i = 0; i < n; i += 1) {s += m[i];}
	for (i = 0; i < n; i += 1) { 
		if (i == 0) { 
			p = m[i]; 
		}
		else{
			p = p * m[i];
		} 
	}
	cout << s << " " << p;
}

void ts1_4() {
	int n, a, ma = 0, mi = 0, m[100], i;
	cin >> n;
	cout << "--------" << endl;
	for (i = 0; i < n; i += 1) {
		cin >> a;
		m[i] = a;
	}
	for (i = 0; i < n; i += 1) {
		if (m[i] > ma) {
			ma = m[i];
		}
	}
	mi = ma;
	for (i = 0; i < n; i += 1) {
		if (m[i] < mi) {
			mi = m[i];
		}
	}
	cout << "ans: " << ma << " " << mi;
}

void ts1_10(){
	//числа по модулю < 100
	int n, a, c = 0, m[100], i, t, x;
	cin >> n;
	cout << "--------" << endl;
	for (i = 0; i < n; i += 1) {
		cin >> a;
		m[i] = a;
	}
	for (i = 0; i < n; i += 1) {
		if (m[i] != 101) {
			x = m[i];
			for (t = 0; t < n; t += 1) {
				if (m[t] == x) {
					m[t] = 101;
				}
			}
			cout << x << endl;
			c += 1;
		}
	}
	cout << "ans: " << c;

}

//массивы 2
void ts2_1() {
	int n, x, p, a, m1[100], m2[100], i;
	bool f;
	cin >> n;
	cout << "------" << endl;
	for (i = 0; i < n; i += 1) {
		cin >> a;
		m1[i] = a;
	}
	cout << "------" << endl;
	cin >> x >> p;
	cout << "------" << endl;
	if (p == 1) { 
		p = 0;
		m2[p] = x;
		for (i = 0; i < n; i += 1) {
			m2[i + 1] = m1[i];
		}

	}
	if (p == n + 1) { 
		p = n;
		m2[p] = x;
		for (i = 0; i < n; i += 1) {
			m2[i] = m1[i];
		}

	}
	else { 
		p -= 1;
		for (i = 0; i < p; i += 1) {
			m2[i] = m1[i];
		}
		m2[p] = x;
		for (i = p; i < n; i += 1) {
			m2[i + 1] = m1[i];
		}
	}

	for (i = 0; i < (n + 1); i += 1) { cout << "ans: " << m2[i] << " " << i << endl; }
}



void ts2_8() {
	int m[15], k, s, i, n = 15, a, c = 0, f, j;
	for (i = 0; i < n; i += 1) {
		cin >> a;
		m[i] = a;
	}
	cout << "__________________________" << endl;
	cin >> k >> s;
	//c = k;
	j = s;
	for (i = k; i < (s / 2); i += 1) {
		swap(m[i], m[j]);
		j -= 1;
	}
	for (i = 0; i <= n; i += 1) {
		cout << m[i] << " ";
	}
}

int main() {
	//ts0_6();
	//ts0_7();

	//ts1_1();
	//ts1_3();
	//ts1_4();
	//ts1_10();

	ts2_1();
	//ts2_8();
}
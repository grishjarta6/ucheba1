#include <iostream>
#include <iomanip>
using namespace std;

//вещ числа
void ts1_6() {
	float a, b, c, r, cen;
	cin >> a >> b >> c;
	r = (a / 100) * b;
	cen = r * c * 2;
	cout << cen;
}

void ts1_7() {
	int H, M, S;
	cin >> H >> M >> S;
	float result = (float(H) * 30.0) + (float(M) / 2.0) + (float(S) / 120.0);
	cout << fixed << setprecision(6) << result << endl;
}
//массивы 2

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
	//ts1_6();
	//ts1_7();

	ts2_8();
}
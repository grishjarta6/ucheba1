#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int dm_ts1(int x) {
	int z, s= 0;
	z = x;
	while (z != 0) {
		s += z % 10;
		z = z / 10;
	}
	//cout << s << endl;
	return s;
}
void ts1() {
	int m[5], n, i, c = 0;
	for (i = 0; i < 5; i += 1) {
		cin >> n;
		m[i] = n;
	}
	for (i = 0; i < 5; i += 1) {
		//cout << dm(m[i]) << endl;
		c += dm_ts1(m[i]);
	}
	cout << c;
}

int min_ts2(int x, int y) {
	if (x < y) { return x; }
	else { return y; }
}

void ts2() {
	int a, b, f;
	cin >> a >> b;
	f = min_ts2(a, 3 * b) * min_ts2(2 * a - b, 2 * b);
	cout << f;
}

int max_ts3(int x, int y) {
	if (x > y) { return x; }
	else { return y; }
}
int min_ts3(int x, int y) {
	if (x < y) { return x; }
	else { return y; }
}
int dis_ts3(int xa, int ya, int xb, int yb) {
	int max, mix, may, miy, x, y;
	float s;
	max = max_ts3(xa, xb);
	mix = min_ts3(xa, xb);
	may = max_ts3(ya, yb);
	miy = min_ts3(ya, yb);
	x = max - mix;
	y = may - miy;
	s = pow((x * x + y * y), 0.5);
	return s;
}

void ts3() {	
	int x1, y1, x2, y2, x3, y3;
	float dist1, dist2, dist3, p;
	cout << "k1" << endl;
	cin >> x1 >> y1; //верш
	cout << "k2" << endl;
	cin >> x2 >> y2; //лев
	cout << "k3" << endl;
	cin >> x3 >> y3; //прав
	dist1 = dis_ts3(x1, y1, x2, y2);
	dist2 = dis_ts3(x1, y1, x3, y3);
	dist3 = dis_ts3(x2, y2, x3, y3);
	p = dist1 + dist2 + dist3;
	cout << fixed << setprecision(8) << p;

}

int main() {
	//ts1();
	//ts2();
	ts3();
}
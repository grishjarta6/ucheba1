#include <iostream>
using namespace std;

void ts00() {
	cout << "1111111";
}

//БИТОВЫЕ ОПЕРАЦИИ
void ts01() {
	int n;
	cin >> n;
	switch (n) {
	case(1):
		cout << "Monday";
		break;
	case(2):
		cout << "Tuesday";
		break;
	case(3):
		cout << "Wednesday";
		break;
	case(4):
		cout << "Thursday";
		break;
	case(5):
		cout << "Friday";
		break;
	case(6):
		cout << "Saturday";
		break;
	case(7):
		cout << "Sunday";
		break;
	default:
		cout << "error";
		break;
	}
}

void ts02() {
	int n, d;
	cin >> n;
	d = n & 7;


	switch (d) {
	case 1: 
		cout << "Monday" << endl; 
		break;
	case 2: 
		cout << "Tuesday" << endl; 
		break;
	case 3: 
		cout << "Wednesday" << endl; 
		break;
	case 4: 
		cout << "Thursday" << endl; 
		break;
	case 5: 
		cout << "Friday" << endl; 
		break;
	case 6: 
		cout << "Saturday" << endl; 
		break;
	case 7: 
		cout << "Sunday" << endl; 
		break;
	}
}

void ts03() {
	int n, d, t;
	cin >> n;
	//nd = n;
	//nd &= ~(1 << 4);
	//nd &= ~(1 << 5);
	d = n & 7;
	t = (n >> 3) & 4;
	
	cout << t << "_t  d_" << d << endl;

	switch (t) {
	case 0:
		cout << "morning" << " ";
		break;
	case 1:
		cout << "afternoon" << " ";
		break;
	case 2:
		cout << "evening" << " ";
		break;
	case 3:
		cout << "night" << " ";
		break;
	default:
		cout << "error";
		break;
	}
	switch (d) {
	case 1:
		cout << "Monday" << endl;
		break;
	case 2:
		cout << "Tuesday" << endl;
		break;
	case 3:
		cout << "Wednesday" << endl;
		break;
	case 4:
		cout << "Thursday" << endl;
		break;
	case 5:
		cout << "Friday" << endl;
		break;
	case 6:
		cout << "Saturday" << endl;
		break;
	case 7:
		cout << "Sunday" << endl;
		break;
	default:
		cout << "error";
		break;
	}
}

// зм   дм    су дн
// 0000 00000 00 000 
void ts04() {
	int n, d, t, w, m;
	cin >> n;
	w = n & 7;
	t = (n >> 3) & 3;
	d = (n >> 5) & 31;
	m = (n >> 10) & 15;
	cout << "mounth " << m << " " << "day mounth " << d << endl;
	switch (t) {
	case 0:
		cout << "morning" << " ";
		break;
	case 1:
		cout << "afternoon" << " ";
		break;
	case 2:
		cout << "evening" << " ";
		break;
	case 3:
		cout << "night" << " ";
		break;
	}
	switch (w) {
	case 1:
		cout << "Monday" << endl;
		break;
	case 2:
		cout << "Tuesday" << endl;
		break;
	case 3:
		cout << "Wednesday" << endl;
		break;
	case 4:
		cout << "Thursday" << endl;
		break;
	case 5:
		cout << "Friday" << endl;
		break;
	case 6:
		cout << "Saturday" << endl;
		break;
	case 7:
		cout << "Sunday" << endl;
		break;
	}
}

void ts05() {
	int n, a;
	cin >> n;
	a = n << 1;
	cout << a;
}

void ts06() {
	int n, a;
	cin >> n;
	a = n << 2;
	cout << a;
}

void ts07() {
	int n, a = 2;
	cin >> n;
	a = (a << n) >> 1;
	cout << a;
}

void ts08() {
	int n, m;
	cin >> n >> m; cout << ((2 << n) >> 1) + ((2 << m) >> 1);
}

void ts09() {
	int n, k;
	cin >> n >> k;
	cout << (n | (1 << k)) << endl;
}

void ts10() {
	int n, k;
	cin >> n >> k;
	cout << (n & ~(1 << k)) << endl;
}

//ВЫДЕЛЕНИЕ ЦИФР
void ts11() {
	int n, a;
	cin >> n;
	while (n > 10) {
		a = n % 10;
		n = n / 10;
		cout << a << " ";
	}

}

void ts12() {
	int n, c = 0;
	cin >> n;
	while (n > 0) {
		c += 1;
		n = n / 10;
	}
	cout << c;
}

void ts13() {
	int n, c = 0, a;
	cin >> n;
	while (n > 0) {
		a = n % 10;
		n = n / 10;
		if (a == 3) {
			c += 3;
		}
	}
	if (c % 3 == 0) {
		cout << "yes";
	}
}

void ts14() {
	int n, c = 0;
	cin >> n;
	while (n > 0) {
		if (n % 10 == 6) {
			c += 1;
		}
		n = n / 10;
	}
	if (c >= 2) {
		cout << "yes";
	}
	else {cout << "no";}
}

void ts15() {
	int n, k, c = 0;
	cin >> n >> k;
	while (n > 0) {
		if (n % 10 == k) {c += 1;}
		n = n / 10;
	}
	cout << c;
}

void ts16() {
	int n, a = 0, b = 0, c = 0, d;
	cin >> n;
	while (n > 0) {
		c += 1;
		d = n % 10;
		switch (c) {
			case 1: a += d; break;
			case 2: a += d; break;
			case 3: a += d; break;
			case 4: b += d; break;
			case 5: b += d; break;
			case 6: b += d; break;
		}
		n = n / 10;
	}
	if (a == b) { cout << "yes"; }
	else { cout << "no"; }
}

void ts17() {
	int n, c0 = 0, c9 = 0;
	cin >> n;
	while (n > 0) {
		switch (n % 10) {
			case 0: c0 += 1; break;
			case 9: c9 += 1; break;
			default: break;
		}
		n = n / 10;
	}
	if (c0 >= c9) { cout << "0";}
	else { cout << "9"; }
}

void ts18() {
	int n, a = 0;
	cin >> n;
	while (n > 0) {a += n % 10; n /= 10;}
	cout << a;
}

void ts19() {
	int n, nma, nmi, ma = 0, mi = 10, cma = 0, cmi = 0, ma2, mi2, cma2 = 0, cmi2 = 0, c = 0, nc;
	cin >> n;
	nma = n;
	nmi = n;
	nc = n;
	while (nma > 0) {
		cma = cma + 1;
		ma2 = nma % 10;
		if ((ma < ma2) or (ma == 0)) {
			ma = ma2;
			//cout << cma << endl;
			cma2 = cma;
		}
		cma = cma - cma2 + 1;
		nma = nma / 10;
	}
	while (nmi > 0) {
		cmi += 1;
		mi2 = nmi % 10;
		if (mi > mi2) {
			mi = mi2;
			cmi2 = cmi;
		}
		nmi = nmi / 10;
	}
	while (nc > 0) {
		if (nc % 10 == mi) { c += 1; }
		nc /= 10;
	}
	cout << ma << " " << mi << endl;
	if (cma == 1) { cout << 1 << endl; }
	else { cout << cma << endl; }
	cout << c;

}

int main() {
	//ts00();
	//ts01();
	//ts02();
	//ts03();
	//ts04();
	//ts05();
	//ts06();
	//ts07();
	//ts08();
	//ts09();
	//ts10();
	//ts11();
	//ts12();
	//ts13();
	//ts14();
	//ts15();
	//ts16();
	//ts17();
	//ts18();
	ts19();
}
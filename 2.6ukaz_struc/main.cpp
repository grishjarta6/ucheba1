#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;


struct p11 { double x, y; };  // локальная структура

double distq(p11 A, p11 B){
        double dx = A.x - B.x;
        double dy = A.y - B.y;
        return sqrt(dx*dx + dy*dy);
}

void ts11() {
    p11 A, B;
    cin >> A.x >> A.y >> B.x >> B.y;
    double dist = distq(A, B);
    cout << fixed << setprecision(6) << dist << endl;
}

struct p12{ double x, y; };

double d12(p12 a, p12 b){
    double dx, dy, ans;
    dx = a.x - b.y;
    dy = a.y - b.y;
    ans = sqrt((dx * dx) + (dy * dy));
    return ans;
}

void ts12(){
    int n, i;
    double tans = 0.0;
    //cout << 11111111111 << endl;
    cin >> n;
    p12 p, c;
    cin >> p.x >> p.y;
    for (i = 0; i < n; i += 1){
        cin >> c.x >> c.y;
        tans = d12(p, c);
        p = c;
    }
    cout << fixed << setprecision(4) << tans << endl;
}

struct p13{double x, y;};

struct l13{p13 p1, p2;};

double pl13(l13 l){
    double w, h, ans;
    w = fabs(l.p2.x - l.p1.x);
    h = fabs(l.p2.y - l.p1.y);
    ans = w * h;
    return ans;
}

double per13(l13 l){
    double w, h, ans;
    w = fabs(l.p2.x - l.p1.x);
    h = fabs(l.p2.y - l.p1.y);
    ans = (w + h) * 2;
    return ans;
}

void ts13(){
    double s, p;
    l13 l;
    cout << "p1 x" << endl;
    cin >> l.p1.x;
    cout << "p1 y" << endl;
    cin >> l.p1.y;
    cout << "p2 x" << endl;
    cin >> l.p2.x;
    cout << "p2 y" << endl;
    cin >> l.p2.y;

    s = pl13(l);
    p = per13(l);

    cout << fixed << setprecision(6) << s << endl;
    cout << fixed << setprecision(6) << p << endl;
}

struct p14{double x, y;};
struct l14{p14 p1, p2, p3;};

double d14(l14 l){
    double anx = 0, any = 0, ax, bx, ex, ay, by, ey;
    ex = l.p3.x;
    ey = l.p3.y;
    ax = l.p1.x;
    ay = l.p1.y;
    bx = l.p2.x;
    by = l.p2.y;
    if ((ax <= ex) and (bx >= ex)){anx = 1;}
    if ((ay <= ey) and (by >= ey)){any = 1;}
    if ((anx == 1) and (any == 1)){return 1;}
    else {return 0;}
}

void ts14(){
    l14 l;
    cout << "p1 x" << endl;
    cin >> l.p1.x;
    cout << "p1 y" << endl;
    cin >> l.p1.y;
    cout << "p2 x" << endl;
    cin >> l.p2.x;
    cout << "p2 y" << endl;
    cin >> l.p2.y;
    cout << "p3 x" << endl;
    cin >> l.p3.x;
    cout << "p3 y" << endl;
    cin >> l.p3.y;

    if(d14(l) == 1){cout << "yes" << endl;}
    else {cout << "no" << endl;}
}

void numswap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void ts21() {
    int x, y;
    cin >> x >> y;
    numswap(&x, &y);
    cout << x << " " << y << endl;
}



void coe(int x, int *odd, int *even){
    int a, b;
    a = x;
    if (a > 9){
        a = x / 10;
        b = x % 10;
        if((a % 2 == 0) or (b % 2 == 0)){*even += 1;}
        if((a % 2 != 0) or (b % 2 != 0)){*odd += 1;}
    }
    else{
        if(a % 2 == 0){*even += 1;}
        if(a % 2 != 0){*odd += 1;}
    }
}

void ts22(){
    int m[10], i, ch, nch;
    
    cout << "enter" << endl;
    for (i = 0; i < 10; i += 1){cin >> m[i];}

    for(i = 0; i < 10; i += 1){
        ch = 0;
        nch = 0;
        coe(m[i], &nch, &ch);
        cout << nch << " " << ch << endl;
    }

}

int re23(double a, double b, double c, double *x1, double *x2){
    double d;
    d = (b * b) - (4 * a * c);

    if (d < 0) {return 0;}

    if (d == 0){
        *x1 = (-b) / (2 * a);
        return 1;
    }
    else{
        *x1 = ((-b) + sqrt(d)) / (2 * a);
        *x2 = ((-b) - sqrt(d)) / (2 * a);
        return 2;
    }
}

void ts23(){
    double a, b, c, x1, x2;
    cout << "a:" << endl;
    cin >> a;
    cout << "b:" << endl;
    cin >> b;
    cout << "b:" << endl;
    cin >> c;

    if (re23(a, b, c, &x1, &x2) == 0){cout << "no" << endl;}
    if (re23(a, b, c, &x1, &x2) == 1){cout << x1 << endl;}
    if (re23(a, b, c, &x1, &x2) == 2){cout << x1 << " " << x2 << endl;}

}

int main(){
    //структуры

    //ts11();
    //ts12();
    //ts13();
    ts14();

    //указатели

    //ts21();
    //ts22();
    //ts23();
    return 0;
}

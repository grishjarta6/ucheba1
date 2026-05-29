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

int main(){
    //ts11();
    //ts12();
    //ts13();
    return 0;
}

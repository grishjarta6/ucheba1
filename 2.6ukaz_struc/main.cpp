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



int main(){
    ts11();
    return 0;
}

#include <cstddef>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

template <typename type>
struct stek{
    type dat[100000];
    int top_indx;
    stek(){
        top_indx = -1;
    }
    
    void push(type v){
        if(top_indx + 1 < 100000){
            dat[top_indx + 1] = v;
            top_indx += 1;
        }
        else{ cout << "stek is full" << endl; }
    }

    void del(){
        if(top_indx != -1){ top_indx -= 1; }
        else { cout << "stek is clear" << endl; }
    }

    type read(){
        return dat[top_indx];
    }

    type readindx(type x){
        if (x <= top_indx){
            return dat[x];
        }
        else{
            cout << "not in dat" << endl;
            return -1;
        }
    }

    int size(){
        return top_indx + 1;
    }

    bool pust(){
        return (top_indx == -1);
    }
};


void zd(){
    stek<int> c;
    int n, i, x, y, cnt = 0, min, m1, m2, ii;
    cin >> n;
    for (i = 0; i < n; i += 1){
        cin >> x;
        switch (x) {
            case(1):
                cin >> y;
                c.push(y);
                cnt += 1;
                break;
            case(2):
                cout << c.read() << endl;
                c.del();
                cnt -=1;
                break;
            case(3):
                for(ii = 0; ii < cnt - 1; ii += 1){
                    m1 = c.readindx(ii);
                    m2 = c.readindx((ii + 1));
                    if(m1 == -1 or m2 == -1){
                        if(m1 == -1 and m2 == -1){
                            cout << "err" << endl;
                        }
                        if (m1 == -1){min = m2;}
                        if (m2 == -1){min = m1;}
                    }
                    else{
                        if (m1 <= m2){
                            min = m1;
                        }
                        else{min = m2;}
                    }
                }   
                cout << min << endl;
                break;
        }
    }
}


int main(){
    zd();   

    return 0;
}
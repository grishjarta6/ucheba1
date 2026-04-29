#include <iostream>

using namespace std;

void ts1(){
    int n, x, i, j, ol, ne;
    cin >> n;
    cout <<"---------------------" << endl;
    int* m = new int [n];
    for (i = 0; i < n; i += 1){
        cin >> x;
        m[i] = x;
    }
    for (i = 0; i < n - 1; i += 1){
        for (j = 0; j < n - i - 1; j += 1){
            if (m[j] > m[j + 1]){
                    ol = m[j];
                    ne = m[j + 1];
                    m[j] = ne;
                    m[j + 1] = ol;
            }
        }
    }
    for (i = 0; i < n; i += 1){
        cout << m[i] << " ";
    }
    delete[] m;
    
    
}

int main(){
    ts1();
    return 0;
}
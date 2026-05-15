#include <cstddef>
#include <cstdio>
#include <iomanip>  // для setprecision
#include <iostream>
#include <string>

using namespace std;

void ts1(){
    string s, so;
    int i;
    cin >> s;
    for(i = 0; i <= s.size(); i += 1){
        if(s[i] == 'e'){
            so += 'i';
        }
        else{so += s[i];}
    }
    cout << so << endl;
}

void ts2(){
    string s;
    cin >> s;
    if(s[0] == s[s.size() - 1]){cout << "yes" << endl;}
    else{cout << "no" << endl;}
}

void ts3(){
    const int m = 500;
    char n[500];                
    cin.getline(n, m);    

    int pos = -1;
    for (int i = 0; n[i] != '\0'; ++i) {
        if (n[i] == ' ') {
            pos = i;
            break;
        }
    }

    cout << (n + pos + 1) << ' ';
    for (int i = 0; i < pos; ++i) {
        cout << n[i];
    }
    cout << endl;
}

void ts4(){
    string s;
    getline(cin, s);

    int count_f = 0;
    int second_index = -1;

    for (int i = 0; i < (int)s.size(); ++i) {
        if (s[i] == 'f') {
            count_f++;
            if (count_f == 2) {
                second_index = i;
                break;
            }
        }
    }

    if (count_f == 0) cout << -2 << endl;
    else if (count_f == 1) cout << -1 << endl;
    else cout << second_index << endl;
}

void ts5(){
    int n, i;
    char c;
    bool zb = false, sb = false, ch = false;
    string s; 
    getline(cin, s);
    n = s.size();
    if (n >= 8){
        for (i = 0; i <= n; i += 1){
            c = s[i];
            if ((c >= 'a') and (c <='z')){sb = true;}
            if ((c >= 'A') and (c <='Z')){zb = true;}
            if ((c >= '0') and (c <='9')){ch = true;}
        }
    }
    //else {cout << "no" << endl;}
    if (zb and sb and ch){cout << "yes" << endl;}
    else {cout << "no" << endl;}
}

void ts6(){
    int i, n;
    string s;
    char c, l;

    getline(cin, s);
    n = s.size();
    l = s[n - 1];
    cout << l << endl;
    if (l == 'l'){
        for (i = 0; i < n - 1; i += 1){
            c = s[i];
            cout << c;
        }
        cout << endl;
    }
    else{cout << s << endl;}
}

void ts7(){
    int n;
    char t;
    string s;
    cin >> n >> t;       
    cin >> s;                 

    int c = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        if (s[i] == t) {
            c+=1;
        }
    }

    double freq = (double)c / n;
    cout << fixed << setprecision(6) << freq << endl;
    //10 a
    //abbacadaff
    
}

int main(){
    //ts1();
    //ts2();
    //ts3();
    //ts4();
    //ts5();
    //ts6();
    //ts7();
    return 0;
}
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



int main(){
    //ts1();
    //ts2();
    //ts3();
    //ts4();
    return 0;
}
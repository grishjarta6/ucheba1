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
    char n[500], n1[500], n2[500];
    int i;
    cin.getline(n, m)
    
    

}

int main(){
    //ts1();
    //ts2();
    ts3();
    return 0;
}
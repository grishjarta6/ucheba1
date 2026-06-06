#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
template <typename type>//штука чтобы универсальные переменные. при вызове конкретный тип данных

//стек работает по принципу стопки(работа онли с верхнем элементом)
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
        else{cout << "stek is full" << endl;}
    }

    void del(){
        if(top_indx != -1){top_indx -= 1;}//следующий вызов push удалит элемент
        else {cout << "stek is clear" << endl;}
    }

    type read(){
        return dat[top_indx];
    }

    int size(){
        return top_indx + 1;
    }

    bool pust(){
        if(top_indx == -1){return 1;}
        else{return 0;}
    }

};

void test(){
    string s;
    char c;
    bool a = 0;
    int n, i;
    stek<char> st;
    cout << "start" << endl;
    getline(cin, s);

    //for (char c : s){st.push(c);}

    n = s.size();

    for(i = 0; i < n; i += 1){
        c = s[i];
        st.push(c);
    }

    while (a != 1){
        cout << "start2 " << a << endl;
        cout << st.read() << endl;
        st.del();
        a = st.pust();
    }
}


void za(){
    string s;
    char c, cv;
    int o, p, i, n;
    bool tf = 0;
    stek<char> st;

    getline(cin, s);

    n = s.size();

    for (i = 0; i < n; i += 1){
        c = s[i];
        st.push(c);
    }

    while (tf != 1){
        cv = st.read();
        st.del();
        tf = st.pust();
        if (cv == '('){o += 1;}
        if (cv == ')'){p += 1;}
    }

    if (o == p){cout << "yes" << endl;}
    else {cout << "no" << endl;}
}

void zb(){
    string s;
    char c, cv;
    int i, n, oo, oc, ko, kc;
    bool tf = 0, old, nw, mark;
    stek<char> st;

    getline(cin, s);

    n = s.size();

    for (i = 0; i < n; i += 1){
        c = s[i];
        st.push(c);
    }

    if (s[n] == '('){old = 0;}
    else{old = 1;}

    while (tf != 1){
        cv = st.read();
        st.del();
        tf = st.pust();
        if(cv == '('){oo += 1; nw = 0;}
        if(cv == ')'){oc += 1; nw = 0;}
        if(cv == '['){ko += 1; nw = 1;}
        if(cv == ']'){kc += 1; nw = 1;}
        if (old == nw){mark = 1;}
        else{mark = 0; break;}
        old = nw;
    }
    if((oo == oc) and (ko == kc) and (mark == 1)){cout << "yes" << endl;}
    else{cout << "no" << endl;}
}

void zc(){
    stek<int> st;
    int i, n, zn, ch, x, a, b;

    cin >> n;

    for (i = 0; i < n; i += 1){
        cin >> x;
        if (x == 0){
            cin >> x;
            st.push(x);
        }
        else{
            switch (x) {
                case (1):
                    a = st.read();
                    st.del();
                    b = st.read();
                    st.del();
                    st.push(a + b);
                    break;
                case(2):
                    a = st.read();
                    st.del();
                    b = st.read();
                    st.del();
                    st.push(b - a);
                    break;
                case(3):
                    a = st.read();
                    st.del();
                    b = st.read();
                    st.del();
                    st.push(a * b);
                    break;
                default:
                    cout << "wrong nmber" << endl;
            }
        
        }
    }
    cout << st.read() << endl;

}

int main(){
    //test();

    //za();
    //zb();
    zc();

    return 0;
}
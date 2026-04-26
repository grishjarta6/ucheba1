#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void ts01(){
    int a, b, p1, p2, p3, n, i;
    ifstream input("input.txt");
    cin >> n;
    int* m = new int[n];
    for (i = 0; i < n; i++){
        input >> m[i];
    }
    ofstream outfile("output.txt");
    //cin >> a >> b;
    p1 = m[0] + m[1];
    p2 = m[0] - m[1];
    p3 = m[0] * m[1];
    if (outfile.is_open()){
        outfile << p1 << endl << p2 << endl << p3 << endl;
    }
    outfile.close();
    delete []m; 
}

void ts02() {
    ifstream input("input.txt");
    

    char ch;
    int count = 0;
    while (input.get(ch)) {
        // isspace требует беззнаковый char для корректной работы с отрицательными значениями
        if (!isspace(static_cast<unsigned char>(ch))) {
            count += 1;
        }
    }
    input.close();

    ofstream output("output.txt");
    output << count;
    output.close();
}


void ts03() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    if (!in.is_open() || !out.is_open()) {
        return;
    }

    char* symbols = nullptr;
    int size = 0;
    int capacity = 16;
    symbols = new char[capacity];

    char ch;
    while (in.get(ch)) {
        
        if (size >= capacity) {
            capacity *= 2;
            char* newSymbols = new char[capacity];
            for (int i = 0; i < size; ++i) {
                newSymbols[i] = symbols[i];
            }
            delete[] symbols;
            symbols = newSymbols;
        }
        symbols[size++] = ch;

        
        if (size >= 3 && symbols[size-3] == 'e' && symbols[size-2] == 'n' && symbols[size-1] == 'd') {
            break;
        }
    }

    out << size << '\n';
    if (size > 0) {
        out << symbols[0];
        for (int i = 1; i < size; ++i) {
            out << ' ' << symbols[i];
        }
        out << '\n';
    }

    delete[] symbols;
    in.close();
    out.close();
}


void ts04() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    if (!in.is_open() || !out.is_open()) {
        return;
    }

    string line;
    int ln = 0;

    while (getline(in, line)) {
        ln += 1;
        if (ln == 3) {
            continue;
        }
        out << line << '\n';
    }

    in.close();
    out.close();
}

void ts05(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    if (!in.is_open() || !out.is_open()) {
        return;
    }

    int lc = 0;
    string line;
    while (getline(in, line)) {
        cout << line << endl;
        lc += 1;
    }

    cout << lc << endl;

    in.close();
    out.close();
    ifstream in2("input.txt");
    ofstream out2("output.txt");

    if (!in2.is_open() || !out2.is_open()) {
        return;
    }

    int ln = 0;
    string line2;
    while (getline(in2, line2)) {
        ln += 1;
        cout << line2 << endl;
        if (ln == lc) {
            continue; 
        }
        out2 << line2 << '\n';
    }
    in2.close();
    out2.close();

}

void ts06(){
    int lc = 0,  cc = 0;
    string l, ht = " ";
    bool tl = false;

    ifstream in("input.txt");
    ofstream out("output.txt");

    while (getline(in, l)){
        lc += 1;
        cc += l.size();
        if (lc >= 3){tl = true; ht = l;}
    }
    out << lc << '\n';
    out << cc << '\n';
    if(tl == true){out << ht << '\n';}
    else {out << 0 << '\n';}
    in.close();
    out.close();

}

int p07(char ch){
    if ((ch == '0') or (ch == '1') or (ch == '2') or (ch == '3') or (ch == '4') or (ch == '5')
    or (ch == '6') or (ch == '7') or (ch == '8') or (ch == '9')){
        return 1;
    }
    else {return 0;}
}

void ts07(){
    int c = 0;
    bool n = false;
    char ch;
    ifstream in("input.txt");

    while (in.get(ch)){
        if (p07(ch) == 1){
            if (n == false){
                c += 1;
                n = true;
            }
        }
        else {
            n = false;
        }
    }

    cout << c << endl;
    in.close();
}

void ts08(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    string l, ln = "", t;

    while (getline(in, l)){
        t = '\n' + l;
        ln = t + ln;    
    }

    out << ln;

    in.close();
    out.close();

}

void ts21(){
    int a, b, i;
    cin >> a >> b;
    for (i = a; i <= b; i += 1){
        cout << i << " " << static_cast<char>(i) << endl;
    }
}

void ts22(){
    int n, x, i;
    char ch;
    cin >> n;
    for (i = 0; i < n; i += 1){
        ch = 'A'+ i;
        for (x = 0; x <= i; x += 1){
            cout << ch;
        }
        cout << endl;
    }
}

void ts23(){
    char n = 'a';
    string h = "Hello ,", a;
    while (n != '.'){
        cin >> n;
        if (n == '.'){break;}
        a += n;
    }
    cout << h + a << endl;

}

void ts24(){
    int c = 0;
    char n = 'a';
    while (n != '.'){
        cin >> n;
        if ((n != ' ') and (n != '.')){c += 1;}
    }
    cout << c << endl;
}

int p23(char ch){
    if ((ch == '0') or (ch == '1') or (ch == '2') or (ch == '3') or (ch == '4') or (ch == '5')
    or (ch == '6') or (ch == '7') or (ch == '8') or (ch == '9')){
        return 1;
    }
    else {return 0;}
}


void ts25(){
    int c = 0;
    char n = 'a';
    while (n != '.'){
        cin >> n;
        if (p23(n) == 1){c += 1;}
    }

    cout << c << endl;
}

int main(){
    //fstream

    //ts01();
    //ts02();
    //ts03();
    //ts04();
    //ts05();
    //ts06();
    //ts07();
    //ts08();

    //аски

    //ts21();
    //ts22();
    //ts23();
    //ts24();
    ts25();
    return 0;
}
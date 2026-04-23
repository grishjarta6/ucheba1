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
    if (!input.is_open()) {
        // Если файл не открылся, считаем, что данных нет
        ofstream output("output.txt");
        output << 0;
        output.close();
        return;
    }

    char ch;
    int count = 0;
    while (input.get(ch)) {
        // isspace требует беззнаковый char для корректной работы с отрицательными значениями
        if (!isspace(static_cast<unsigned char>(ch))) {
            ++count;
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
        // расширяем массив при необходимости
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

        // проверяем последние три символа на "end"
        if (size >= 3 && symbols[size-3] == 'e' && symbols[size-2] == 'n' && symbols[size-1] == 'd') {
            break;
        }
    }

    // вывод
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
            continue; // пропускаем третью строку
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
            continue; // пропускаем третью строку
        }
        out2 << line2 << '\n';
    }
    in2.close();
    out2.close();

}

int main(){
    //ts01();
    //ts02();
    //ts03();
    //ts04();
    ts05();
    return 0;
}
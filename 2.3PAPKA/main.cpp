#include <iostream>
#include <fstream>

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



int main(){
    //ts01();
    //ts02();
    return 0;
}
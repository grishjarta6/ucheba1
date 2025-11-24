#include <iostream>
using namespace std;


void task1() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << "Number of pigs: " << i << endl;
    }
}

void task2() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << "[_]";
    }
}

void task3() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        if (i % 3 == 0) {
            cout << "";
        }
        else {
            cout << i << " ";
        }
    }
}

void task4() {
    int x, n;
    cin >> x >> n;
    for (int i = 0; i < n; i++) {
        x *= 2;
    }
    cout << x;
}

void task5() {
    int x;
    cin >> x;
    for (int i = x; i >= 50; i -= 5) {
        cout << i << endl;
    }
}

void task6() {
    int x;
    cin >> x;
    int sum = 0;
    for (int i = 1; i <= x; i++) {
        sum += i;
    }
    cout << sum << endl;
}

void task7() {
    int x;
    cin >> x;
    for (int i = 1; i <= x; i++) {
        if (x % i == 0) {
            cout << i << " ";
        }
    }
}

void task8() {
    int n;
    cin >> n;
    int cnt = 0;
    int summa = 0;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        if (k > 1000) {
            cnt++;
            summa += k;
        }
    }
    cout << cnt << " " << summa << endl;
}

void task9() {
    int N;
    cin >> N;
    int k1 = 0, k2 = 0, k3 = 0;
    int obsh_prib = 0;
    for (int i = 0; i < N; i++) {
        int P;
        cin >> P;
        obsh_prib += P;
        if (P > 0) {
            k1++;
        }
        else if (P < 0) {
            k2++;
        }
        else {
            k3++;
        }
    }
    cout << k1 << " " << k2 << " " << k3 << endl;
    cout << obsh_prib << endl;
}

void task10() {
    int n;
    cin >> n;

    int best_index = 0;
    int best_income = -1;
    int best_age = -1;
    for (int i = 1; i <= n; i++) {
        int age, income;
        cin >> age >> income;
        if (age >= 1 && age <= 12) {
            continue;
        }
        if (best_index == 0) {
            best_index = i;
            best_income = income;
            best_age = age;
            continue;
        }
        bool cur_youth = (age >= 13 && age <= 29);
        bool best_youth = (best_age >= 13 && best_age <= 29);
        bool cur_old = (age >= 30);
        bool best_old = (best_age >= 30);
        if (cur_old && best_youth) {
            if (income + 100000 > best_income) {
                best_index = i;
                best_income = income;
                best_age = age;
            }
        }
        else if (cur_youth && best_old) {
            if (income > best_income + 100000) {
                best_index = i;
                best_income = income;
                best_age = age;
            }
        }
        else if (income > best_income) {
            best_index = i;
            best_income = income;
            best_age = age;
        }
        else {
            if (income > best_income) {
                best_index = i;
                best_income = income;
                best_age = age;
            }
        }
    }
    cout << best_index << endl;
}

void task11() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int age = 0;
        int income = 0;
        cin >> age >> income;
        if (1 <= age <= 12) {
            cout << 0;
        }
        if (13 <= age <= 29) {

        }
        if (30 <= age) {

        }
    }
}

int main() {
    //void task1();
    //void task2();
    //void task3();
    //void task4();
    //void task5();
    //void task6();
    //void task7();
    //void task8();
    //void task9();
    //void task10();
    //void task11();
}
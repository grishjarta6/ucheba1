#include <iostream>

using namespace std;

template <typename uni>

struct Clist {
    struct Ldat{
    uni dat;
    Ldat* next;
    };
    
    Ldat* head;

    void strt(){
        head = nullptr;
    }

    void PF(uni n){
        Ldat* ndat = new Ldat;
        (*ndat).dat = n;
        (*ndat).next = head;
        head = ndat;
    }

    void PB(uni n){
        Ldat* ndat = new Ldat;
        (*ndat).dat = n;
        (*ndat).next = nullptr;

        Ldat* cur = head;

        if (head == nullptr){head = ndat;}
        else{
            while ((*cur).next != nullptr){
                cur = (*cur).next;
            }
            (*cur).next = ndat;
        }
    }

    bool EmpAsk() { return (head == nullptr); }

    void RF(){
        if(EmpAsk()){cout << "empty" << endl; return;}
        Ldat* tmp = head;
        head = (*head).next;
        delete tmp;
    }

    void RB(){
        if(EmpAsk()){cout << "empty" << endl; return;}
        if((*head).next == nullptr){
            delete head;
            strt();
            return;
        }
        Ldat* cur = head;
        while (cur->next->next != nullptr){
            cur = (*cur).next;
        }
        delete (*cur).next;
        (*cur).next = nullptr;
    }

    void prnt(){
        Ldat* cur = head;
        while(cur != nullptr){
            cout << (*cur).dat << " ";
            cur = (*cur).next;
        }
        cout << endl;
    }

    void rever(){
        Ldat* prv = nullptr;
        Ldat* cur = head;
        Ldat* nxt = nullptr;

        while(cur != nullptr){
            nxt = (*cur).next;
            (*cur).next = prv;
            prv = cur;
            cur = nxt;
        }
        head = prv;
    }
};



void tst(){
    Clist<int> com;
    com.strt();
    int c1, c2, i, x;
    cout << "ipf c1: " << endl;
    cin >> c1;
    for (i = 0; i < c1; i += 1){cin >> x; com.PF(x);}
    cout << "ipb c2: " << endl;
    cin >> c2;
    for (i = 0; i < c2; i += 1){cin >> x; com.PB(x);}
    com.prnt();
    com.rever();
    com.prnt();
    com.RF();
    com.RB();
    com.prnt();
}

void tst2(){
    Clist<int> c;
    c.strt();
    long long x, i, cn = 0;
    int co = 1;
    x = 3;
    for (i = 0; i < x; i += 1){
        x += 3;
        c.PF(co);
        co += 1;
        if (co == 1000){
            co = 0;
            cn += 1;
            cout << cn << endl;
        }
        if (cn == 1059991){break;}
    }
    c.rever();
    c.prnt();
}

void ts1(){
    Clist<int> com;
    com.strt();

    int i, n, x;
    cin >> n;
    for (i = 0; i < n; i += 1){cin >> x; com.PB(x);}

    com.prnt();
    com.rever();
    com.prnt();    
}

void ts2(){
    Clist<int> com;
    com.strt();

    int i, n, x, k;
    cin >> n;
    for (i = 0; i < n; i += 1){cin >> x; com.PB(x);}

    com.prnt();

    cout << "k: " << endl;
    cin >> k;

    com.rever();

    Clist<int>::Ldat* first = com.head;
    Clist<int>::Ldat* second = com.head;
    for (i = 0; i < k; i += 1) {
        if (first == nullptr) {     
            cout << "empty" << endl;
            return;
        }
        first = (*first).next;
    }
    while (first != nullptr) {
        first = (*first).next;
        second = (*second).next;
    }
    cout << (*second).dat << endl;
}



int main(){
    //tst();
    //tst2();

    //ts1();
    //ts2();
    return 0;
}
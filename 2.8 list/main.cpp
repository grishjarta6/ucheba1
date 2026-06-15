#include <iostream>
//#include <list>
using namespace std;
struct Node{
	int data;
	Node* next;
};

struct MyList {
	Node* head;
	void init() { head = nullptr;}
	void push_front(int el);
	void push_back(int el);
	void remove_front();
	void remove_back();
	bool is_empty() { return (head == nullptr); }
	void print();
    void reverse();
};

void MyList::remove_back()
{
	if (head == nullptr)
		return;
	if (head->next == nullptr)
	{
		delete head;
		head = nullptr;
		return;
	}
	Node* cur = head;
	while (cur->next->next != nullptr)
		cur = cur->next;
	delete cur->next;
	cur->next = nullptr;
}
void MyList::remove_front()
{
	if (head == nullptr)
		return;
	Node* tmp = head;
	head = head->next;
	delete tmp;
}
void MyList::push_back(int el)
{
	Node* new_node = new Node;
	new_node->data = el;
	new_node->next = nullptr;
	Node* cur = head;
	if (head == nullptr)
		head = new_node;
	else
	{
		while (cur->next != nullptr)
			cur = cur->next;
		cur->next = new_node;
	}
}
void MyList::push_front(int el)
{
	Node* new_node = new Node;
	new_node->data = el;
	new_node->next = head;
	head = new_node;
}
void MyList::print()
{
	Node* cur = head;
	while (cur != nullptr)
	{
		cout << cur->data << " -> ";
		cur = cur->next;
	}
	cout << "nullptr\n";
}

void MyList::reverse() {
    Node* prev = nullptr;
    Node* cur = head;
    Node* nxt = nullptr;
    while (cur != nullptr) {
        nxt = cur->next;   // запоминаем следующий элемент
        cur->next = prev;  // разворачиваем связь
        prev = cur;        // сдвигаем prev вперёд
        cur = nxt;         // переходим к следующему
    }
    head = prev;           
}

void ts1(){
    MyList lst;
    int n, x, i;

    cin >> n;
    for (i = 0; i <= n; i += 1){
        cin >> x;
        lst.push_front(x);
    }
    lst.print();
    lst.reverse();
    lst.print();

}

void ts2() {
    MyList list;
    int k, n, x;
    
    // Ввод: сначала k (номер с конца), затем n (количество элементов), затем сами элементы
    cin >> k;
    cin >> n;
    
    // Заполняем список (push_front - порядок будет обратным)
    for (int i = 0; i < n; ++i) {
        cin >> x;
        list.push_front(x);
    }
    // Разворачиваем список: теперь k-й с конца стал k-м с начала
    list.reverse();    
    // Ищем k-й элемент с начала (индексация с 1)
    Node* cur = list.head;
    for (int i = 1; i < k; ++i) {
        cur = cur->next;
    }
    
    // Выводим результат
    cout << cur->data << endl;
}

int main(){
    //ts1
	ts2();

    return 0;

}

// int main()
// {
// 	MyList my_list;
// 	my_list.init();
// 	my_list.push_front(-1);
// 	my_list.push_front(-2);
// 	my_list.push_back(1);
// 	my_list.push_back(2);
// 	my_list.push_back(3);
// 	my_list.remove_front();
// 	my_list.remove_back();
// 	my_list.print();
// }
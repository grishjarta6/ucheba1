// ConsoleApplication5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

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
};
int main()
{
	MyList my_list;
	my_list.init();
	my_list.push_front(-1);
	my_list.push_front(-2);
	my_list.push_back(1);
	my_list.push_back(2);
	my_list.push_back(3);
	my_list.remove_front();
	my_list.remove_back();
	my_list.print();
}
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

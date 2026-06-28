#include <iostream>
using namespace std;
struct uzel { 
	int data; 
	uzel* next; 
	uzel(int val) : data(val), next(nullptr) {}  
};

class Listuzlov { 
public:
	uzel* head; 
	Listuzlov() : head(nullptr){} 
	void pushfront(int val) { 
		uzel* newuzel = new uzel(val);
		newuzel->next = head; 
		head = newuzel;
	}
	void pushback(int val) {
		uzel* newuzel = new uzel(val);
		if (head == nullptr) {
			head = newuzel;
			return;
		}
		uzel* temp = head;
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = newuzel;
	}
	void print() const {
		uzel* curr = head;
		while (curr != nullptr) {
			cout << curr->data;
			if (curr->next != nullptr) {
				cout << " -> ";
			}
			curr = curr->next;
		}
		cout << " -> nullptr\n";
	}
	void reverse() {
		uzel* prev = nullptr;
		uzel* curr = head;
		uzel* next = nullptr;
		while (curr != nullptr) {
			next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
		}
		head = prev;
	}
	uzel* kfromend(int k) {
		if (k <= 0 || head == nullptr) return nullptr;
		uzel* fast = head;
		uzel* slow = head;
		for (int i = 0; i < k; i++) {
			if (fast == nullptr) return nullptr;
			fast = fast->next;
		}
		while (fast != nullptr) {
			fast = fast->next;
			slow = slow->next;
		}
		return slow;
	}
	void removeval(int val) {
		if (head == nullptr) return;
		if (head->data == val) {
			uzel* temp = head;
			head = head->next;
			delete temp;
			return;
		}
		uzel* curr = head;
		while (curr->next != nullptr) {
			if (curr->next->data == val) {
				uzel* temp = curr->next;
				curr->next = curr->next->next;
				delete temp;
				return;
			}
			curr = curr->next;
		}
	}
	uzel* findmiddle() {
		if (head == nullptr) return nullptr;
		uzel* slow = head;
		uzel* fast = head;
		while (fast != nullptr && fast->next != nullptr) {
			slow = slow->next;
			fast = fast->next->next;
		}
		return slow;
	}

	static uzel* mergetwosorted(uzel* l1, uzel* l2) {
		uzel dummy(0);
		uzel* tail = &dummy;
		while (l1 != nullptr && l2 != nullptr) {
			if (l1->data <= l2->data) {
				tail->next = l1;
				l1 = l1->next;}
			else {
				tail->next = l2;
				l2 = l2->next;
			}
			tail = tail->next;
		}
		tail->next = (l1 != nullptr) ? l1 : l2;
		return dummy.next;
	}
	~Listuzlov() {
		uzel* curr = head;
		while (curr != nullptr) {
			uzel* temp = curr;
			curr = curr->next;
			delete temp;
		}
	}
};

struct DNode {
	int data;
	DNode* prev;
	DNode* next;

	DNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
public:
	DNode* head;
	DNode* tail;

	DoublyLinkedList() : head(nullptr), tail(nullptr) {}

	void push_front(int val) {
		DNode* node = new DNode(val);
		if (head == nullptr) {
			head = tail = node;
		}
		else {
			node->next = head;
			head->prev = node;
			head = node;
		}
	}

	void push_back(int val) {
		DNode* node = new DNode(val);
		if (tail == nullptr) {
			head = tail = node;
		}
		else {
			node->prev = tail;
			tail->next = node;
			tail = node;
		}
	}

	void print() const {
		DNode* curr = head;
		while (curr != nullptr) {
			cout << curr->data;
			if (curr->next != nullptr) cout << " <-> ";
			curr = curr->next;
		}
		cout << " nullptr\n";
	}

	~DoublyLinkedList() {
		DNode* curr = head;
		while (curr != nullptr) {
			DNode* temp = curr;
			curr = curr->next;
			delete temp;
		}
	}
};

int main() {
	return 0;
}
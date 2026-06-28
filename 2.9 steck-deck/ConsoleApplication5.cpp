#include <iostream>
using namespace std;
struct Stack {
	int cap;
	int size;
	int* arr;
	int cap0;
	void init() {
		cap0 = 8;
		cap = cap0;
		arr = new int[cap];
		size = 0;
	}
	void remove() { delete[] arr; }
	void pop() { size--; if (size < 0) size = 0; }
	int top() { return arr[size - 1]; }
	bool isempty() { return (size == 0); }
	void push(int x);
};
void Stack::push(int x) {
	if (size == cap) {
		int* tmp = new int[cap + cap0];
		for (int i = 0; i < cap; i++) { tmp[i] = arr[i]; }
		cap += cap0;
		delete[] arr;
		arr = tmp;
	}
	arr[size] = x;
	size++;
}

struct Deque {
	int cap;
	int size;
	int* arr;
	int cap0;
	int front;
	int back;
	void init() {
		cap0 = 8;
		cap = cap0;
		arr = new int[cap];
		size = 0;
		front = 0;
		back = -1;
	}
	void remove() { delete[] arr; }
	bool isempty() { return (size == 0); }
	void resize() {
		int newcap = cap + cap0;
		int* tmp = new int[newcap];
		for (int i = 0; i < size; i++) {
			int idx = (front + i) % cap;
			tmp[i] = arr[idx];
		}
		delete[] arr;
		arr = tmp;
		front = 0;
		back = size - 1;
		cap = newcap;
	}
	void pushfront(int x) {
		if (size == cap) resize();
		if (size == 0) {
			front = 0;
			back = 0;
			arr[0] = x;
		}
		else {
			front = (front - 1 + cap) % cap;
			arr[front] = x;
		}
		size++;
	}
	void pushback(int x) {
		if (size == cap) resize();
		if (size == 0) {
			front = 0;
			back = 0;
			arr[0] = x;
		}
		else {
			back = (back + 1) % cap;
			arr[back] = x;
		}
		size++;
	}
	void popback() {
		if (size == 0) return;
		if (size == 1) {
			front = 0;
			back = -1;
		}
		else {
			back = (back - 1 + cap) % cap;
		}
		size--;
	}
	void popfront() {
		if (size == 0) return;
		if (size == 1) {
			front = 0;
			back = -1;
		}
		else {
			front = (front + 1) % cap;
		}
		size--;
	}
	int getfront() { return arr[front]; }
	int getback() { return arr[back]; }
};
void taskA() {
	char ch;
	int otkr = 0;
	while (cin.get(ch) && ch != '\n') {
		if (ch == '(') { otkr++; }
		else if (ch == ')' && otkr != 0) { otkr--; }
		else { otkr--;  break; }
	}
	if (otkr == 0) cout << "yes";
	else cout << "no";
}
void taskB() {
	char ch;
	Stack st;
	st.init();
	bool nice = true;
	while (cin.get(ch) && ch != '\n' && nice) {
		if (ch == '(' || ch == '{' || ch == '[') { st.push(ch); }
		else if (ch == ')') {
			if (st.isempty() || st.top() != '(') nice = false;
			else st.pop();
		}
		else if (ch == '}') {
			if (st.isempty() || st.top() != '{') nice = false;
			else st.pop();
		}
		else if (ch == ']') {
			if (st.isempty() || st.top() != '[') nice = false;
			else st.pop();
		}
	}
	if (!st.isempty()) nice = false;
	cout << (nice ? "yes" : "no");
	st.remove();
}
void taskC() {
	Stack st;
	st.init();
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int type;
		cin >> type;
		if (type == 0) {
			int x;
			cin >> x;
			st.push(x);
		}
		else {
			int b = st.top();
			st.pop();
			int a = st.top();
			st.pop();
			if (type == 1) st.push(a + b);
			else if (type == 2) st.push(a - b);
			else if (type == 3) st.push(a * b);
		}
	}
	cout << st.top();
	st.remove();
}
void taskD() {
	int q;
	cin >> q;
	Stack st;
	Stack mn;
	st.init();
	mn.init();

	for (int i = 0; i < q; i++) {
		int type;
		cin >> type;
		if (type == 1) {
			long long x;
			cin >> x;
			st.push(x);
			if (mn.isempty() || x <= mn.top()) {
				mn.push(x);
			}
		}
		else if (type == 2) {
			long long x = st.top();
			cout << x << '\n';
			if (x == mn.top()) {
				mn.pop();
			}
			st.pop();
		}
		else if (type == 3) {
			cout << mn.top() << '\n';
		}
	}
	st.remove();
	mn.remove();
}
void taskE() {
	int q;
	cin >> q;
	Deque dq;
	Deque mindq;
	dq.init();
	mindq.init();
	for (int i = 0; i < q; i++) {
		int type;
		cin >> type;
		if (type == 1) {
			long long x;
			cin >> x;
			dq.pushback(x);
			while (!mindq.isempty() && (mindq.getback() > x)) {
				mindq.popback();
			}
			mindq.pushback(x);
		}
		else if (type == 2) {
			long long val = dq.getfront();
			cout << val << endl;
			if (val == mindq.getfront()) {
				mindq.popfront();
			}
			dq.popfront();
		}
		else if (type == 3) {
			int idx;
			cin >> idx;
			int realidx = (dq.front + idx - 1) % dq.cap;
			cout << dq.arr[realidx];
		}
		else if (type == 4) {
			cout << mindq.getfront();
		}
	}
	dq.remove();
	mindq.remove();
}
int main() {
	taskE();
	/*Stack st;
	st.init();
	for (int i = 0; i < 15; i++) {
	 st.push(i);
	 cout << st.top() << endl;
	}
	st.remove();*/
	/*Deque dq;
	dq.init();
	dq.pushfront(1);
	dq.pushback(10);
	dq.pushfront(2);
	dq.pushfront(3);
	dq.pushfront(4);
	dq.pushfront(5);
	dq.pushfront(6);
	dq.pushfront(7);
	dq.pushfront(8);
	dq.pushfront(9);
	cout << dq.getback();*/
	return 0;
}
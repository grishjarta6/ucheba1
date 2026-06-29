#include <iostream>
#include <vector>
using namespace std;

int n, k;
vector<long long> a;
vector<long long> tree;

void build(int v, int l, int r) {
	if (l == r) {
		tree[v] = a[l];
		return;
	}
	int mid = (l + r) / 2;
	build(v * 2, l, mid);
	build(v * 2 + 1, mid + 1, r);
	tree[v] = tree[v * 2] + tree[v * 2 + 1]; // почему именно v*2? нельзя ли просто v+1 и v+1+1?
}
void update(int v, int l, int r, int pos, long long newval) {
	if (l == r) {
		tree[v] = newval;
		a[pos] = newval;
		return;
	}
	int mid = (l + r) / 2;
	if (pos <= mid) update(v * 2, l, mid, pos, newval);
	else update(v * 2 + 1, mid + 1, r, pos, newval);
	tree[v] = tree[v * 2] + tree[v * 2 + 1];
}
long long query(int v, int l, int r, int ql, int qr) { // ql and qr - и то, и то весь запрос?
	if (ql == l && qr == r) return tree[v];
	int mid = (l + r) / 2;
	if (qr <= mid) return query(v * 2, l, mid, ql, qr);
	if (ql > mid) return query(v * 2 + 1, mid + 1, r, ql, qr);
	return query(v * 2, l, mid, ql, mid) + query(v * 2 + 1, mid + 1, r, mid + 1, qr);
}

void task1() {
	cin >> n >> k;
	a.assign(n, 0);
	tree.assign(4 * n, 0);
	build(1, 0, n - 1);
	while (k > 0) {
		char c;
		cin >> c;
		if (c == 'A') {
			int i;
			long long x;
			cin >> i >> x;
			update(1, 0, n - 1, i - 1, x);
		}
		else {
			int l, r;
			cin >> l >> r;
			cout << query(1, 0, n - 1, l - 1, r - 1) << endl;
		}
		k--;
	}
}

struct Node {
	int val;
	int idx;
};
vector<int> a2;
vector<Node> tree2;
Node bigger(Node a, Node b) {
	if (a.val > b.val) return a;
	else return b;
}
void build2(int v, int l, int r) {
	if (l == r) {
		tree2[v] = { a2[l], l + 1 };
		return;
	}
	int mid = (l + r) / 2;
	build2(v * 2, l, mid);
	build2(v * 2 + 1, mid + 1, r);
	tree2[v] = bigger(tree2[v * 2], tree2[v * 2 + 1]);
}
Node query2(int v, int l, int r, int ql, int qr) {
	if (ql == l && qr == r) return tree2[v];
	int mid = (l + r) / 2;
	if (qr <= mid) return query2(v * 2, l, mid, ql, qr);
	if (ql > mid) return query2(v * 2 + 1, mid + 1, r, ql, qr);
	Node left = query2(v * 2, l, mid, ql, mid);
	Node right = query2(v * 2 + 1, mid + 1, r, mid + 1, qr);
	return bigger(left, right);
}
void task2() {
	cin >> n;
	a2.resize(n);
	tree2.resize(4 * n);
	for (int i = 0; i < n; i++) {
		cin >> a2[i];
	}
	build2(1, 0, n - 1);
	cin >> k;
	while (k > 0) {
		int l, r;
		cin >> l >> r;
		Node ans = query2(1, 0, n - 1, l - 1, r - 1);
		cout << ans.val << " " << ans.idx << endl;
		k--;
	}
}

int m;
vector<int> a3;
vector<int> tree3;
int nod(int a, int b) {
	if (b == 0) return a;
	return nod(b, a % b);
}
void build3(int v, int l, int r) {
	if (l == r) {
		tree3[v] = a3[l];
		return;
	}
	int mid = (l + r) / 2;
	build3(v * 2, l, mid);
	build3(v * 2 + 1, mid + 1, r);
	tree3[v] = nod(tree3[v * 2], tree3[v * 2 + 1]);
}
void update3(int v, int l, int r, int pos, int val) {
	if (l == r) {
		tree3[v] = val;
		a3[pos] = val;
		return;
	}
	int mid = (l + r) / 2;
	if (pos <= mid) update3(v * 2, l, mid, pos, val);
	else update3(v * 2 + 1, mid + 1, r, pos, val);
	tree3[v] = nod(tree3[v * 2], tree3[v * 2 + 1]);
}
int query3(int v, int l, int r, int ql, int qr) {
	if (ql == l && qr == r) return tree3[v];
	int mid = (l + r) / 2;
	if (qr <= mid) return query3(v* 2, l, mid, ql, qr);
	if (ql > mid) return query3(v * 2 + 1, mid + 1, r, ql, qr);
	return nod(query3(v * 2, l, mid, ql, mid), query3(v * 2 + 1, mid + 1, r, mid + 1, qr));
}
void task3() {
	cin >> n;
	a3.resize(n);
	tree3.resize(4 * n);
	for (int i = 0; i < n; i++) cin >> a3[i];
	build3(1, 0, n - 1);
	cin >> m;
	while (m > 0) {
		char c;
		cin >> c;
		if (c == 's') {
			int l, r;
			cin >> l >> r;
			cout << query3(1, 0, n - 1, l - 1, r - 1) << " ";
		}
		else {
			int pos, val;
			cin >> pos >> val;
			update3(1, 0, n - 1, pos - 1, val);
		}
		m--;
	}
}

int main() {
	task3();
	return 0;
}
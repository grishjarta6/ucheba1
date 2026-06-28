#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>> mass;
vector<bool> used;
vector<int> group;
vector<int> sost;
int n;
int k;
bool ok;

void task1() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> arr(n, vector<int>(n, 0));
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		arr[a - 1][b - 1] = 1;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}
void task2() {
	int n, m;
	cin >> n >> m;
	vector<int> step(n, 0);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		step[a - 1]++;
		step[b - 1]++;
	}
	for (int i = 0; i < n; i++) {
		cout << step[i] << " ";
	}
}

void dfs3(int v) {
	used[v] = true;
	k++;
	for (int i = 0; i < n; i++) {
		if (mass[v][i] == 1 && used[i] == false) dfs3(i);
	}
}

void task3() {
	int s;
	cin >> n >> s;
	mass.assign(n, vector<int>(n));
	used.assign(n, false);
	k = 0;
	for (int i = 0; i < n; i++) {
		mass[i].resize(n);
		for (int j = 0; j < n; j++) {
			cin >> mass[i][j];
		}
	}
	dfs3(s - 1);
	cout << k;
}

void dfs4(int v, int g) {
	group[v] = g;
	for (int i : mass[v]) {
		if (group[i] == -1) dfs4(i, 1 - g);
		else if (group[i] == g) ok = false;
	}
}
void task4() {
	int n, m;
	cin >> n >> m;
	mass.assign(n, vector<int>());
	group.assign(n, -1);
	ok = true;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		mass[a].push_back(b);
		mass[b].push_back(a);
	}
	for (int i = 0; i < n; i++) {
		if (group[i] == -1) {
			dfs4(i, 0);
		}
	}
	if (ok) {
		cout << "YES";
	}
	else cout << "NO";
}

void dfs5(int v) {
	sost[v] = 1;
	for (int i : mass[v]) {
		if (sost[i] == 0) dfs5(i);
		else if (sost[i] == 1) ok = true;
	}
	sost[v] = 2;
}
void task5() {
	int n, m;
	cin >> n >> m;
	mass.assign(n, vector<int>());
	sost.assign(n, 0);
	ok = false;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		mass[a].push_back(b);
	}
	for (int i = 0; i < n; i++) {
		if (sost[i] == 0) dfs5(i);
	}
	if (ok) cout << 1;
	else cout << 0;
}

void dfs6(int v, int par) {
	used[v] = true;
	for (int i : mass[v]) {
		if (used[i] == false) dfs6(i, v);
		else if (i != par) ok = true;
	}
}
void task6() {
	int n, m;
	cin >> n >> m;
	mass.assign(n, vector<int>());
	used.assign(n, false);
	ok = false;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		mass[a].push_back(b);
		mass[b].push_back(a);
	}
	dfs6(0, -1);
	for (int i = 0; i < n; i++) {
		if (used[i] == false) { cout << "NO"; return; }
	}
	if (ok) cout << "NO";
	else cout << "YES";
}

void dfs7(int v, vector<int>& comp) {
	used[v] = true;
	comp.push_back(v);
	for (int i : mass[v]) {
		if (used[i] == false) dfs7(i, comp);
	}
}
void sortVector(vector<int>& a) {
	for (int i = 0; i < a.size(); i++) {
		for (int j = i + 1; j < a.size(); j++) {
			if (a[i] > a[j]) swap(a[i], a[j]);
		}
	}
}
void task7() {
	int n, m;
	cin >> n >> m;
	mass.assign(n, vector<int>());
	used.assign(n, false);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		mass[a].push_back(b);
		mass[b].push_back(a);
	}
	vector<vector<int>> components;
	for (int i = 0; i < n; i++) {
		if (used[i] == false) {
			vector<int> comp;
			dfs7(i, comp);
			sortVector(comp);
			components.push_back(comp);
		}
	}
	cout << components.size() << endl;
	for (int i = 0; i < components.size(); i++) {
		cout << components[i].size() << endl;
		for (int j = 0; j < components[i].size(); j++) {
			cout << components[i][j] + 1 << " ";
		}
		cout << endl;
	}
}
int main() {
	task7();
	return 0;
}
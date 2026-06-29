#include <iostream>
#include <vector>
#include <queue>
#include <deque>
using namespace std;

void task1() {
	int n, m, s;
	cin >> n >> m >> s;
	s--;
	vector<vector<int>> graph(n);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	vector<int> dist(n, -1);
	queue<int> q;
	dist[s] = 0;
	q.push(s);
	while (q.empty() == false) {
		int v = q.front();
		q.pop();
		for (int to : graph[v]) {
			if (dist[to] == -1) {
				dist[to] = dist[v] + 1;
				q.push(to);
			}
		}
	}
	for (int x : dist) cout << x << " ";
}

void task2() {
	int n, k;
	cin >> n >> k;
	vector<vector<int>> graph(n);
	vector<int> dist(n, -1);
	queue<int> q;
	for (int i = 0; i < k; i++) {
		int x;
		cin >> x;
		x--;
		dist[x] = 0;
		q.push(x);
	}
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	while (q.empty() == false) {
		int v = q.front();
		q.pop();
		for (int to : graph[v]) {
			if (dist[to] == -1) {
				dist[to] = dist[v] + 1;
				q.push(to);
			}
		}
	}
	for (int x : dist) cout << x << " ";
}

void task3() {
	int n, m, s;
	cin >> n >> m >> s;
	s--;
	const int INF = 1e9;
	vector<vector<pair<int, int>>> graph(n);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--; b--;
		graph[a].push_back({ b,c });
		graph[b].push_back({ a,c });
	}
	vector<int> dist(n, INF);
	deque<int> dq;
	dist[s] = 0;
	dq.push_front(s);
	while (dq.empty() == false) {
		int v = dq.front();
		dq.pop_front();
		for (pair<int, int> edge : graph[v]) {
			int to = edge.first;
			int w = edge.second;
			if (dist[to] > dist[v] + w) {
				dist[to] = dist[v] + w;
				if (w == 0) dq.push_front(to);
				else dq.push_back(to);
			}
		}
	}
	for (int x : dist) {
		if (x == INF) cout << -1 << " ";
		else cout << x << " ";
	}
}

int main() {
	task3();
	return 0;
}
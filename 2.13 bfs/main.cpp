#include <iostream>
#include <vector>
#include <queue>
#include <deque>

using namespace std;

void za(){
    int n, m, s;
    int i, u, v;
    vector<vector<int> > graph;
    vector<int> dist;
    queue<int> q;

    cin >> n >> m >> s;
    graph.resize(n + 1);
    dist.assign(n + 1, -1);

    for (i = 0; i < m; i = i + 1) {
        cin >> u >> v;
        graph[static_cast<size_t>(u)].push_back(v);
        graph[static_cast<size_t>(v)].push_back(u);
    }

    dist[static_cast<size_t>(s)] = 0;
    q.push(s);

    while (q.empty() == false) {
        u = q.front();
        q.pop();
        for (i = 0; i < (int)graph[static_cast<size_t>(u)].size(); i = i + 1) {
            v = graph[static_cast<size_t>(u)][i];
            if (dist[static_cast<size_t>(v)] == -1) {
                dist[static_cast<size_t>(v)] = dist[static_cast<size_t>(u)] + 1;
                q.push(v);
            }
        }
    }

    for (i = 1; i <= n; i = i + 1) {
        cout << dist[static_cast<size_t>(i)];
        if (i != n) cout << ' ';
    }
    cout << endl;
}

void zb(){
    int n, k, m;
    int i, u, v, exit_node;
    vector<vector<int> > bunkers;
    vector<int> dist;
    queue<int> q;

    cin >> n >> k;
    bunkers.resize(n + 1);
    dist.assign(n + 1, -1);

    for (i = 0; i < k; i = i + 1) {
        cin >> exit_node;
        dist[static_cast<size_t>(exit_node)] = 0;
        q.push(exit_node);
    }

    cin >> m;
    for (i = 0; i < m; i = i + 1) {
        cin >> u >> v;
        bunkers[static_cast<size_t>(u)].push_back(v);
        bunkers[static_cast<size_t>(v)].push_back(u);
    }

    while (q.empty() == false) {
        u = q.front();
        q.pop();
        for (i = 0; i < (int)bunkers[static_cast<size_t>(u)].size(); i = i + 1) {
            v = bunkers[static_cast<size_t>(u)][i];
            if (dist[static_cast<size_t>(v)] == -1) {
                dist[static_cast<size_t>(v)] = dist[static_cast<size_t>(u)] + 1;
                q.push(v);
            }
        }
    }

    for (i = 1; i <= n; i = i + 1) {
        cout << dist[static_cast<size_t>(i)];
        if (i != n) cout << ' ';
    }
    cout << endl;
}

void zc(){
    int n, m, s;
    int i, u, v, w;
    vector<vector<int> > graph;
    vector<int> dist;
    deque<int> dq;

    cin >> n >> m >> s;
    graph.resize(n + 1);
    dist.assign(n + 1, -1);

    for (i = 0; i < m; i = i + 1) {
        cin >> u >> v >> w;
        graph[static_cast<size_t>(u)].push_back(v);
        graph[static_cast<size_t>(u)].push_back(w);
        graph[static_cast<size_t>(v)].push_back(u);
        graph[static_cast<size_t>(v)].push_back(w);
    }

    dist[static_cast<size_t>(s)] = 0;
    dq.push_back(s);

    while (dq.empty() == false) {
        u = dq.front();
        dq.pop_front();
        for (i = 0; i < (int)graph[static_cast<size_t>(u)].size(); i = i + 2) {
            v = graph[static_cast<size_t>(u)][i];
            w = graph[static_cast<size_t>(u)][i + 1];
            if (dist[static_cast<size_t>(v)] == -1 or dist[static_cast<size_t>(u)] + w < dist[static_cast<size_t>(v)]) {
                dist[static_cast<size_t>(v)] = dist[static_cast<size_t>(u)] + w;
                if (w == 0) {
                    dq.push_front(v);
                } else {
                    dq.push_back(v);
                }
            }
        }
    }

    for (i = 1; i <= n; i = i + 1) {
        cout << dist[static_cast<size_t>(i)];
        if (i != n) cout << ' ';
    }
    cout << endl;
}

int main(){
    za();   
    // zb();   
    // zc();   
    return 0;
}
#include <iostream>
using namespace std;

void taskA() {
	int n;
	cin >> n;
	if (n <= 2) {
		cout << 1;
		return;
	}
	long long f[46];
	f[1] = 1;
	f[2] = 1;
	for (int i = 3; i <= n; i++) {
		f[i] = f[i - 1] + f[i - 2];
	}
	cout << f[n];
}

void taskB() {
	int n;
	cin >> n;
	int stup[101];
	for (int i = 0; i <= n; i++) {
		cin >> stup[i];
	}
	int minway[102];
	minway[0] = 0;
	if (n >= 1) minway[1] = stup[0];
	for (int i = 2; i <= n; i++) {
		minway[i] = stup[i - 1] + min(minway[i - 1], minway[i - 2]);
	}
	cout << minway[n];
}

void taskC() {
	int n, m;
	cin >> n >> m;
	int tabl[101][101];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> tabl[n][m];
		}
	}
	int dp[101][101];
	int predI[101][101];
	int predJ[101][101];
	dp[0][0] = tabl[0][0];
	for (int j = 1; j < m; j++) {
		dp[0][j] = dp[0][j - 1] + tabl[0][j];
		predI[0][j] = 0;
		predJ[0][j] = j - 1;
	}
	for (int i = 1; i < n; i++) {
		dp[i][0] = dp[i - 1][0] + tabl[i][0];
		predI[i][0] = i - 1;
		predJ[i][0] = 0;
	}
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < m; j++) {
			if (dp[i - 1][j] >= dp[i][j - 1]) {
				dp[i][j] = dp[i - 1][j] + tabl[i][j];
				predI[i][j] = i - 1;
				predJ[i][j] = j;
			}
			else {
				dp[i][j] = dp[i][j - 1] + tabl[i][j];
				predI[i][j] = i;
				predJ[i][j] = j - 1;
			}
		}
	}
	cout << dp[n - 1][m - 1];

	char way[201];
	int len = 0;
	int i = n - 1, j = m - 1;
	while (i != 0 || j != 0) {
		if (predI[i][j] == i - 1) way[len++] = 'D';
		else way[len++] = 'R';
		int tempi = predI[i][j];
		int tempj = predJ[i][j];
		i = tempi;
		j = tempj;
	}
	for (int k = len - 1; k >= 0; k--) {
		cout << way[k];
	}
}

void taskD() {
	int n, m;
	cin >> n >> m;
	long long dp[51][51];
	dp[0][0] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (dp[i][j] == 0) continue;
			if (i + 2 < n && j + 1 < m) dp[i + 2][j + 1] += dp[i][j];
			if (i + 1 < n && j + 2 < m) dp[i + 1][j + 2] += dp[i][j];
		}
	}
	cout << dp[n - 1][m - 1];
}

void taskE() {
	int n, m;
	cin >> n >> m;
	long long dp[16][16];
	dp[0][0] = 1;
	int dx[8] = { -2, 2, 2, -2, -1, 1, 1, -1 };
	int dy[8] = { -1, -1, 1, 1, -2, -2, 2, 2 };
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (dp[i][j] == 0) continue;
			for (int k = 0; k < 8; k++) {
				int ni = i + dx[k];
				int nj = j + dx[k];
				if (ni >= 0 && ni < n && nj >= 0 && nj < m) dp[ni][nj] += dp[i][j];
			}
		}
	}
	cout << dp[n - 1][m - 1];
}

int main() {
	taskA();
	return 0;
}
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> duraciones;
vector<vector<int>> prereqs;
vector<long long> memo;
vector<bool> calculado;

long long ef(int v) {
	if (calculado[v]) return memo[v];

	long long mejor = 0;
	for (int p : prereqs[v]) {
		mejor = max(mejor, ef(p));
	}

	memo[v] = mejor + duraciones[v];
	calculado[v] = true;
	return memo[v];
}

void tc() {
	cin >> n;
	duraciones.assign(n, 0);
	for (int i = 0; i < n; ++i) cin >> duraciones[i];

	prereqs.assign(n, {});
	for (int i = 0; i < n; ++i) {
		int k; cin >> k;
		prereqs[i].resize(k);
		for (int j = 0; j < k; ++j) cin >> prereqs[i][j];
	}

	memo.assign(n, 0);
	calculado.assign(n, false);

	cout << ef(n - 1) << "\n";
}

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	int T;
	cin >> T;
	while (T--) tc();
}

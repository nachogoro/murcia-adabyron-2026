#include <bits/stdc++.h>
using namespace std;

void tc() {
	int n;
	cin >> n;
	vector<int> duraciones(n);

	for (int i = 0; i < n; ++i)
		cin >> duraciones[i];

	vector<vector<int>> hijos(n);
	vector<int> dependencias_incompletas(n, 0);
	for (int i = 0; i < n; ++i) {
		int k;
		cin >> k;
		for (int j = 0; j < k; ++j) {
			int p;
			cin >> p;
			hijos[p].push_back(i);
			dependencias_incompletas[i]++;
		}
	}

	vector<long long> ef(n, 0);
	queue<int> tareas;
	tareas.push(0);
	while (!tareas.empty()) {
		int tarea = tareas.front(); tareas.pop();
		ef[tarea] += duraciones[tarea];

		for (int hijo : hijos[tarea]) {
			ef[hijo] = max(ef[hijo], ef[tarea]);
			if (--dependencias_incompletas[hijo] == 0) {
				tareas.push(hijo);
			}
		}
	}

	cout << ef[n-1] << "\n";
}

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	int T;
	cin >> T;
	while (T--) {
		tc();
	}
}

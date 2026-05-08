#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	int T;
	cin >> T;
	while (T--) {
		ll D;
		cin >> D;

		ll N, M;
		cin >> N >> M;

		vector<ll> cpus(N), gpus(M);
		for (int i = 0; i < N; ++i) cin >> cpus[i];
		for (int i = 0; i < M; ++i) cin >> gpus[i];

		sort(cpus.begin(), cpus.end());
		sort(gpus.begin(), gpus.end());

		// Dos punteros: i recorre CPUs de barata a cara, j recorre GPUs
		// de cara a barata.
		// - Si cpus[i] + gpus[j] > D, la GPU j es demasiado cara para
		//   cualquier CPU >= cpus[i] (que solo serán más caras), así
		//   que la descartamos: --j.
		// - Si cpus[i] + gpus[j] <= D, la pareja es válida. Para esta
		//   CPU la GPU j es la más cara que cabe (cualquier j' > j ya
		//   ha sido descartado), así que actualizamos el máximo y
		//   pasamos a la siguiente CPU: ++i.
		ll best = -1;
		int i = 0, j = M - 1;
		while (i < N && j >= 0) {
			ll sum = cpus[i] + gpus[j];
			if (sum > D) {
				--j;
			} else {
				best = max(best, sum);
				++i;
			}
		}
		cout << best << "\n";
	}
}

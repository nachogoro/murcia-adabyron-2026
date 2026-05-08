#include <bits/stdc++.h>
using namespace std;

using ll = long long;

optional<ll> max_leq(const vector<ll>& v, ll x) {
    auto it = upper_bound(v.begin(), v.end(), x);
    if (it == v.begin()) return nullopt;
    return *(--it);
}

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

		vector<ll> cpus(N);
		vector<ll> gpus(M);

		for (int i = 0; i < N; ++i) cin >> cpus[i];
		for (int i = 0; i < M; ++i) cin >> gpus[i];

		sort(gpus.begin(), gpus.end());

		ll most_expensive = -1;

		for (auto c1 : cpus) {
			ll remaining = D - c1;
			auto c2 = max_leq(gpus, remaining);

			if (!c2) continue;

			most_expensive = max(most_expensive, c1 + *c2);
		}

		cout << most_expensive << "\n";
	}
}

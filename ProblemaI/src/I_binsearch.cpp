#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// Búsqueda binaria sobre k de forma que k*(k+1) == N, sin tocar coma
// flotante. La función k -> k*(k+1) es estrictamente creciente para
// k >= 1, así que es directo.
//
// Cota superior: con N <= 10^18 y k(k+1) >= k^2, el k buscado cumple
// k <= sqrt(N) < 10^9 + 1. Tomamos como cota holgada 2*10^9, que
// también cabe en long long.
bool es_oblongo(ll N) {
	ll lo = 1, hi = 2'000'000'000LL;
	while (lo <= hi) {
		ll mid = lo + (hi - lo) / 2;
		ll prod = mid * (mid + 1);
		if (prod == N) return true;
		if (prod < N) lo = mid + 1;
		else          hi = mid - 1;
	}
	return false;
}

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	ll N;
	while (cin >> N && N != 0) {
		cout << (es_oblongo(N) ? "SI" : "NO") << "\n";
	}
}

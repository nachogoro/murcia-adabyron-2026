#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// Búsqueda ternaria sobre la función g(k) = |N - k(k+1)|.
//
// g es unimodal en V para k in [1, 2*10^9]: decrece estrictamente hasta
// que k(k+1) supera a N y desde ahí crece estrictamente. Por tanto la
// ternaria converge al mínimo. Si ese mínimo vale 0, N es oblongo.
//
// Caso especial: si N = (k0+1)^2 (cuadrado perfecto), g(k0) = g(k0+1) =
// k0+1. La ternaria estándar puede terminar en cualquiera de esos dos
// puntos, pero ambos dan el mismo valor no nulo, así que la respuesta
// (no oblongo) sigue siendo correcta.
bool es_oblongo(ll N) {
	auto g = [&](ll k) {
		ll prod = k * (k + 1);
		return prod > N ? prod - N : N - prod;
	};

	ll lo = 1, hi = 2'000'000'000LL;
	while (hi - lo > 2) {
		ll m1 = lo + (hi - lo) / 3;
		ll m2 = hi - (hi - lo) / 3;
		if (g(m1) <= g(m2)) hi = m2 - 1;
		else                lo = m1 + 1;
	}

	for (ll k = lo; k <= hi; ++k) {
		if (g(k) == 0) return true;
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

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	ll N;
	while (cin >> N && N != 0) {
		ll k = (ll) sqrt((double) N);
		cout << (k * (k+1) == N ? "SI" : "NO") << "\n";
	}
}

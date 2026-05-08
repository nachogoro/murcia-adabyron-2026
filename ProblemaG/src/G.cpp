#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	int T;
	cin >> T;
	while (T--) {
		ll N, M, F;
		cin >> N >> M >> F;
		set<ll> crops;
		set<ll> no_crops;
		while (F--) {
			ll x, y;
			cin >> x >> y;
			cin.ignore();
			array<string, 3> pic;
			for (int i = 0; i < 3; ++i) {
				getline(cin, pic[i]);
			}

			for (int i = 0; i < 3; ++i) {
				for (int j = 0; j < 3; ++j) {
					if (pic[i][j] == '#') {
						crops.insert((x + i) * M + (y + j));
					} else {
						no_crops.insert((x + i) * M + (y + j));
					}
				}
			}
		}

		cout << crops.size() << " " << N*M - no_crops.size() << "\n";
	}
}

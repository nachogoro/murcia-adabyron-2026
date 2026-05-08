#include <bits/stdc++.h>
using namespace std;

int main() {
	int T;
	cin >> T;

	while (T--) {
		int N, D;
		cin >> N >> D;

		int fallos{0};
		while (N--) {
			int v;
			cin >> v;
			if (v <= D) fallos++;
		}

		if (fallos == 0) cout << "TODOS\n";
		else cout << fallos << " NO\n";
	}
}

#include <bits/stdc++.h>
using namespace std;

struct Alumno {
	double nota;
	int pos;
	vector<int> prefs;
};

int main() {
	int T;
	cin >> T;
	while (T--) {
		int n, m;
		cin >> n >> m;
		vector<Alumno> alumnos(n);
		for (int i = 0; i < n; ++i) {
			alumnos[i].pos = i;
			cin >> alumnos[i].nota;
		}

		vector<int> cupos(m);
		for (int i = 0; i < m; ++i) {
			cin >> cupos[i];
		}

		for (int i = 0; i < n; ++i) {
			int k;
			cin >> k;
			alumnos[i].prefs.resize(k);
			for (int p = 0; p < k; ++p) {
				cin >> alumnos[i].prefs[p];
			}
		}

		sort(alumnos.begin(), alumnos.end(),
			[](const Alumno& a, const Alumno& b) {
				if (a.nota != b.nota) return a.nota > b.nota;
				return a.pos < b.pos;
			});

		vector<int> asignaciones(n, -1);
		for (auto& [nota, pos, prefs] : alumnos) {
			for (auto pref : prefs) {
				if (cupos[pref] > 0) {
					asignaciones[pos] = pref;
					cupos[pref]--;
					break;
				}
			}
		}

		for (auto asig : asignaciones) {
			cout << asig << "\n";
		}

	}
}

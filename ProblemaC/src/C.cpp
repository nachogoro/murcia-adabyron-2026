#include <bits/stdc++.h>
using namespace std;

struct Fighter {
	int hp, dp;
};

struct LiveFighter {
	int8_t hp, pos;

	bool operator<(const LiveFighter& o) {
		return tie(hp, pos) < tie(o.hp, o.pos);
	}
};

using Team = deque<LiveFighter>;

// Estado dp:
// - Jugador que mueve
// - Alineación de cada uno (orden y HP) (solo luchadores vivos)
struct State {
	bool turno_alfredo;
	Team alfredo;
	Team borja;
	bool operator<(const State& o) const {
		return tie(turno_alfredo, alfredo, borja)
			< tie(o.turno_alfredo, o.alfredo, o.borja);
	}
};

set<State> dp;
vector<Fighter> original_alfredo;
vector<Fighter> original_borja;

// Estado tras un ataque del jugador en turno: el activo golpea al activo
// rival y, si lo deja sin HP, lo retira del equipo. El turno pasa al rival.
State attack(const State& st) {
	State next = st;
	auto& atacante = next.turno_alfredo ? next.alfredo : next.borja;
	auto& defensor = next.turno_alfredo ? next.borja   : next.alfredo;
	const auto& orig_at = next.turno_alfredo ? original_alfredo : original_borja;

	defensor.front().hp -= orig_at[atacante.front().pos].dp;
	if (defensor.front().hp <= 0) defensor.pop_front();

	next.turno_alfredo = !next.turno_alfredo;
	return next;
}

// El jugador en turno solo puede intercambiar si tiene banquillo.
bool canSwap(const State& st) {
	return (st.turno_alfredo ? st.alfredo : st.borja).size() > 1;
}

// Estado tras intercambiar activo y banquillo del jugador en turno y atacar
// con el nuevo activo: equivale a la acción "Intercambiar y atacar" del
// enunciado.
State swap_attack(const State& st) {
	State next = st;
	auto& equipo = next.turno_alfredo ? next.alfredo : next.borja;
	std::swap(equipo[0], equipo[1]);
	return attack(next);
}

bool alfredo_wins(State st) {
	if (dp.count(st)) return false;
	if (st.borja.empty()) return true;
	if (st.alfredo.empty()) {
		dp.insert(st);
		return false;
	}

	// Movimientos disponibles: atacar y, opcionalmente, intercambiar y atacar.
	vector<State> siguientes;
	siguientes.push_back(attack(st));
	if (canSwap(st)) siguientes.push_back(swap_attack(st));

	// Si es el turno de Alfredo: gana si ALGÚN siguiente estado le asegura
	// victoria con juego óptimo.
	// Si es el turno de Borja: Alfredo gana solo si el juego óptimo le asegura
	// la victoria en cualquier estado siguiente.
	bool result = !st.turno_alfredo;
	for (const auto& ns : siguientes) {
		bool would_win = alfredo_wins(ns);
		if (st.turno_alfredo) { if (would_win)  { result = true;  break; } }
		else                  { if (!would_win) { result = false; break; } }
	}

	if (!result) dp.insert(st);
	return result;
}

void tc() {
	dp.clear();
	Team alfredo_lineup;
	for (size_t i = 0; i < original_alfredo.size(); ++i) {
		alfredo_lineup.push_back({
			static_cast<int8_t>(original_alfredo[i].hp),
			static_cast<int8_t>(i)
		});
	}

	Team borja_lineup;
	for (size_t i = 0; i < original_borja.size(); ++i) {
		borja_lineup.push_back({
			static_cast<int8_t>(original_borja[i].hp),
			static_cast<int8_t>(i)
		});
	}

	if (alfredo_wins({true, alfredo_lineup, borja_lineup})) cout << "Alfredo\n";
	else cout << "Borja\n";
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		int N;
		cin >> N;
		original_alfredo = vector<Fighter>(N);
		for (int i = 0; i < N; ++i) {
			cin >> original_alfredo[i].hp >> original_alfredo[i].dp;
		}

		int M;
		cin >> M;
		original_borja = vector<Fighter>(M);
		for (int i = 0; i < M; ++i) {
			cin >> original_borja[i].hp >> original_borja[i].dp;
		}

		tc();
	}
}

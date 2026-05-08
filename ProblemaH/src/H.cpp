#include <bits/stdc++.h>
using namespace std;

// Resolución del Lineanograma con DP sufijo top-down + memoización.
//
//   resolver(i, j) = "¿se pueden cubrir las celdas [i, N) usando los
//                     bloques (j+1)..M?"
//
// Es decir, ya hemos procesado las celdas [0, i) colocando los j primeros
// bloques de forma consistente, y nos queda decidir el resto. La respuesta
// global es resolver(0, 0).
//
// En cada estado solo hay dos transiciones posibles:
//
//   (A) dejar la celda i en blanco         -> resolver(i + 1, j)
//   (B) empezar aquí el bloque (j+1)-ésimo -> resolver(i + a[j+1] + 1, j+1)
//                                             (el +1 es el separador
//                                              obligatorio tras el bloque)
//
// Como hay como mucho N*M estados y cada uno se resuelve en O(1) gracias a
// las sumas prefijas de abajo, el coste total es O(N*M).

int N, M;
vector<int> a;             // tamaños de los bloques, 1-indexados: a[1..M].
string estado;             // estado parcial: '0' = blanca, '1' = negra, 'X'.

// Sumas prefijas para consultar rangos en O(1):
//   no_blancas[i] = nº de celdas en [0, i) que NO están fijadas a '0'.
//   no_negras[i]  = nº de celdas en [0, i) que NO están fijadas a '1'.
vector<int> no_blancas, no_negras;

// Memo de tres valores: -1 sin calcular, 0 false, 1 true.
vector<vector<int>> memo;

// ¿Pueden todas las celdas en [l, r) ser negras? Equivale a que ninguna
// esté ya fijada a blanca ('0').
bool todo_puede_ser_negro(int l, int r) {
    return no_blancas[r] - no_blancas[l] == r - l;
}

// ¿Pueden todas las celdas en [l, r) ser blancas?
bool todo_puede_ser_blanco(int l, int r) {
    return no_negras[r] - no_negras[l] == r - l;
}

bool resolver(int i, int j) {
    if (memo[i][j] != -1) return memo[i][j];

    // Caso base: ya hemos colocado todos los bloques. Lo único que queda
    // por verificar es que el resto de la línea pueda quedar todo en blanco
    // (ninguna celda esté fijada a '1').
    if (j == M) {
        memo[i][j] = todo_puede_ser_blanco(i, N);
        return memo[i][j];
    }

    // Caso base: se acabaron las celdas pero aún quedan bloques por colocar.
    if (i == N) {
        memo[i][j] = 0;
        return false;
    }

    bool ok = false;

    // (A) Dejar la celda i en blanco. Legal salvo que esté fijada a '1'.
    if (estado[i] != '1' && resolver(i + 1, j)) ok = true;

    // (B) Empezar aquí el bloque (j+1)-ésimo, que ocupa [i, i + len).
    // Necesitamos que esas celdas puedan ser todas negras. Tras el bloque,
    // si no llega al final, hay una celda separadora obligatoria en la
    // posición 'fin', que debe poder ser blanca.
    if (!ok) {
        int len = a[j + 1];
        int fin = i + len;
        if (fin <= N && todo_puede_ser_negro(i, fin)) {
            if (fin == N) {
                // El bloque encaja justo al final: solo es válido si era
                // el último bloque pendiente.
                if (j + 1 == M) ok = true;
            } else if (estado[fin] != '1') {
                // Consumimos también la celda separadora.
                if (resolver(fin + 1, j + 1)) ok = true;
            }
        }
    }

    memo[i][j] = ok ? 1 : 0;
    return ok;
}

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int T;
    cin >> T;
    while (T--) {
        cin >> N >> M;
        a.assign(M + 1, 0);
        for (int k = 1; k <= M; ++k) cin >> a[k];
        cin >> estado;

        no_blancas.assign(N + 1, 0);
        no_negras.assign(N + 1, 0);
        for (int i = 0; i < N; ++i) {
            no_blancas[i + 1] = no_blancas[i] + (estado[i] != '0');
            no_negras[i + 1]  = no_negras[i]  + (estado[i] != '1');
        }

        memo.assign(N + 1, vector<int>(M + 1, -1));

        cout << (resolver(0, 0) ? "SI" : "NO") << "\n";
    }
}

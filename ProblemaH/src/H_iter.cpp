#include <bits/stdc++.h>
using namespace std;

// Resolución del Lineanograma con DP sufijo bottom-up.
//
//   dp[i][j] = "¿hay una extensión válida desde la posición i habiendo
//               colocado ya los j primeros bloques?"
//
// Es decir: todavía quedan por cubrir las celdas [i, N) y por colocar los
// bloques (j+1), ..., M en ese tramo, de manera consistente con el estado
// parcial. La respuesta del problema es dp[0][0] (no hemos procesado
// ninguna celda ni colocado ningún bloque).
//
// Casos base:
//   dp[N][M] = true  (todo cubierto y todos los bloques puestos)
//   dp[i][M] = "todas las celdas restantes pueden ser blancas"
//
// Transiciones desde (i, j) con i < N y j < M:
//   (A) la celda i es blanca           -> dp[i+1][j]
//   (B) empezar aquí el bloque (j+1)   -> dp[i + a[j+1] + 1][j+1]
//                                         (o dp[N][M] si encaja al final)
//
// El orden de iteración es i decreciente y, dentro, j decreciente, para
// que cuando se procesa (i, j) los estados que se consultan ya estén
// resueltos.
//
// Coste: O(N*M) por caso de prueba.

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;
        vector<int> a(M + 1, 0);
        for (int k = 1; k <= M; ++k) cin >> a[k];
        string estado;
        cin >> estado;

        // Sumas prefijas para consultar rangos en O(1).
        //   no_blancas[i] = nº de celdas en [0, i) que NO están fijadas a '0'.
        //   no_negras[i]  = nº de celdas en [0, i) que NO están fijadas a '1'.
        vector<int> no_blancas(N + 1, 0), no_negras(N + 1, 0);
        for (int i = 0; i < N; ++i) {
            no_blancas[i + 1] = no_blancas[i] + (estado[i] != '0');
            no_negras[i + 1]  = no_negras[i]  + (estado[i] != '1');
        }
        auto todo_puede_ser_negro = [&](int l, int r) {
            return no_blancas[r] - no_blancas[l] == r - l;
        };
        auto todo_puede_ser_blanco = [&](int l, int r) {
            return no_negras[r] - no_negras[l] == r - l;
        };

        vector<vector<char>> dp(N + 1, vector<char>(M + 1, 0));

        // Casos base para j == M: queda solo cubrir el resto con blancas.
        for (int i = 0; i <= N; ++i) {
            dp[i][M] = todo_puede_ser_blanco(i, N) ? 1 : 0;
        }

        for (int i = N - 1; i >= 0; --i) {
            for (int j = M - 1; j >= 0; --j) {
                bool ok = false;

                // (A) la celda i es blanca y extendemos desde (i+1, j).
                if (estado[i] != '1' && dp[i + 1][j]) ok = true;

                // (B) empezar aquí el bloque (j+1).
                if (!ok) {
                    int len = a[j + 1];
                    int fin = i + len;
                    if (fin <= N && todo_puede_ser_negro(i, fin)) {
                        if (fin == N) {
                            // Encaja justo al final: válido si era el último.
                            if (j + 1 == M) ok = true;
                        } else if (estado[fin] != '1') {
                            // Consumimos también la celda separadora.
                            if (dp[fin + 1][j + 1]) ok = true;
                        }
                    }
                }

                dp[i][j] = ok ? 1 : 0;
            }
        }

        cout << (dp[0][0] ? "SI" : "NO") << "\n";
    }
}

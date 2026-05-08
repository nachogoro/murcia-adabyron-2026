#include <bits/stdc++.h>
using namespace std;

// Resolución del Lineanograma con DP prefijo bottom-up.
//
//   dp[i][j] = "¿es posible procesar las primeras i celdas habiendo
//               colocado exactamente los j primeros bloques, con la celda
//               i libre para empezar lo que venga?"
//
// Caso base:   dp[0][0] = true.
// Respuesta:   dp[N][M].
//
// Transiciones (estilo "push": desde un estado true, marcamos los estados
// que se pueden alcanzar):
//
//   (A) dejar la celda i en blanco                -> dp[i+1][j]
//   (B) empezar aquí el bloque (j+1)-ésimo        -> dp[i + a[j+1] + 1][j+1]
//                                                    (el +1 es el separador
//                                                     blanco obligatorio
//                                                     tras el bloque)
//
// Como hay como mucho N*M estados y cada uno se procesa en O(1) gracias a
// las sumas prefijas, el coste total es O(N*M).

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

        // dp como char para abaratar memoria; los valores son 0/1.
        vector<vector<char>> dp(N + 1, vector<char>(M + 1, 0));
        dp[0][0] = 1;

        // Iteramos i creciente y, dentro, j creciente. Esto garantiza que
        // cuando procesamos (i, j) ya están resueltas todas las celdas
        // (i', j') con i' < i (o i' = i, j' < j) desde las que se podría
        // haber propagado hasta aquí.
        for (int i = 0; i <= N; ++i) {
            for (int j = 0; j <= M; ++j) {
                if (!dp[i][j]) continue;

                // (A) dejar la celda i en blanco. Solo legal si esa celda
                // no está fijada a '1' y, evidentemente, si existe (i < N).
                if (i < N && estado[i] != '1') {
                    dp[i + 1][j] = 1;
                }

                // (B) empezar aquí el bloque (j+1)-ésimo, que ocupará las
                // celdas [i, i + len). Necesitamos:
                //   - quedar bloques por colocar (j < M).
                //   - que el bloque entero quepa (fin <= N).
                //   - que ninguna de esas celdas esté fijada a '0'.
                if (j < M) {
                    int len = a[j + 1];
                    int fin = i + len;
                    if (fin <= N && todo_puede_ser_negro(i, fin)) {
                        if (fin == N) {
                            // El bloque encaja justo al final. No hace falta
                            // separador; basta con que sea el último bloque.
                            if (j + 1 == M) dp[N][M] = 1;
                        } else if (estado[fin] != '1') {
                            // Hay celda separadora obligatoria en posición
                            // 'fin' y debe poder ser blanca. La consumimos
                            // como parte de la transición.
                            dp[fin + 1][j + 1] = 1;
                        }
                    }
                }
            }
        }

        cout << (dp[N][M] ? "SI" : "NO") << "\n";
    }
}

# Introducción a la solución

El problema pide decidir si un número natural $N$ es **oblongo**, es decir,
si se puede escribir como $N = k \cdot (k+1)$ para algún natural $k \ge 1$.

A pesar del envoltorio sobre curvas elípticas, la pregunta es puramente
aritmética: dado $N$, ¿existe un entero $k$ tal que $k(k+1) = N$?

# La idea

Si $N = k(k+1)$, entonces $k$ y $k+1$ son dos enteros consecutivos cuyo
producto es $N$. La media geométrica de $k$ y $k+1$ es $\sqrt{k(k+1)} =
\sqrt{N}$, así que **necesariamente** uno de los dos está por debajo de
$\sqrt{N}$ y el otro por encima. Pero como $k$ y $k+1$ son **consecutivos**,
no pueden alejarse más de 1 unidad entre ellos, así que tampoco se pueden
alejar mucho de $\sqrt{N}$.

Más concretamente:

$$
k^2 \;<\; k(k+1) \;<\; (k+1)^2
$$

(siempre que $k \ge 1$). Tomando raíz:

$$
k \;<\; \sqrt{k(k+1)} \;<\; k+1.
$$

Es decir, $\sqrt{N}$ cae estrictamente entre $k$ y $k+1$, así que la
única posibilidad es

$$
k \;=\; \lfloor \sqrt{N} \rfloor.
$$

El algoritmo se reduce entonces a:

1. Calcular $r = \lfloor \sqrt{N} \rfloor$.
2. Comprobar si $r \cdot (r+1) = N$. Si sí, $N$ es oblongo; si no, no lo es.

Cada caso se resuelve en $O(1)$ aritméticas.

# ¿Y los errores de redondeo?

Cabe la duda razonable de si la raíz cuadrada en coma flotante de doble
precisión puede salir desplazada respecto al entero correcto cuando $N$ es
grande. Hay que tener cuidado al razonarlo: en general, si $\sqrt{N}$ real
fuera **exactamente un entero $k$**, **cualquier perturbación negativa**,
por pequeña que fuese, daría $k - \varepsilon$ y el truncamiento bajaría
a $k-1$. Es decir, cerca de un entero el "*umbral de fallo*" no es
$0{,}5$, es prácticamente nulo.

Sin embargo, **en este algoritmo ese problema no se presenta**, por dos
razones complementarias.

## (1) Para los oblongos, la raíz nunca cae cerca de un entero

Si $N = k(k+1)$, hemos visto que $k < \sqrt{N} < k+1$. Para acotar más
fino la posición de $\sqrt{N}$ dentro de ese intervalo necesitamos
estimar $\sqrt{k^2+k} - k$.

Primero, lo reescribimos multiplicando y dividiendo por el conjugado:

$$
\sqrt{k^2+k} - k
\;=\; \frac{(\sqrt{k^2+k} - k)(\sqrt{k^2+k} + k)}{\sqrt{k^2+k} + k}
\;=\; \frac{(k^2+k) - k^2}{\sqrt{k^2+k} + k}
\;=\; \frac{k}{\sqrt{k^2+k} + k}.
$$

Ahora tenemos una división, que es más fácil de acotar.

Usando el desarrollo de Taylor
$\sqrt{1+x} = 1 + \tfrac{x}{2} - \tfrac{x^2}{8} + O(x^3)$ con $x = \tfrac{1}{k}$,

$$
\sqrt{k^2+k} \;=\; k\sqrt{1 + \tfrac{1}{k}} \;=\; k\left(1 + \tfrac{1}{2k} - \tfrac{1}{8k^2} + O(1/k^3)\right)
\;=\; k + \tfrac{1}{2} - \tfrac{1}{8k} + O(1/k^2).
$$

Restando $k$:

$$
\sqrt{k^2 + k} - k \;\approx\; \frac{1}{2} - \frac{1}{8k}.
$$

Es decir, $\sqrt{N}$ está aproximadamente a distancia $\tfrac{1}{2} -
\tfrac{1}{8k}$ de $k$ por arriba, y a $\tfrac{1}{2} + \tfrac{1}{8k}$ de
$k+1$ por abajo. Para todo $k \ge 1$, $\sqrt{k(k+1)}$ vive **cerca de
$k + \tfrac{1}{2}$, sistemáticamente lejos de cualquier entero**. Para
que el truncamiento se equivoque y no devuelva $k$, el error tendría que
llegar al menos a $\tfrac{1}{2} - \tfrac{1}{8k}$, que para $k \ge 1$ es
$\ge \tfrac{3}{8}$.

Acotando ese error: para $N \le 10^{18}$,

- El espaciado entre `double` consecutivos cerca de $10^{18}$ es de a lo
  sumo $\dfrac{10^{18}}{2^{52}} \approx 222$, así que al convertir un
  `long long` a `double` el error absoluto cumple
  $|\Delta N| \le \tfrac{1}{2} \cdot 222 \approx 128$.
- El error introducido en $\sqrt{N}$ por una perturbación $\Delta N$
  es aproximadamente
  $$
  |\Delta \sqrt{N}| \;\approx\; \frac{|\Delta N|}{2\sqrt{N}} \;\lesssim\; \frac{128}{2 \cdot 10^9} \;\approx\; 6{,}4 \cdot 10^{-8}.
  $$
- Para los $N$ pequeños la cuenta es aún más holgada: el `double`
  representa exactamente todos los enteros hasta $2^{53}$.

Es decir, el error real es del orden de $10^{-7}$ o menos, frente al
$\tfrac{3}{8}$ que haría falta para estropear el truncamiento. Sobra muchísimo
margen.

## (2) Para los no-oblongos, da igual qué $r$ devuelva el truncamiento

El único caso en el que la observación inicial ("*cerca de un entero el
truncamiento es frágil*") tiene importancia es cuando $\sqrt{N}$ real es
exactamente un entero, es decir, cuando $N = m^2$ es un cuadrado
perfecto. Pero **ningún cuadrado perfecto es oblongo**: si $m^2 = k(k+1)$
fuera oblongo, $k(k+1)$ y $k^2$ serían cuadrados consecutivos, lo que es
imposible para $k \ge 1$. Así que en ese caso la respuesta correcta es
`NO` y, sea cual sea el $r$ que devuelva el truncamiento (ya sea $m-1$ o
$m$), la comprobación $r(r+1) = N$ falla y la respuesta es exactamente
esa.

De hecho la observación es más general: para cualquier no-oblongo (cuadrado
perfecto o no), la comprobación $r(r+1) = N$ siempre devuelve `NO`, sea cual
sea el $r$, porque por definición no existe ningún entero $k$ con $k(k+1) =
N$. Así que cuando el número no es oblongo, da igual el valor de $r$ que
calculemos.

## Resumen

Para que el algoritmo dé un resultado **incorrecto**:

- En oblongos: requeriría un error $\ge \tfrac{3}{8}$ para alterar el
  truncamiento, frente al $10^{-7}$ real. Imposible.
- En no-oblongos: imposible por construcción.

# Alternativa sin flotantes: búsqueda binaria

Si uno detectase la posibilidad de error de redondeo pero no pudiese demostrar
que no es un problema real para el rango del problema, hay una solución robusta
alternativa muy directa: **búsqueda binaria** de $k$ tal que $k(k+1) = N$.

La función $k \mapsto k(k+1)$ es estrictamente creciente para $k \ge 1$, y
con $N \le 10^{18}$ la cota superior holgada $k \le 2 \cdot 10^9$ basta y
sigue cabiendo en un entero de 64 bits sin desbordar al evaluar
$k(k+1)$. La búsqueda binaria estándar encuentra la solución (o concluye
que no existe) en $O(\log N)$ por consulta, sin ninguna operación en
coma flotante.

# Otra alternativa: búsqueda ternaria

Por curiosidad metodológica, hay una tercera vía que también resuelve el
problema: **búsqueda ternaria** sobre la función "*error*"

$$
g(k) \;=\; \lvert N - k(k+1) \rvert.
$$

Esta función es **unimodal en V** sobre $k \in [1, k_{\max}]$: como
$k(k+1)$ es estrictamente creciente, $g$ empieza alta y decreciente
mientras $k(k+1) < N$, alcanza su mínimo cuando $k(k+1)$ se acerca lo
máximo posible a $N$, y vuelve a crecer (estrictamente) cuando se pasa
de largo. La búsqueda ternaria estándar converge a ese mínimo en
$O(\log N)$ iteraciones, y el criterio "*$g_{\min} = 0 \iff N$ es
oblongo*" es exactamente lo que pide el problema.

Habría que preguntarse si puede haber empates (no un mínimo único sino dos).
Imponiendo $g(k_0) = g(k_0+1)$:

$$
N - k_0(k_0+1) \;=\; (k_0+1)(k_0+2) - N
\;\Longrightarrow\;
2N = 2(k_0+1)^2
\;\Longrightarrow\;
N = (k_0+1)^2.
$$

Es decir, **solo cuando $N$ es un cuadrado perfecto** la función presenta
una "*meseta*" de longitud 2 con el mismo valor mínimo. La búsqueda
ternaria estándar puede terminar en cualquiera de los dos puntos, pero
ambos dan el mismo valor (no nulo, salvo el caso imposible $k_0+1 = 0$),
así que la respuesta sigue siendo "*no oblongo*", como debe. En todos los
demás casos, el mínimo se alcanza en un único $k$.

Esta aproximación es más lenta que la búsqueda binaria, pero debería entrar
igualmente en tiempo.

# Soluciones

| Solución | Descripción | Verificado con el juez |
| :------: | :---------- | :--------------------: |
| [I.cpp](src/I.cpp) | Calcula $r = \lfloor\sqrt{N}\rfloor$ y comprueba directamente $r(r+1) = N$. | :x: |
| [I_binsearch.cpp](src/I_binsearch.cpp) | Búsqueda binaria sobre $k$ tal que $k(k+1) = N$. | :x: |
| [I_ternary.cpp](src/I_ternary.cpp) | Búsqueda ternaria sobre $g(k) = \lvert N - k(k+1) \rvert$. | :x: |

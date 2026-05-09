# Introducción a la solución

El problema describe una variante lineal y reducida del nonograma: una única
fila de $N$ celdas, una secuencia de $M$ pistas $(a_1, \ldots, a_M)$ que
indican los tamaños de los bloques negros en orden, y un estado parcial que
fija algunas celdas a blanca o a negra dejando otras como indeterminadas. Hay
que decidir si existe alguna asignación válida que respete las pistas y el
estado parcial.

A primera vista parece un problema de **vuelta atrás** sobre las posibles
posiciones donde podemos arrancar cada bloque. Para cada uno de los $M$
bloques hay del orden de $N$ posiciones de inicio candidatas, así que un
backtracking ingenuo explora del orden de $N^M$ ramas. Con $N \le 3000$ y
$M \le \lceil N/2 \rceil$, esto es totalmente intratable.

La observación clave es que, mientras vamos colocando bloques de izquierda a
derecha, en cada momento la única información que condiciona si la
configuración actual es completable se reduce a dos números: cuántas celdas
hemos consumido ya y cuántos bloques hemos colocado. Todo lo que pase desde ahí
en adelante depende exclusivamente de esos dos valores y del estado parcial
(que es fijo, no es parte del estado de la búsqueda), no de la posición exacta
en la que hayamos colocado los bloques ya fijados.

Es decir, muchas ramas distintas del backtracking convergen en el mismo
$(i, j)$: si una rama explora exhaustivamente ese punto y concluye que desde él
no hay solución, esa información sirve para podar todas las ramas futuras que
también lleguen ahí. Esto es **programación dinámica con memoización**.

# El estado del DP

Definimos:

$$
\text{dp}[i][j] = \text{"¿hay una extensión válida desde la posición $i$ habiendo}
$$
$$
\text{colocado ya los $j$ primeros bloques?"}
$$

Es decir, todavía quedan por cubrir las celdas $[i, N)$ y por colocar los
bloques $(j+1), \ldots, M$ en ese tramo, de manera consistente con el
estado parcial.

**Caso base:** $\text{dp}[N][M] = \text{true}$ (no quedan celdas por
procesar ni bloques por colocar; trivialmente válido).

**Respuesta del problema:** $\text{dp}[0][0]$ (no hemos procesado ninguna
celda ni colocado ningún bloque).

Cada estado $\text{true}$ significa que **sí existe alguna manera de
terminar**.

# Transiciones

Desde un estado $\text{dp}[i][j]$ con $i < N$ y $j < M$, podemos avanzar
de exactamente dos formas:

1. **Dejar la celda $i$ en blanco**. Solo es legal si la celda $i$ no
   está fijada a negra en el estado parcial. El estado actual en ese caso
   podrá extenderse si y solo si el estado $(i+1, j)$ puede extenderse:
   $$\text{dp}[i][j] \Leftarrow \text{dp}[i+1][j].$$

2. **Empezar aquí el bloque $(j+1)$-ésimo**. Solo es legal si:
   - Las $a_{j+1}$ celdas $[i, i + a_{j+1})$ pueden ser todas negras
     (ninguna está fijada a blanca); y
   - Si tras el bloque o bien se han acabado las celdas ($i + a_{j+1} == N$),
     o bien la celda que sigue puede ser una celda separadora con el siguiente
     bloque (es decir, no está fijada a negra).

   Tras la transición consumimos también el separador, por lo que pasamos
   a $(i + a_{j+1} + 1, j+1)$:
   $$\text{dp}[i][j] \Leftarrow \text{dp}[i + a_{j+1} + 1][j+1].$$

   Consumir el separador como parte de la transición evita tener que
   arrastrar en el estado la información extra "*la última celda procesada
   es blanca o forma parte de un bloque*".

   Como caso especial, si el bloque encaja justo al final ($i + a_{j+1} =
   N$) y se trata del último bloque pendiente ($j+1 = M$), la transición
   conduce directamente a $\text{dp}[N][M]$, que es $\text{true}$ por el
   caso base.

Cuando $j = M$ pero $i < N$, no quedan bloques pero sí celdas por
procesar; el estado es $\text{true}$ si y solo si todas esas celdas
restantes pueden ser blancas (ninguna está fijada a negra).

# Comprobaciones de rango en O(1)

Cada transición de tipo "*colocar bloque*" pregunta cosas del tipo
"*¿pueden las celdas $[l, r)$ ser todas negras?*". Una respuesta directa
costaría $O(r - l)$, que en el peor caso es $O(N)$, y haría el algoritmo
cuadrático en $N$ por bloque.

La forma estándar de responder en $O(1)$ es precomputar dos sumas
prefijas:

- $\text{no blancas}[i] =$ nº de celdas en $[0, i)$ que **no** están
  fijadas a `'0'` (es decir, las que pueden ser negras: tanto las `'1'`
  como las indeterminadas `'X'`).
- $\text{no negras}[i] =$ análogo, contando las que **no** están
  fijadas a `'1'`.

Con esto, "*todas las celdas en $[l, r)$ pueden ser negras*" equivale a
$\text{no blancas}[r] - \text{no blancas}[l] = r - l$, en $O(1)$.
Análogo para "*pueden ser todas blancas*".

# Complejidad

El número de estados es $O(N \cdot M)$ con $M \le \lceil N/2 \rceil$, y
cada estado se procesa en $O(1)$. El coste total por caso de prueba es
$O(N \cdot M)$ y, con la suma global $\sum N \le 3 \cdot 10^4$, queda
muy holgado dentro del límite.

# Dos formas de implementar la misma DP

La recurrencia descrita arriba se puede ejecutar en dos sentidos.

## Top-down (recursivo con memoización)

Para resolver $\text{dp}[i][j]$, se llama recursivamente a las dos transiciones
aplicables, cacheando el resultado para cada estado. La recursión solo expande
estados realmente alcanzables desde $(0, 0)$.

Como observación útil: en cuanto la recursión encuentra una transición
que devuelve $\text{true}$ propaga el resultado hacia arriba sin probar
la otra, así que un mismo estado nunca se reconsulta en la caché con
valor $\text{true}$. Memoizar solo los estados $\text{false}$ es
suficiente, aunque memoizar también los $\text{true}$ no estorba (el
coste es despreciable).

## Bottom-up (iterativo)

Se llena la tabla en orden $i$ decreciente y, dentro, $j$ decreciente,
de modo que cuando se procesa $(i, j)$ los estados $(i+1, j)$ y
$(i + a_{j+1} + 1, j+1)$ que pueden necesitarse ya están resueltos. Los
casos base se inicializan explícitamente: $\text{dp}[N][M]$ y la fila
$\text{dp}[i][M]$ (que vale "*el resto puede ser todo blanco*").

Su ventaja es que no requiere recursión y hace buen aprovechamiento de la caché.

# Reformulación alternativa: DP de prefijo

La misma recurrencia admite una lectura simétrica que también puede
resultar natural:

$$
\text{dp}[i][j] = \text{"¿es posible procesar las primeras $i$ celdas habiendo}
$$
$$
\text{colocado exactamente los $j$ primeros bloques, con la celda $i$ libre para}
$$
$$
\text{empezar lo que venga después?"}
$$

Es la misma DP leída en sentido inverso: ahora un estado $\text{true}$
indica "*alcanzabilidad del prefijo*" en lugar de "*extensibilidad del
sufijo*". El caso base es $\text{dp}[0][0] = \text{true}$ y la respuesta
es $\text{dp}[N][M]$. Las transiciones son las mismas pero se aplican
hacia adelante: cuando un estado es $\text{true}$, se marcan como
$\text{true}$ los estados a los que se llega.

Hay un matiz importante en esta formulación: $\text{dp}[i][j] =
\text{true}$ no implica que ese prefijo se pueda **completar** hasta una
solución total; solo que el prefijo es **alcanzable**. Habrá multitud de
estados marcados $\text{true}$ que en realidad sean callejones sin
salida porque ninguna transición desde ellos sobreviva a las
restricciones futuras. Esto no es un problema porque el DP solo nos
pregunta al final si $\text{dp}[N][M]$ es $\text{true}$, y los callejones
sin salida no contribuyen a marcarlo.

La implementación natural de esta variante es bottom-up con iteración $i$
creciente y, dentro, $j$ creciente.

# Soluciones

| Solución | Descripción | Verificado con el juez |
| :------: | :---------- | :--------------------: |
| [H.cpp](src/H.cpp) | DP sufijo top-down con memoización (recursivo). | :x: |
| [H_iter.cpp](src/H_iter.cpp) | DP sufijo bottom-up (iterativo). | :x: |
| [H_prefijo.cpp](src/H_prefijo.cpp) | DP prefijo bottom-up (iterativo). Reformulación alternativa. | :x: |

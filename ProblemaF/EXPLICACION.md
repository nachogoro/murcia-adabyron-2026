# Introducción a la solución

El problema pide, dado un presupuesto $D$ y dos catálogos de precios
(uno de CPUs y otro de GPUs), encontrar la combinación de **una CPU + una
GPU** cuyo precio total sea lo más alto posible sin superar $D$. Es
decir, queremos maximizar $n_i + m_j$ sujeto a $n_i + m_j \le D$, eligiendo
una pieza de cada catálogo.

# Enfoque ingenuo (demasiado lento)

La solución por fuerza bruta examina todas las parejas $(i, j)$ y comprueba
si la suma cabe en el presupuesto, quedándose con el máximo. Es $O(N \cdot
M)$ por caso de prueba. Con los límites del problema ($N, M$ hasta $10^5$
y suma global hasta $10^6$), un caso adverso podría hacer del orden de
$10^{10}$ operaciones, claramente fuera del límite de tiempo.

# Mejora: ordenar uno y búsqueda binaria sobre el otro

La observación clave es que, *fijada una CPU de precio $c$*, el problema
se reduce a "*encontrar la GPU más cara cuyo precio sea $\le D - c$*". Si
tenemos las GPUs ordenadas por precio, esa pregunta se contesta con una
*búsqueda binaria* en $O(\log M)$, buscando el mayor elemento $x$ que satisface
$x \leq D - c$.

Iterando sobre todas las CPUs y quedándonos con el mejor total, el
algoritmo queda en $O(N \log M + M \log M)$ por caso (el segundo término es
el coste de ordenar las GPUs). Con la suma global de $N$ y $M$ acotada
por $10^6$, el coste total cae cómodamente dentro del límite.

Por simetría, también se podría ordenar las CPUs y buscar binariamente
sobre ellas mientras se itera por las GPUs; el resultado y la complejidad
son similares.

# Soluciones

| Solución | Verificado con el juez |
| :------: | :--------------------: |
| [F.cpp](src/F.cpp) | :x: |

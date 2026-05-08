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

# Mejora: ordenar uno y búsqueda binaria por cada elemento del otro

La observación clave es que, *fijada una CPU de precio* $c$, el problema
se reduce a "*encontrar la GPU más cara cuyo precio sea* $\le D - c$". Si
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

# Alternativa: dos punteros

Hay otra solución que evita la búsqueda binaria y baja el coste por
elemento de $\log$ a constante amortizada. Si ordenamos *ambos*
catálogos (CPUs ascendente, GPUs ascendente) y colocamos un puntero $i$
al inicio de las CPUs (la más barata) y otro $j$ al final de las GPUs
(la más cara), podemos avanzar de forma monótona:

- Si $\mathrm{cpus}[i] + \mathrm{gpus}[j] > D$, la GPU $j$ es demasiado
  cara para cualquier CPU desde $i$ en adelante (las siguientes solo
  serán más caras), así que ya nunca volveremos a usarla: descartamos
  esa GPU bajando $j$.
- Si $\mathrm{cpus}[i] + \mathrm{gpus}[j] \le D$, esta pareja es
  factible. Y, *para esta CPU concreta*, $\mathrm{gpus}[j]$ es la GPU
  más cara que aún cabe (las que estaban por encima ya las descartamos
  en pasos previos), así que registramos la suma como candidato al
  máximo y pasamos a la siguiente CPU subiendo $i$.

Cada paso o avanza $i$ o retrocede $j$, así que el bucle hace a lo sumo
$N + M$ iteraciones. El coste dominante vuelve a ser ordenar, pero el
recorrido en sí es lineal: $O(N \log N + M \log M)$ en total.

Toda pareja $(c, g)$ que descartamos lo hacemos por una de dos razones:

- Subimos $i$ habiendo registrado $\mathrm{cpus}[i] + \mathrm{gpus}[j]$.
  Cualquier $(\mathrm{cpus}[i], \mathrm{gpus}[j'])$ con $j' < j$ tiene
  suma menor que la registrada, así que no podía mejorar el máximo.
  Cualquier $(\mathrm{cpus}[i], \mathrm{gpus}[j'])$ con $j' > j$ ya
  había sido descartada antes (al bajar $j$ pasando por $j'$).
- Bajamos $j$ porque $\mathrm{cpus}[i] + \mathrm{gpus}[j] > D$. Para
  cualquier $i' \ge i$, $\mathrm{cpus}[i'] + \mathrm{gpus}[j] \ge
  \mathrm{cpus}[i] + \mathrm{gpus}[j] > D$, así que la GPU $j$
  tampoco habría sido útil para ningún $i'$ posterior.

En ningún momento se descarta una pareja que pudiera batir al óptimo.

# Soluciones

| Solución | Descripción | Verificado con el juez |
| :------: | :---------- | :--------------------: |
| [F.cpp](src/F.cpp) | Ordena las GPUs y, para cada CPU, hace una búsqueda binaria de la GPU más cara que cabe en el presupuesto restante. | :x: |
| [F_dospunteros.cpp](src/F_dospunteros.cpp) | Ordena ambos catálogos y los recorre con dos punteros, uno desde la CPU más barata y otro desde la GPU más cara. | :x: |

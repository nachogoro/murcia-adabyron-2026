# Introducción a la solución

El problema pide, para cada caso de prueba, decidir si todas las personas de
un grupo pueden saltar un obstáculo situado a distancia $D$, y en caso
contrario, decir cuántas no lo consiguen. Una persona supera el obstáculo si
su distancia de salto es **estrictamente mayor** que $D$.

La solución directa es recorrer las $N$ distancias de salto del grupo
contando cuántas son menores o iguales que $D$ (es decir, cuántos *no*
saltan el obstáculo). Al terminar:

- Si el contador es 0, todos lo superan: imprimir `TODOS`.
- Si no, imprimir el contador seguido de `NO`.

No hace falta almacenar las distancias en una estructura: se procesan al
vuelo conforme se leen, lo que mantiene el coste en $O(N)$ por caso de
prueba y memoria $O(1)$.

# Notas sobre tipos numéricos

Las distancias de salto y la distancia al obstáculo pueden llegar a $10^9$,
así que caben sobradamente en un entero de 32 bits: no es necesario
recurrir a tipos de 64 bits para almacenarlas.

# Soluciones

| Solución | Verificado con el juez |
| :------: | :--------------------: |
| [A.cpp](src/A.cpp) | :x: |

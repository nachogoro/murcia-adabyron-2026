# Introducción a la solución

El problema describe un grafo dirigido acíclico de tareas: cada tarea tiene
una duración y un conjunto de prerrequisitos que deben completarse antes de
que ella pueda empezar. Se garantiza que la tarea $0$ es la única sin
prerrequisitos y que la tarea $n-1$ depende, directa o indirectamente, de
todas las demás. Hay que calcular la duración del camino más largo
(en suma de duraciones) que va de la tarea $0$ a la tarea $n-1$ siguiendo
las dependencias (la ruta crítica).

Se asume que podemos realizar las tareas inmediatamente en cuanto están
desbloqueadas (por estar sus requisitos completados), y que podemos realizar
tantas tareas a la vez como deseemos.

# La idea: programación dinámica sobre el orden topológico

Para cada tarea $v$ definimos $\text{ef}[v]$ como **la longitud del camino
crítico que termina al acabar $v$**. Es decir, el tiempo mínimo que debe
transcurrir desde el inicio del proyecto hasta que $v$ está completada en el
mejor caso de planificación (sin límite de tareas paralelas). La relación
de recurrencia es:

$$
\text{ef}[v] = d_v + \max_{u \in \text{prereqs}(v)} \text{ef}[u]
$$

donde $d_v$ es la duración de $v$. El caso base es $\text{ef}[0] = d_0$
(la tarea inicial no tiene prerrequisitos).

La respuesta del problema es $\text{ef}[n-1]$.

# Alternativa 1: bottom-up (orden topológico de Kahn + DP)

Para calcular $\text{ef}[v]$ necesitamos conocer $\text{ef}$ de todos los
prerrequisitos de $v$, así que tenemos que procesar las tareas en un orden
en el que cada tarea aparezca después de sus prerrequisitos. Eso es
exactamente un **ordenamiento topológico**.

La forma más limpia de procesar las tareas en orden topológico es el
algoritmo de Kahn:

1. Construir, para cada tarea $u$, la lista de **hijos** (tareas que tienen
   a $u$ como prerrequisito) y el número de prerrequisitos pendientes de
   cada tarea.
2. Iniciar una cola con la tarea $0$ (la única sin prerrequisitos por
   garantía del enunciado).
3. Mientras la cola no esté vacía, sacar una tarea $u$:
   - Sumar $d_u$ a $\text{ef}[u]$. En este momento $\text{ef}[u]$ ya
     contiene $\max_{p \in \text{prereqs}(u)} \text{ef}[p]$ (los
     predecesores ya lo han actualizado al pasar por sus aristas).
   - Para cada hijo $v$ de $u$:
     - Actualizar $\text{ef}[v] \leftarrow \max(\text{ef}[v], \text{ef}[u])$.
     - Decrementar el contador de prerrequisitos pendientes de $v$. Si
       llega a 0, encolar $v$.

Cada arista del grafo se procesa una vez (en el momento en que el
predecesor relaja al hijo), y cada tarea entra y sale de la cola
exactamente una vez. La complejidad es $O(n + E)$ por caso de prueba,
con $E$ el número total de aristas (acotado por $10^5$ en este
problema).

# Alternativa 2: Top-down (memoización)

La recurrencia anterior ($\text{ef}[v] = d_v + \max_{u} \text{ef}[u]$ sobre
los prerrequisitos de $v$) admite directamente una traducción recursiva
con memoización:

1. Para resolver $\text{ef}[v]$, llamar recursivamente a $\text{ef}$ sobre
   cada prerrequisito de $v$, quedarse con el máximo y sumarle $d_v$.
2. Cachear el resultado de cada $v$ para no recalcular.
3. La respuesta del problema es $\text{ef}[n-1]$, así que basta con una
   única llamada inicial; la recursión visita por primera vez cada tarea
   del subgrafo alcanzable hacia atrás desde $n-1$ (que por garantía del
   enunciado es todo el grafo).

Como solo se exploran las dependencias hacia atrás, esta versión usa
directamente la lista de **predecesores** (que es justo la que da el
enunciado, sin transformarla), y no necesita calcular hijos ni contadores
de prerrequisitos pendientes.

La complejidad es la misma que la versión iterativa, $O(n + E)$: cada tarea
se resuelve una vez (gracias a la memoización) y cada arista se recorre
también una vez (al iterar sobre los prerrequisitos de la tarea que la
contiene).

El único punto delicado es la **profundidad de recursión**: el camino más
largo en el DAG puede tener hasta $n$ tareas, así que la pila puede llegar
a $n$ marcos. Con $n \leq 10^4$ esto cabe sin problemas en una pila
estándar (~8 MB).

# Soluciones

| Solución | Descripción | Verificado con el juez |
| :------: | :---------- | :--------------------: |
| [E.cpp](src/E.cpp) | Versión iterativa (bottom-up) | :x: |
| [E_recursivo.cpp](src/E_recursivo.cpp) | Versión recursiva (top-down) | :x: |

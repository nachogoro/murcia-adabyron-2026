# Problema E - Proyecto Dolce

Tiempo de ejecución: 1 s

*Problema patrocinado por STEL Order.*

## Contexto

Como experto en Planificación Estratégica, te han pedido ayuda para
gestionar el proyecto *Dolce*: la producción a larga escala de pasteles en la
mayor fábrica de la región. Para estimar plazos realistas, la empresa modela
cada pastel mediante un diagrama con tareas que dependen unas de otras, de
forma que una tarea no puede empezar hasta que no terminan todas las tareas
de las que depende. Por ejemplo, antes de decorar una tarta de la abuela, hay
que preparar las galletas y las natillas.

En particular, a la empresa le conviene estimar la mínima cantidad de tiempo
entre que comienza la primera tarea hasta que termina la última en el mejor
caso de planificación posible, donde no hay un límite de tareas que se
puedan realizar paralelamente.

A esta secuencia de tareas que determina la duración más corta posible entre
el principio y el final de la tarta se la denomina ruta crítica.

## El problema

Se darán $n$ tareas, cada una con su duración estimada. La tarea inicial es
la 0, y la final es la $n-1$. Para cada tarea $i$, se listan sus
prerrequisitos: las tareas que deben terminar antes de que $i$ pueda
comenzar. Al ser fabricación masiva de pasteles, se asume que si una tarea
está preparada para comenzar, simplemente empieza.

La longitud de la ruta crítica se define como la máxima suma de duraciones
de las tareas a lo largo de cualquier sucesión de tareas dependientes cada
una de la anterior que empiece en la tarea 0 y termine en la tarea $n-1$
(incluyendo ambas tareas). Tu objetivo es calcular la longitud de la ruta
crítica para distintas tartas.

Se garantiza que la tarea 0 es la única tarea que no tiene dependencias, que
la tarea $n-1$ tiene de prerrequisitos todas las tareas, y que no hay
ciclos ni bucles en el diagrama.

## Entrada

La entrada consiste en múltiplos planificaciones de tartas. La primera línea
contiene un entero $T$ ($1 \leq T \leq 200$) con el número de tartas. Cada
proyecto de tarta está compuesto por múltiples líneas con el siguiente
formato:

- La primera línea contiene un entero $n$ ($2 \leq n \leq 10^4$) con el
  número de tareas.
- La segunda línea contiene $n$ enteros $d_i$ ($1 \leq d_i \leq 10^3$),
  donde el $i$-ésimo entero representa la duración de la tarea $i$.
- A continuación, hay $n$ líneas, cada una describiendo las dependencias de
  cada tarea $i$. Cada una de estas líneas comienza con un entero $m_i$ ($0
  \leq m_i \leq n-1$), seguido de $m_i$ enteros distintos entre $0$ y
  $n-1$ (excluyendo $i$), que representan las tareas de las que depende la
  tarea $i$.

Se garantiza que la suma de los $m_i$ no supera $10^5$.

## Salida

La salida consta de una línea para cada tarta, indicando la longitud de la
ruta crítica desde el paso $0$ hasta el $n-1$, incluyendo las duraciones
de la primera y última tarea.

## Ejemplo de Entrada 1
```
3
5
3 2 4 5 1
0
1 0
2 0 1
1 2
4 0 1 2 3
5
1 1 1 1 1
0
1 0
1 1
1 2
4 0 1 2 3
6
10 5 1 1 1 3
0
1 0
1 0
1 0
1 0
5 0 1 2 3 4
```

## Ejemplo de Salida 1
```
15
5
18
```

## Explicación de los ejemplos

La entrada consta de 2 casos de prueba. Para el primer caso, se muestra el
diagrama con la ruta crítica. Primero se resuelve la tarea 0, después la 1,
y secuencialmente 2, 3, y 4, por lo que la duración de la ruta crítica es:
$3 + 2 + 4 + 5 + 1 = 15$.

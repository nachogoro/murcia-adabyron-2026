# Problema A - Cruzando el Río

Tiempo de ejecución: 1 s

*Problema patrocinado por NTT Data.*

## Contexto

En una actividad de *coworking*, un grupo de empleados ha decidido pasar un
día de excursión por el río. Sin embargo, siempre hay rocas u obstáculos que
impiden el paso y la única manera de avanzar es saltándolos... pero es posible
que algunos no puedan llegar al otro lado. Todo el grupo quiere permanecer
unido, por lo que no irán por un camino que no puedan superar todos.

## El problema

Cada persona $i$ tiene una capacidad de salto $a_i$, que determina la
distancia a la que puede saltar. Diremos que podrá salvar un obstáculo a
distancia $d$ si puede saltar estrictamente más allá del mismo.

Dado un obstáculo, y un grupo de personas con sus capacidades de salto,
decidir si todo el grupo puede atravesarlo saltando o no. En caso de no poder
todos, decir el número de personas que no pueden.

## Entrada

La entrada consiste en múltiples casos de prueba. La primera línea contiene
un entero $T$ ($1 \leq T \leq 200$) con el número de casos de prueba. Cada
caso de prueba está compuesto por múltiples líneas con el siguiente formato:

- La primera línea contiene dos enteros $N$ ($1 \leq N \leq 10^4$) y $D$ ($1
  \leq D \leq 10^9$) con el número de personas en el grupo y la distancia al
  obstáculo, respectivamente.
- La segunda línea contiene $N$ enteros, donde el $i$-ésimo entero ($a_i$)
  representa la distancia de salto de la persona $i$ ($1 \leq a_i \leq
  10^9$).

## Salida

Para cada caso de prueba, imprimir una línea con "`TODOS`" en caso de que
todas las personas del grupo puedan saltar el obstáculo, o bien "`X NO`",
donde $X$ es el número de personas que no pueden saltar el obstáculo.

## Ejemplo de Entrada 1
```
2
2 50
120 150
4 10
25 31 12 10
```

## Ejemplo de Salida 1
```
TODOS
1 NO
```

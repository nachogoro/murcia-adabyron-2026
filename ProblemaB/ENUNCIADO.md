# Problema B - Asignación de Grupos

Tiempo de ejecución: 1 s

## Contexto

Como todos los años, hay que elegir grupos de prácticas y esta vez los
estudiantes tienen que hacer una lista con sus preferencias. Se utilizará un
método un tanto controvertido: asignar los grupos en función de las notas de
los alumnos...

## El problema

Cada grupo de prácticas tiene un cupo y unos horarios distintos. Cada
estudiante tiene una lista ordenada de preferencias de grupos a los que
querría ir. Los estudiantes eligen grupo en función de su nota $n_i$, y en
caso de empate, prioriza el orden de aparición de la nota en la entrada del
programa.

Tu tarea es calcular una asignación de grupos en la que cada estudiante $i$
no esté asignado a un grupo que preferiría más porque en ese grupo haya
plazas sin ocupar o porque otro estudiante con menor nota, o con la misma
nota pero que aparezca más tarde según el orden de aparición de la nota de
la entrada del programa, haya sido asignado a ese grupo.

Además, las listas de preferencias no son exhaustivas, pero deben indicar al
menos un grupo.

## Entrada

La entrada consiste en múltiples casos de prueba. La primera línea contiene
un entero $T$ ($1 \leq T \leq 200$) con el número de casos de prueba. Cada
caso de prueba está compuesto por múltiples líneas con el siguiente formato:

- La primera línea contiene dos enteros $n$ ($1 \leq n \leq 10^4$) y $m$ ($1
  \leq m \leq 10^3$), que corresponden al número de estudiantes y número de
  grupos. Los estudiantes se identifican del $0$ al $n-1$, y los grupos del
  $0$ al $m-1$.
- La segunda línea del caso tiene $n$ números reales con 2 decimales ($0.00
  \leq n_i \leq 10.00$), que corresponden a las notas de los $n$ alumnos. A
  mayor nota, mayor preferencia. Si hay 2 notas iguales, tendrá prioridad el
  orden de aparición de las notas.
- La tercera línea tiene $m$ enteros con los cupos de los grupos de
  prácticas, $1 \leq q_j \leq n$.
- Siguen $n$ líneas describiendo las listas de preferencias de los
  estudiantes:
  - Cada línea comienza un entero $k$, el número de grupos elegidos por el
    estudiante ($1 \leq k \leq m$), seguido de los $k$ grupos en orden de
    preferencia, primero los más preferidos.

Se garantiza que en cada caso de prueba, la suma de los elementos de todas
las listas de preferencias es menor que $10^6$.

## Salida

Para cada caso de prueba, imprimir $n$ líneas con una asignación válida que
respete las preferencias de los estudiantes y los cupos. Cada línea $i$ de la
salida (empezando por 0) debe contener 1 entero $j$, el grupo al que está
asignado el estudiante $i$.

Si un estudiante no está asignado a un grupo, $j$ debe ser $-1$.

En caso de haber varias asignaciones posibles, imprimir la primera en orden
lexicográfico teniendo en cuenta que si hay 2 estudiantes con la misma nota,
tiene preferencia el que tenga la primera de las notas según orden de
aparición de las mismas.

## Ejemplo de Entrada 1
```
1
3 2
3.30 2.20 1.11
1 2
2 1 0
1 0
2 0 1
```

## Ejemplo de Salida 1
```
1
0
1
```

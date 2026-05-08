# Problema H - Lineanograma

Tiempo de ejecución: 1 s

## Contexto

Un nonograma es un rompecabezas lógico que consiste en una cuadrícula que
debe ser rellenada en celdas negras o blancas de acuerdo con ciertas pistas
numéricas, de tal manera que se forme un patrón válido. En su versión
clásica bidimensional, cada fila y cada columna tiene una secuencia de
números que indica el tamaño de los bloques consecutivos de celdas negras
que deben aparecer en esa línea, separados siempre por al menos una celda
blanca. Resolver un nonograma consiste en deducir, a partir de estas
restricciones, qué celdas deben ser negras y cuáles blancas.

En este problema se considera una variante reducida y lineal del nonograma
tradicional, llamada *Líneanograma*. Aquí la cuadrícula se restringe a una
sola línea horizontal de longitud $n$. En lugar de pistas bidimensionales,
se dan únicamente las pistas de esa línea: una secuencia de enteros
positivos que indica los tamaños de cada bloque de celdas negras que deben
colocarse, separados por al menos un espacio blanco entre ellos. Además, se
proporciona un estado parcial de la línea, en el que algunas posiciones ya
están determinadas (como negras o blancas), mientras que otras permanecen
inciertas.

## El problema

Dada una línea de longitud $n$, un estado parcial de sus casillas (donde
cada casilla puede estar marcada como negra, blanca o indeterminada) y una
secuencia de pistas $(a_1, a_2, \ldots, a_M)$ que indican la longitud de
los bloques de celdas negras que deben aparecer en el orden dado, se pide
determinar si existe al menos una solución válida que complete el
lineanograma.

## Entrada

La entrada consiste en múltiples casos de prueba. La primera línea contiene
un entero $T$ ($1 \leq T \leq 1000$) con el número de casos de prueba.
Cada caso de prueba está compuesto por múltiples líneas con el siguiente
formato:

- La primera línea contiene dos enteros $N$ y $M$, ($1 \leq N \leq 3000$,
  $1 \leq M \leq \lceil \frac{N}{2} \rceil$) la longitud del lineanograma
  y el número de pistas:
- La segunda línea contiene $M$ enteros $(a_1, a_2, \ldots, a_M)$, el
  tamaño de cada bloque de celdas negras.
- La tercera línea contiene una cadena representando el estado parcial,
  dónde cada carácter indica que la celda en su posición es blanca, negra o
  indeterminada con un "`0`", "`1`" o "`X`", respectivamente.

Se garantiza que la suma de $N$ en todos los casos de prueba no supera $3
\cdot 10^4$.

## Salida

Para cada caso de prueba, escribe en una línea "`SI`" si existe, al menos,
una solución o "`NO`" si no existe ninguna.

## Ejemplo de Entrada 1
```
3
20 4
3 5 1 2
XXXXXX01XX110010X110
20 4
3 5 1 2
XX110XXXX11100XXXXXX
20 4
3 5 1 2
1X110XXXX11100XXXXXX
```

## Ejemplo de Salida 1
```
SI
SI
NO
```

## Explicación de los ejemplos

La imagen del problema se corresponde con el primer caso de prueba.

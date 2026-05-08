# Problema G - Control de Producción

Tiempo de ejecución: 1 s

*Problema patrocinado por Neuromobile.*

## Contexto

En un intento de digitalizar la agricultura, un grupo de inversores ha
apostado por el uso de drones para monitorizar los cultivos. Estos van
tomando fotografías aéreas del terreno y procesándolas para determinar qué
parcelas contienen cultivo y cuáles no. Sin embargo, el presupuesto es
limitado y los drones no pueden cubrir todo el terreno. ¿Podrías ayudarles a
estimar la cantidad de cultivo que hay en el terreno?

## El problema

Tenemos un terreno de $N$ parcelas de alto y $M$ parcelas de ancho. Cada
parcela es un cuadrado de $1 \times 1$ y la parcela en la posición superior
izquierda se indexa como $(1, 1)$. Un dron ha tomado $F$ fotografías
aéreas del terreno en posiciones $(x, y)$, siendo cada una de $3 \times 3$
parcelas. Algunas de las parcelas pueden aparecer en más de una fotografía.
En cada fotografía se ha procesado qué contiene cada parcela: tierra o
cultivo.

Dada la descripción del terreno y las $F$ fotografías, determinar cuál es
el número mínimo y máximo de parcelas que contienen cultivo en el terreno.

## Entrada

La entrada consiste en múltiples casos de prueba. La primera línea contiene
un entero $T$ ($1 \leq T \leq 100$) con el número de casos de prueba. Cada
caso de prueba está compuesto por múltiples líneas con el siguiente formato:

- La primera línea contiene tres enteros $N$, $M$ y $F$ ($3 \leq N, M
  \leq 10^6$, $1 \leq F \leq 10^5$) con las dimensiones del terreno y el
  número de fotografías respectivamente.
- A continuación, vienen $F$ bloques con la descripción de cada fotografía:
  - La primera línea de cada bloque contiene dos enteros $x$ e $y$ ($1
    \leq x \leq N-2$, $1 \leq y \leq M-2$) con la posición de la esquina
    superior izquierda de la fotografía.
  - Las siguientes tres líneas contienen cada una 3 caracteres, siendo
    cada carácter '`#`' si la parcela contiene cultivo y '`.`' si contiene
    tierra.

Se garantiza que la suma de $F$ en todos los casos de prueba no supera
$10^5$.

## Salida

Para cada caso de prueba, imprimir una línea con dos enteros separados por
un espacio: el número mínimo y máximo de parcelas que contienen cultivo en
el terreno.

## Ejemplo de Entrada 1
```
1
8 8 3
1 1
...
.#.
...
4 5
.##
..#
#..
6 3
#.#
#..
##.
```

## Ejemplo de Salida 1
```
9 47
```

## Explicación de los ejemplos

La imagen del problema se corresponde con el caso de ejemplo.

# Problema I - Encriptación... ¿Oblonga?

Tiempo de ejecución: 1 s

*Problema patrocinado por Qualcomm.*

## Contexto

Un grupo de investigadores en criptografía está explorando propiedades de
ciertas curvas elípticas. Concretamente, las de la forma:

$$y^2 = x^3 - N^2 \cdot x$$

Donde $N$ es un número oblongo. Un número natural es considerado oblongo si
se expresa como producto de dos naturales consecutivos.

Los investigadores están interesados en identificar rápidamente si un número
dado es oblongo o no. ¿Puedes ayudarles a desarrollar un programa que
determine si un número es oblongo?

## El problema

Dado un número natural $N$, determinar si es un número oblongo o no.

## Entrada

La entrada consiste en varios casos de prueba. Cada caso de prueba está
compuesto por un único número natural $N$ ($1 \leq N \leq 10^{18}$). La
entrada termina con un caso de prueba con $N = 0$, que no debe ser
procesado.

Se garantiza que el total de casos de prueba no excede $10^6$.

*OJO*: $N$ puede desbordar un entero, si es necesario, utiliza un tipo de
datos que permita almacenarlos. En C++, `long long`. En Java, `Long`. En
Python, no es necesario indicar el tipo.

## Salida

Para cada caso de prueba, se debe imprimir una línea con "`SI`" si $N$ es
un número oblongo, o "`NO`" en caso contrario.

## Ejemplo de Entrada 1
```
12
100
20880535878006
0
```

## Ejemplo de Salida 1
```
SI
NO
SI
```

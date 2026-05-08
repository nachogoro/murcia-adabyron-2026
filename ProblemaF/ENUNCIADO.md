# Problema F - Presupuestos Cuestionables

Tiempo de ejecución: 1 s

## Contexto

Tras una dura selectividad, Carlos ha conseguido entrar en Ingeniería
Informática. Sus padres, orgullosos, han decidido comprarle un buen
ordenador para hacer la carrera, diciéndole el presupuesto que tiene
disponible. Carlos no se ha visto nunca antes en una así y, como es un poco
pillo, quiere colar en el presupuesto junto a la CPU también una buena GPU,
convenciendo a sus padres de que realmente le hace falta (porque todos
sabemos que la última ENBIDIA 89700XTR es imprescindible para programar un
"Hola Mundo" en el bloc de notas). Asumiendo que el rendimiento de un equipo
completo es equivalente a su precio total de venta, ¿puedes ayudar a Carlos
a comprar el mejor PC que le permita su presupuesto?

## El problema

Dado el catálogo de precios de todas las CPUs y GPUs de una tienda,
determinar cuál es la combinación CPU + GPU más cara que puedes comprar con
un presupuesto $D$.

## Entrada

La entrada consiste en múltiples casos de prueba. La primera línea contiene
un entero $T$ ($1 \leq T \leq 100$) con el número de casos de prueba. Cada
caso de prueba está compuesto por múltiples líneas con el siguiente formato:

- La primera línea contiene un entero $D$ ($1 \leq D \leq 10^9$) con el
  presupuesto total disponible.
- La segunda línea contiene dos enteros $N$ y $M$ ($1 \leq N, M \leq
  10^5$) con el número de CPUs y GPUs disponibles respectivamente en el
  catálogo.
- La tercera línea contiene $N$ enteros, donde el $i$-ésimo entero ($n_i$)
  representa el precio de la CPU $i$ ($1 \leq n_i \leq 10^9$).
- La cuarta línea contiene $M$ enteros, donde el $j$-ésimo entero ($m_j$)
  representa el precio de la GPU $j$ ($1 \leq m_j \leq 10^9$).

Se garantiza que la suma de todos los $N$ y la suma de todos los $M$ en
todos los casos de prueba no excede $10^6$.

## Salida

Para cada caso, muestra el precio de la combinación CPU + GPU más cara que
se puede comprar con el presupuesto $D$. Si no es posible comprar ninguna
combinación, muestra $-1$.

## Ejemplo de Entrada 1
```
2
100
5 4
60 20 40 80 50
90 10 70 30
10
2 2
7 9
6 4
```

## Ejemplo de Salida 1
```
90
-1
```

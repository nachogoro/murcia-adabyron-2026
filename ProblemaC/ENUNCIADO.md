# Problema C - La Final de Boxa-Fighters

Tiempo de ejecución: 1 s

## Contexto

Horacio está siguiendo un torneo de su videojuego favorito, Boxa-Fighters. La
final, disputada entre los dos mejores jugadores del mundo, Alfredo y Borja,
tendrá lugar en EEUU, pero por cuestiones de horario en Murcia se celebrará
a altas horas de la madrugada. Dado que no podrá verlo en directo, ha hecho
una predicción del equipo que utilizará cada jugador en base a su historial.
Sabiendo los equipos que usarán, ¿puedes ayudar a Horacio a predecir el
resultado de la final?

## El problema

Boxa-Fighters es un juego de estrategia por turnos competitivo en el que cada
jugador controla un equipo de luchadores donde no interviene ningún elemento
aleatorio. Cada equipo está compuesto por uno o más luchadores. Cada luchador
tiene dos estadísticas: puntos de vida (HP) y puntos de daño (DP). Antes de
comenzar la partida, cada jugador debe de establecer el orden de los
luchadores de su equipo. Un jugador no puede modificar ni reordenar su equipo
durante una partida.

Al comienzo de la partida, cada jugador pondrá a su primer luchador en el
**puesto activo** y a su segundo luchador (si lo hay) en el **banquillo**,
respetando el orden original del equipo.

Durante la partida, los turnos de los jugadores se van alternando. En cada
turno, el jugador activo puede ejecutar una de las siguientes acciones:

- **Atacar**: el luchador en su puesto activo inflinge DP puntos de daño al
  luchador en el puesto activo del rival, reduciendo sus HP en dicha cantidad.
- **Intercambiar y atacar**: el luchador del puesto activo y del banquillo
  se intercambian de posición, y el luchador que pasa a estar ahora en el
  puesto activo realiza inmediatamente la acción de **Atacar**.

Cuando los HP de un luchador se reducen a 0 o menos, ese luchador queda
fuera de combate y pasa a ser automáticamente sustituido por el luchador en
el banquillo de su mismo jugador. Si quedan luchadores en el equipo,
automáticamente se preparará el próximo luchador disponible (en orden) y se
rellenará el hueco del banquillo. Ganará el primer jugador que consiga
vencer a todos los luchadores del equipo rival.

En la final, se sabe que Alfredo empezará jugando el primer turno. Dados los
equipos de ambos jugadores y considerando que ambos jugadores jugarán la
partida de forma óptima, determina si será Alfredo o Borja el próximo
campeón mundial de Boxa-Fighters.

## Entrada

La entrada consiste en múltiples casos de prueba. La primera línea contiene
un entero $T$ ($1 \leq T \leq 10$) con el número de casos de prueba. Cada
caso de prueba está compuesto por múltiples líneas con el siguiente formato:

- La primera línea contiene un entero $N$ ($1 \leq N \leq 10$) con el
  número de luchadores en el equipo de Alfredo.
- La segunda línea contiene $N$ pares de enteros, $a_i$ y $b_i$ ($1 \leq
  a_i, b_i \leq 10$) siendo $a_i$ los HP del $i$-ésimo luchador de Alfredo
  y $b_i$ los DP del $i$-ésimo luchador de Alfredo.
- La tercera línea contiene un entero $M$ ($1 \leq M \leq 10$) con el
  número de luchadores en el equipo de Borja.
- La cuarta línea contiene $M$ pares de enteros, $c_i$ y $d_i$ ($1 \leq
  c_i, d_i \leq 10$) siendo $c_i$ los HP del $i$-ésimo luchador de Borja y
  $d_i$ los DP del $i$-ésimo luchador de Borja.

## Salida

Para cada caso, muestra en una línea el nombre del ganador del combate
("`Alfredo`" o "`Borja`").

## Ejemplo de Entrada 1
```
2
1
1 2
2
1 1 1 1
2
1 1 2 2
2
2 1 1 2
```

## Ejemplo de Salida 1
```
Borja
Alfredo
```

## Explicación de los ejemplos

En el primer caso, Alfredo sólo puede atacar con su único luchador (1 HP, 2
DP), derrotando al primer luchador de Borja (1 HP, 1 DP). En el turno de
Borja, sólo puede atacar con su luchador restante (con también 1 HP y 1 DP),
derrotando al único luchador de Alfredo y ganando la partida.

En el segundo caso, si Alfredo intercambia su primer luchador (1 HP, 1 DP)
con el segundo (2 HP, 2 DP) y ataca, puede derrotar al primer luchador de
Borja (2 HP, 1 DP). En el siguiente turno, Borja ataca con su segundo
luchador (1 HP, 2 DP) derrotando al segundo luchador de Alfredo (que ahora
está primero). En el tercer turno, Alfredo gana la partida atacando con su
luchador restante (el que inicialmente era el primero).

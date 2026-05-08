# Introducción a la solución

El problema describe un juego por turnos con información perfecta (los
dos jugadores ven todo el estado en cada momento), sin azar (los ataques
y los intercambios son deterministas) y finito (cada turno reduce
estrictamente los puntos de vida del rival, así que no puede haber partidas
infinitas). Bajo esas condiciones el ganador con juego óptimo está
determinado por el estado inicial: existe una función que, para cada
configuración posible del combate, devuelve "*gana Alfredo*" o "*gana
Borja*".

La forma natural de calcular esa función es **vuelta atrás con
memoización**:

- Desde el estado inicial, se simula recursivamente cada decisión posible
  del jugador en turno.
- Si gana el jugador en turno tras *alguna* de sus decisiones, ese estado es
  ganador para él. Si gana el rival tras *todas*, es perdedor para el
  jugador en turno.
- Para evitar repetir el mismo subárbol de combate muchas veces, se guarda
  en una tabla el resultado de cada estado ya resuelto.

La idea clave que justifica la memoización es que dos combates distintos que
hayan llegado a la misma configuración terminarán exactamente igual con juego
óptimo: el desenlace depende solo del estado, no de cómo se haya llegado a
él. Por eso un mismo estado solo necesita resolverse una vez.

# Definición del estado del combate

Para que la equivalencia "*mismo estado $\Rightarrow$ mismo desenlace*" sea
cierta, el estado tiene que capturar toda la información que el juego
puede usar a partir de ahora. En este problema esa información se reduce a:

- **Quién tiene el turno**: Alfredo o Borja.
- **El equipo de Alfredo**, en orden, con los HP actuales. Es decir: quién
  está en el puesto activo, quién en el banquillo y quiénes esperan en
  reserva, junto con el HP que les queda. Los identificadores de cada
  luchador (sus DP y HP máximos) no son parte del estado: son inmutables y
  se leen aparte.
- **El equipo de Borja**, análogamente.

Notar que los luchadores que aún no han salido del banquillo nunca han
recibido daño, así que su HP es siempre el inicial. Pese a ello conviene
mantenerlos en el estado porque su orden de aparición sí es relevante para
los movimientos futuros.

Tampoco se necesita guardar quién ha sido derrotado: a los luchadores
derrotados se les retira del equipo en cuanto caen y desaparecen del
estado.

# Transiciones

Desde un estado en el que ambos equipos tienen al menos un luchador, el
jugador en turno tiene como mucho **dos** decisiones posibles:

1. **Atacar**: el activo del jugador en turno inflinge sus DP al activo
   rival. Si el activo rival cae a 0 HP o menos, se retira; el banquillo
   pasa a activo y, si todavía queda alguien en reserva, sale al banquillo.
   Tras el ataque, el turno cambia.
2. **Intercambiar y atacar**: si el jugador en turno tiene banquillo, puede
   permutarlo con el activo y, a continuación, ejecutar el ataque como en
   el caso anterior.

Si en alguno de los dos casos el rival se queda sin luchadores, el jugador
en turno gana inmediatamente.

# La recursión

Con el estado y las transiciones bien definidos, la recursión se escribe de
forma natural:

- **Casos base**: si el rival no tiene luchadores, gana el jugador en
  turno; si el jugador en turno no tiene luchadores, gana el rival.
- **Caso recursivo**: se generan los estados resultantes de las hasta dos
  decisiones del jugador en turno, se resuelve cada uno por recursión, y se
  combina:
  - Si Alfredo está en turno, basta con que *algún* sub-estado le sea
    favorable: tomar la mejor decisión es elegir cualquiera que le lleve a
    ganar.
  - Si Borja está en turno, se requiere que *todos* los sub-estados sean
    favorables a Alfredo: Borja elegirá racionalmente, así que con que
    tenga una sola decisión que le permita ganar, lo hará.

En implementación esto se traduce en un OR sobre las decisiones del jugador
en turno cuando le toca al "*nuestro*" jugador y un AND cuando le toca al
rival, con el correspondiente cortocircuito en cuanto el resultado quede
fijado.

# Memoización

Cada estado se resuelve **una sola vez** porque tras resolverlo se guarda en
una tabla indexada por el propio estado, y futuras consultas devuelven el
valor cacheado sin re-explorar.

El número total de estados está acotado: con como mucho 10 luchadores por
equipo, HP iniciales $\le 10$ y dos posibles turnos, la cantidad de
configuraciones distintas alcanzables es lo bastante pequeña como para que
la memoización quepa cómodamente en memoria y se procese en una pequeña
fracción del tiempo límite.

Una observación útil: como en cuanto encontramos una transición que devuelve
el resultado favorable al jugador en turno la búsqueda se corta hacia
arriba, los estados con resultado "*el jugador en turno gana*" no se vuelven
a consultar en la caché. **Basta con memorizar los estados perdedores**, lo
que simplifica la estructura (un conjunto de estados perdidos es suficiente,
no hace falta un mapa de estado a booleano). Los estados ganadores también
podrían memoizarse sin daño, pero no es necesario para la corrección ni
estrictamente para el rendimiento de este problema.

# Notas sobre la implementación en C++

Para indexar la tabla de memoización el estado debe poder compararse o
hashearse. Hay dos enfoques cómodos:

1. **Vector/struct como clave de un `std::map`**: si el estado se modela
   como una estructura cuyos miembros incluyen los dos equipos representados
   como secuencias de pares `(id, hp_actual)`, basta con definir un
   operador de comparación lexicográfico (por ejemplo con `std::tie` sobre
   los miembros) y usarla como clave de un `std::map<Estado, bool>`. Es la
   solución más directa.
2. **Codificación a entero o cadena, con `std::unordered_map`**: si la
   constante del map ordenado se queda corta, se puede empaquetar el
   estado en una clave plana —cada luchador cabe en un byte (4 bits para
   el id, 4 bits para el HP)— y usar una tabla hash. Para los límites de
   este problema cualquiera de las dos opciones funciona.

Otro detalle: el equipo conviene representarlo como una estructura que
permita poner y quitar luchadores por delante (el activo) en O(1), por
ejemplo un `std::deque`. La operación "*quitar al activo cuando cae*" se
convierte así en un simple `pop_front`, y el "*pasar el banquillo a activo*"
se hace solo, sin tener que reordenar nada.

# Soluciones

| Solución | Verificado con el juez |
| :------: | :--------------------: |
| [C.cpp](src/C.cpp) | :x: |

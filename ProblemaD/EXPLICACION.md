# Introducción a la solución

El problema describe dos rondas consecutivas de inversión sobre una cantidad
inicial $X$, y pide calcular el capital total al final.

La parte sustancial del problema no es la aritmética, sino la precisión.
El enunciado permite $X$ hasta $10^{1000}$, lo que descarta cualquier tipo
de coma flotante (ni `double` ni `long double` se acercan a esa precisión) y
también los enteros nativos (incluso `long long` o `int128` se quedan muy
cortos). Hay que trabajar con aritmética de precisión arbitraria.

## El truco: el resultado es exactamente $2X$

Hagamos las dos rondas de forma simbólica.

**Primer fondo:** rentabilidad del 80% con un 25% de los beneficios
descontados en impuestos. La cantidad tras el primer medio año es:

$$
X + X \cdot 0{,}8 \cdot (1 - 0{,}25) = X + X \cdot 0{,}6 = 1{,}6 \cdot X
$$

**Segundo fondo:** rentabilidad del 30% con $\tfrac{1}{6}$ de los beneficios
descontados en impuestos. Aplicado sobre el resultado anterior:

$$
1{,}6 X + 1{,}6 X \cdot 0{,}3 \cdot \left(1 - \tfrac{1}{6}\right)
= 1{,}6 X + 1{,}6 X \cdot 0{,}3 \cdot \tfrac{5}{6}
= 1{,}6 X + 0{,}4 X
= 2 X
$$

El resultado final es siempre exactamente $2X$, sin redondeos intermedios.

### Atajo: descubrirlo desde los ejemplos

Sin necesidad de hacer las cuentas simbólicas, basta con observar que todas las
operaciones del enunciado son multiplicativas: cada paso es "multiplica por un
porcentaje y suma o resta un porcentaje del resultado".  No aparece nunca un
término aditivo independiente de $X$, ni ningún término exponencial. Eso
garantiza que el resultado tiene la forma $k \cdot X$ para alguna constante $k$
que no depende de $X$.

Asumiendo eso, basta con mirar el primer ejemplo del enunciado para
deducir $k$: $287 \to 574$, así que $k = \frac{574}{287} = 2$. El segundo
ejemplo lo confirma: $5823372036854775803 \to 11646744073709551606 =
2 \cdot 5823372036854775803$.

# Dos enfoques

## Enfoque 1: aprovechar la simplificación

Una vez sabemos que el resultado es $2X$, basta con leer el número como cadena
(o como entero de precisión arbitraria, según el lenguaje) y duplicarlo. En
cualquier lenguaje con enteros grandes nativos (Python o Java con `BigInteger`)
es trivial. En C/C++, donde no los hay de serie, la duplicación dígito a dígito
sobre la representación decimal es muy sencilla:

- Recorrer la cadena de derecha a izquierda con un acarreo inicialmente a 0.
- En cada posición, calcular `2 · dígito + acarreo`. La unidad de ese
  resultado es el nuevo dígito; las decenas (0 o 1, ya que $2 \cdot 9 + 1 =
  19$) son el nuevo acarreo.
- Si tras la última posición el acarreo es 1, anteponerlo a la salida.

Coste $O(\text{nº de dígitos})$ por caso de prueba.

## Enfoque 2: implementar la fórmula con racionales exactos

Si no se hace la simplificación previa, hay que ejecutar las operaciones
indicadas en el enunciado *sin* perder precisión. Para no acarrear ni un
mínimo error, la aritmética debe hacerse con fracciones exactas:
representar cada cantidad como un par numerador/denominador y operar con
ellas hasta el final, donde se redondea al entero más cercano.

Esto es trivial en lenguajes con tipos de fracción nativos (Python tiene
`fractions.Fraction`); en C++ habría que implementar la fracción a mano y,
puesto que $X$ puede tener mil dígitos, el numerador y el denominador
también necesitan ser enteros de precisión arbitraria. Es bastante código
para resolver lo que en realidad termina siendo "*multiplicar por 2*", así
que normalmente este camino solo merece la pena en lenguajes que ya traen
el soporte hecho.

# Notas sobre los lenguajes

- **Python** tiene enteros de precisión arbitraria de serie y un módulo
  `fractions` con `Fraction(num, den)` que implementa los racionales
  exactos. Cualquiera de los dos enfoques es de pocas líneas.
- **Java** tiene `BigInteger` y `BigDecimal`, así que el enfoque 1 (con
  `BigInteger.shiftLeft(1)` o `multiply(BigInteger.TWO)`) y el enfoque 2
  (con `BigDecimal` o un wrapper de fracción sobre `BigInteger`) son
  igualmente cómodos.
- **C/C++** no traen aritmética de precisión arbitraria de serie. El
  enfoque 1 vía manipulación de cadena es muy sencillo (la duplicación se
  hace en una pasada con acarreo); el enfoque 2 requiere bastante código
  extra y normalmente no compensa.

# Soluciones

| Solución | Descripción | Verificado con el juez |
| :------: | :---------- | :--------------------: |
| [D.py](src/D.py) | Aplica la fórmula del enunciado paso a paso con `Fraction` para no perder precisión. | :x: |
| [D_simple.py](src/D_simple.py) | Aprovecha que el resultado es $2X$ y simplemente duplica el entero (Python soporta enteros grandes de serie). | :x: |
| [D_simple.cpp](src/D_simple.cpp) | Aprovecha que el resultado es $2X$, duplicando el número dígito a dígito sobre su representación decimal. | :x: |
| [D_simple.java](src/D_simple.java) | Aprovecha que el resultado es $2X$ usando `BigInteger.shiftLeft(1)` (equivalente a `multiply(BigInteger.TWO)`). | :x: |

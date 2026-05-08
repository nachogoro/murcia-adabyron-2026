# Introducción a la solución

El terreno es una cuadrícula de $N \times M$ parcelas y cada fotografía
revela información sobre $9$ parcelas de un cuadrado de $3 \times 3$:
qué parcelas son cultivo (`#`) y cuáles son tierra (`.`). Las fotografías
pueden solaparse, pero el resto del terreno queda **desconocido**. La
pregunta es por la cota mínima y máxima del número total de parcelas con
cultivo.

La cantidad real de parcelas con cultivo en el terreno está acotada por:

- **Mínimo**: lo único de lo que tenemos certeza es que las parcelas que
  aparecen marcadas como cultivo (`#`) en *al menos una* fotografía son,
  en efecto, cultivo. Esa cantidad es el mínimo: el resto podría ser
  tierra.
- **Máximo**: análogamente, las parcelas que aparecen marcadas como tierra
  (`.`) en *al menos una* fotografía son tierra y nunca podrán ser
  cultivo. Todas las demás (las marcadas como cultivo *o* las nunca
  fotografiadas) podrían serlo. Por tanto el máximo es

  $$N \cdot M - \lvert \text{parcelas conocidas como tierra} \rvert$$

Por hipótesis del enunciado las fotografías son consistentes (una misma
parcela no aparece marcada como cultivo en una y como tierra en otra), así
que cada parcela cubierta por al menos una foto cae en exactamente una de
las dos categorías.

# El algoritmo

Mantener dos conjuntos, uno con las parcelas conocidas como cultivo y otro
con las conocidas como tierra. Para cada fotografía, recorrer sus 9
parcelas y añadirlas al conjunto correspondiente. Al final:

- El **mínimo** es el tamaño del conjunto de "*cultivo*".
- El **máximo** es $N \cdot M$ menos el tamaño del conjunto de "*tierra*".

Como cada parcela puede aparecer en varias fotografías, los conjuntos se
encargan automáticamente de no contarla más de una vez.

El número total de inserciones es $9 F$ (con $F$ acotado por $10^5$ en la
suma global), así que el coste total con conjuntos basados en árbol
balanceado o tabla hash es manejable.

Para meter cada parcela en un conjunto hay que asociarle una **clave
única**. Las dos formas más naturales son:

1. **Pareja de coordenadas $(\text{fila}, \text{columna})$** como
   estructura compuesta: el conjunto la usa directamente. Es la opción más
   robusta porque no requiere razonar sobre rangos, y elimina cualquier
   posible colisión por construcción. Su único coste es alguna constante
   más por las comparaciones.
2. **Codificación a un único entero**, típicamente algo como
   $\text{fila} \cdot M + \text{columna}$. Los valores
   $\text{fila} \cdot M + \text{columna}$ son únicos para cada parcela y
   la codificación es unívoca.

# Soluciones

| Solución | Descripción | Verificado con el juez |
| :------: | :---------- | :--------------------: |
| [G.cpp](src/G.cpp) | Codifica cada parcela como un único entero $\text{fila} \cdot M + \text{columna}$. | :x: |
| [G_pair.cpp](src/G_pair.cpp) | Misma idea pero usando pares de coordenadas como clave del conjunto, sin codificación a entero. | :x: |

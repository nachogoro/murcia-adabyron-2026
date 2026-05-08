# Introducción a la solución

El problema pide asignar a un conjunto de estudiantes a grupos de prácticas
con cupo limitado. Cada estudiante aporta una lista ordenada de los grupos a
los que querría ir, y la asignación tiene que respetar la prioridad
establecida por las notas: ningún estudiante debe quedar asignado a un grupo
que prefiera menos que otro al que podría haber entrado (porque ese otro
tuviera plaza o porque hubiera alguien con menor prioridad ya colocado allí).
Los empates de nota se rompen por orden de aparición en la entrada.

Los alumnos que no tengan nota suficiente para entrar en ninguno de los grupos
que prefieren, deben quedarse sin asignar.

La condición de validez es que no exista *envidia justificada*: ningún
estudiante puede preferir un grupo en el que haya plaza libre o en el que haya
alguien con menor prioridad que él.

Cuando las prioridades son estrictas (no hay empates, como en este caso) y las
preferencias de cada alumno son una lista ordenada, este problema tiene una
solución clásica: el *serial dictatorship*. La idea es muy simple:

1. Ordenar a los alumnos por prioridad descendente (en este problema, por
   nota descendente y, en caso de empate, por orden de aparición).
2. Recorrerlos en ese orden y asignar a cada uno el primer grupo de su lista
   de preferencias que aún tenga cupo.
3. Si ninguno de los grupos de su lista tiene plaza cuando le toca, queda sin
   asignar (`-1`).

Cualquier desviación de este algoritmo introduciría envidia justificada:
saltarse un grupo más preferido teniendo plaza, o dejar a alguien con mayor
nota fuera de un grupo donde ha entrado alguien con menor nota.

# Sobre el criterio de desempate lexicográfico

El enunciado dice "*En caso de haber varias asignaciones posibles, imprimir
la primera en orden lexicográfico [...]*". Esta frase no aporta nada, puesto
que, al tener prioridades estrictas y preferencias estrictas, el resultado del
*serial dictatorship* es la *única* asignación válida.

# Sobre la comparación de notas (C++)

Las notas tienen 2 decimales y caben sin problemas en `double`. La comparación
de igualdad entre `double`s funciona aquí porque dos lecturas de la misma
cadena producen exactamente el mismo bit-pattern, por lo que los empates se
detectan sin error de redondeo. Si se quiere ser defensivamente correcto, se
puede leer la nota como cadena, eliminar el punto decimal y guardarla como
entero (multiplicada por 100).

# Soluciones

| Solución | Verificado con el juez |
| :------: | :--------------------: |
| [B.cpp](src/B.cpp) | :x: |

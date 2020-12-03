# Actividad 3.2 Árbol Heap: Implementando una fila priorizada

Análisis de complejidad

---- Push -----

Este método agrega un dato a la fila priorizada por lo que su complejidad es de

O(n) en el peor de los casos y O(log n)) en el average case

---- Pop -----

Este método saca de la fila priorizada el dato con mayor prioridad, tiene

una complejidad de O(log n) en el average case

---- Top -----

El método Top regresa el valor del dato que está con mayor prioridad, por lo que

su complejidad sería de O(1) en todos los casos

---- Empty ----

Regre un valor booleano diciendo si la fila está vacía o tiene datos, por lo que

su complejidad sería de O(1)

----- Size ----

Size regresa la cantidad de datos que tiene la fila, al ser solo ún número

que se acumula la complejidad es lineal O(1) en todos los casos

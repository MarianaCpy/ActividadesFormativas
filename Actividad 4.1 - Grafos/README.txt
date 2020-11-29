Actividad 4.1 Grafos
#Análsis de complejidad

El programa cuenta con 4 funciones las cuales son:

------ loadGraphMat -------

Esta función carga los datos de un grafo desde un archivo y los almacena en una matriz de adjacencia

por lo que su análisis de complejidad sería de O(|v|^2) en el average case, esto tomando en cuenta

que se cargan los datos

------ loadGraphList -------

Esta función carga los datos de un grafo desde un archivo y los almacena en una matriz de adjacencia

por lo que su análisis de complejidad sería de O(|v|+E) en el average case, esto tomando en cuenta que se cargan los datos

------ DFS -------

Por medio de dos entradas imprime el Recorrido de DFS, por lo que su análisis de complejidad sería de

O(V+E), en donde V es el número de vértices

------ BFS -------

Hace algo similar a la función anterior pero ahora con la anchura, por lo que su análisis de complejidad

sería de O(V+E)
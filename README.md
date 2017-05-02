# Algorithm-Exercises



##4

###The Mincut Problem

In this [Minumum cut](https://en.wikipedia.org/wiki/Minimum_cut) problem, the undirected graph is given as a file with every element represents a vertice in the graph. In each line, all the element except the first one represent the vertices connected with the vertice of the first element.

The task is to compute the minimum cut.

###My Implementation

Based on [Karger's algorithm](https://en.wikipedia.org/wiki/Karger%27s_algorithm), my implementation of the randomized contraction algorithm is

* While there are more than 2 vertices:
	* pick a remaining edge (v1,v2) uniformly at random, this includes: 
		* delete the edge (v1,v2)
		* delete the edge (v2,v1). Acutally (v2,v1) represent the same edge in the graph. However, one edge is represented twice in the file.
		* remove self-loops
		* modify other edges in the vertices. (All v2 should be changed into v1)
	* merge (or “contract” ) v2 into v1
* return cut represented by final 2 vertices.

###Run My Code

run

	gcc -g mincut.c
	./runMincut.sh
	
to compute the mincut. The number of vertices and the file name might need to be modified based on the given file. It will run 500 times with different random seeds and output the smallest cut among those 500 results.

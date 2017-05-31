
## Karatsuba Multiplication

Related files: karatsubaStringMultiplication.c

The [Karatsuba Algorithm](https://en.wikipedia.org/wiki/Karatsuba_algorithm) can get the multiplication of two numbers faster than classic multiplication method.

### My Implementation
Instead of receiving two integers, the input numbers are represented as strings so that we can get the multiplication of two very large numbers. Therefore, the method of adding and subtracting should also be modified in order to be applied on the strings. In my implication, the substracting method is not a general method, which means that the calling function of `stringSubtract()` have to make sure that the first number should be greater than the second number if they have the same digits. The basic multiplication method (the classical method) is used in function `stringProd()` but I just used the classical method to get the mutliplication of two 1-digit numbers.

To get the multiplication of two large numbers ab\*cd (e.g., 12345*6789):

|  a  |  b  |
| --- |:---:|
|  c  |  d  |

e.g.,

|  123  |  45  |
| ----- |:----:|
|   67  |  89  |

the length of the number which has longer length is nl, and the length of the number which has shorter length is ns. (if both have the same length, then nl=ns)

The multiplication can be calculated as

**[10^(ns/2)\*10^(ns/2)\*a\*c]+[10^(ns/2)\*(a+b)\*(c+d)-a\*c-b\*d]+[b\*d]**





## Count inversions

Related files: inversion.c, Array.txt

Count the number of inversions in the file Array.txt, where the ith of the row indicates the ithe entry of the array.

### My Implementation (based on slides of the course Divide and Conquer, Sorting and Searching, and Randomized Algorithms in Coursera )

* Divide the entire array into two parts and count the inversions of the left and right parts.

* Also count the inversions of the subarray whose first entry lies in the left part of the original array and last entry lies in the right part of the original array.

* The total number of inversions of the original array equals the sum of the three results acquired in the method described above.


## Get number of comparisions in QuickSort Algorithm

Related files: QuickSort.c, QuickSort.txt

Week 3 Assignment for course Divide and Conquer, Sorting and Searching, and Randomized Algorithms in Coursera: "Compute the total number of comparisons used to sort the given input file by QuickSort. When there is a recursive call on a subarray of length m, simply add m−1 to the running total of comparisons. (This is because the pivot element is compared to each of the other m−1 elements in the subarray in this recursive call.) "

### My Implecation

Based on slides for that course:

* The Partition subroutine.
	* Choose the pivot (in 3 different methods: left most, the median, right most) and swap it with the first entry of the array.
	* Put the pivot into the right place.

* Compute the total number of conparisions
	* if n==1, return	 
	* Partition the original array around the pivot
	* Recursively sort the left part
	* Recursively sort the right part 



## The Mincut Problem

Related files: mincut.c, runMincut.sh, kargerMinCut.txt

In this [Minumum cut](https://en.wikipedia.org/wiki/Minimum_cut) problem, the undirected graph is given as a file with every element represents a vertice in the graph. In each line, all the element except the first one represent the vertices connected with the vertice of the first element.

The task is to compute the minimum cut.

### My Implementation

Based on [Karger's algorithm](https://en.wikipedia.org/wiki/Karger%27s_algorithm), my implementation of the randomized contraction algorithm is

* While there are more than 2 vertices:
	* pick a remaining edge (v1,v2) uniformly at random, this includes: 
		* delete the edge (v1,v2)
		* delete the edge (v2,v1). Acutally (v2,v1) represent the same edge in the graph. However, one edge is represented twice in the file.
		* remove self-loops
		* modify other edges in the vertices. (All v2 should be changed into v1)
	* merge (or “contract” ) v2 into v1
* return cut represented by final 2 vertices.

### Run My Code

run

	gcc -g mincut.c
	./runMincut.sh
	
to compute the mincut. The number of vertices and the file name might need to be modified based on the given file. It will run 500 times with different random seeds and output the smallest cut among those 500 results.

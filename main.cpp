#include graph.h

int main(){
	Graph g(5, 10);
	g.printGraph();
	int** matrix = g.getMatrix();
	printMatrix(matrix, g.n);
	int* array = g.getBinaryArray();
	printArray(array, (int)g.n*(g.n-1)/2);
	int* compacted = g.getCompactedArray();
	printArray(compacted, g.compSize);
	int** genMatrix = g.genMatrix(compacted);
	printMatrix(genMatrix, g.n);
	return 0;
}

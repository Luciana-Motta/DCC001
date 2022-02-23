#include <iostream>
#include <cmath>

using namespace std;

struct node {
	int value; // nó que representa
	float weight; // peso da aresta
	node* next; // pŕoximo nó na lista de adjacência
};

class Graph {
	bool checkNode(int start, int end){
		node* local = nodesList[start];
		while(local != nullptr){
			if(local->value == end) return true;
			local = local->next;
		}
		return false;
	}
public:
	node** nodesList;
	int n;
	int compSize;
	Graph(int n, int m){
		this->n = n;
		nodesList = new node*[n]();
		for(int i = 0; i < n; i++){
			nodesList[i] = nullptr;
		}
		srand(time(NULL));
		for(int i = 0; i < ((int)m/2); i++){
			int startVertex = rand() % n;
			int endVertex = rand() % n;
			float weight = (rand() % 100000)/100000.0;

			if(startVertex == endVertex || checkNode(startVertex, endVertex)){
				i--;
				continue;
			}

			node* newNode = new node;
			newNode->weight = weight;
			newNode->value = endVertex;
			newNode->next = nodesList[startVertex];
			nodesList[startVertex] = newNode;

			newNode = new node;
			newNode->weight = weight;
			newNode->value = startVertex;
			newNode->next = nodesList[endVertex];
			nodesList[endVertex] = newNode;
		}
	}
	~Graph(){
		for(int i = 0; i < this->n; i++){
			delete[] nodesList[i];
		}
		delete[] nodesList;
	}
	void printGraph(){
		for(int i = 0; i < n; i++){
			cout << i << " |";
			node* local = nodesList[i];
			while(local != nullptr){
				cout << " -> " << local->value;
				local = local->next;
			}
			cout << " -> #" << endl;
		}
	}
	int** getMatrix(){
		int** matrix = new int*[n];
		for(int i = 0; i < n; i++){
			matrix[i] = new int[n];
		}
		for(int i = 0; i < n; i++){
			node* local = nodesList[i];
			while(local != nullptr){
				matrix[i][local->value] = 1;
				local = local->next;
			}
		}
		return matrix;
	}
	int* getBinaryArray(){
		int* binArray = new int[((int)n*(n-1)/2)];
		int** matrix = getMatrix();
		int pos = 0;
		for(int i = 0; i < n; i++){
			for(int j = i+1; j < n; j++){
				binArray[pos] = matrix[i][j];
				pos++;
			}
		}
		return binArray;
	}
	int* getCompactedArray(){
		int* binArray = getBinaryArray();
		int count = 0;
		for(int i = 0; i < ((int)n*(n-1)/2); i++){
			count += binArray[i];
		}
		this->compSize = count;
		int* compacted = new int[count];
		int pos = 0;
		for(int i = 0; i < ((int)n*(n-1)/2); i++){
			if(binArray[i]){
				compacted[pos] = i;
				pos++;
			}
		}
		return compacted;
	}
	int** genMatrix(int* compacted){
		int** matrix = new int*[n];
		for(int i = 0; i < n; i++){
			matrix[i] = new int[n];
		}
		int index = 0;
		int pos = 0;
		for(int i = 0; i < n; i++){
			for(int j = i+1; j < n; j++){
				if(index == compacted[pos]){
					matrix[i][j] = 1;
					matrix[j][i] = 1;
					pos++;
				}
				index++;
			}
		}
		return matrix;
	}
	int getCompactedIndexFromMatrix_A(int i, int j){
		int** matrix = getMatrix();
		int* array = getCompactedArray();

		int iStart = (int)(n*i - i*(i+1)/2);
		int indexArray = (int)(iStart+j-(i+1));
		for(int k = 0; k < compSize; k++){
			if(array[k] == indexArray){
				return array[k];
			}
		}
		return -1;
	}
	int getCompactedIndexFromMatrix_I(int i, int j){
		int** matrix = getMatrix();
		int* array = getCompactedArray();

		int index = -1;
		for(int k = 0; k < n; k++){
			for(int l = k+1; l < n; l++){
				index += matrix[k][l];
				if(k == i && l == j) return array[index];
			}
		}
		return index;
	}
	int getMatrixIndexFromCompacted_A(int indexCompacted){
		int** matrix = getMatrix();
		int* array = getCompactedArray();

		int index = array[indexCompacted];
		int Ic = (int)(n*(n-1)/2 - index);
		int Ie = (int)ceil((1+sqrt(8*Ic+1))/2.0);
		int i = (int)(n - Ie);
		int j = (int)(-n*i + i*(i+1)/2 + (i+1) + index);
		cout << "(" << i << "," << j << ")#";
		return matrix[i][j];
	}

	int getMatrixIndexFromCompacted_I(int indexCompacted){
		int** matrix = getMatrix();
		int* array = getCompactedArray();

		int index = array[indexCompacted];
		int count = 0;
		for(int i = 0; i < n; i++){
			for(int j = i+1; j < n; j++){
				if(count == index){
					cout << index << "#";
					return matrix[i][j];
				}
				count += 1;
			}
		}
		return -1;
	}
};

void printMatrix(int** matrix, int n){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void printArray(int* array, int n){
	cout << "[";
	for(int i = 0; i < n; i++){
		cout << array[i] << " ";
	}
	cout << "]" << endl;
}

int main(){
	Graph g(5, 10);
	cout << "Grafo: " << endl;
	g.printGraph();        
	cout << endl;
	int** matrix = g.getMatrix();
	cout << "Matriz" << endl;
	printMatrix(matrix, g.n);
	cout << endl;
	int* array = g.getBinaryArray();
	cout << "Vetor binario "<<endl;
	printArray(array, (int)g.n*(g.n-1)/2);
	cout << endl;
	int* compacted = g.getCompactedArray();
        cout << "Vetor compactado" << endl;
	printArray(compacted, g.compSize);
	cout << endl;
	int** genMatrix = g.genMatrix(compacted);
	cout << "Matriz" << endl;
	printMatrix(genMatrix, g.n);
	cout << endl;
	cout << "Teste 6 Analítica ###" << endl;
	for(int i = 0; i < g.n; i++){
		for(int j = i+1; j < g.n; j++){
			if(matrix[i][j]){
				cout << g.getCompactedIndexFromMatrix_A(i, j) << endl;
			}
		}
	}
	cout << endl;
	cout << "Teste 6 Iterativa ###" << endl;
	for(int i = 0; i < g.n; i++){
		for(int j = i+1; j < g.n; j++){
			if(matrix[i][j]){
				cout << g.getCompactedIndexFromMatrix_I(i, j) << endl;
			}
		}
	}
	cout << endl;
	cout << "Teste 7 Analítica ###" << endl;
	for(int i = 0; i < g.compSize; i++){
		cout << g.getMatrixIndexFromCompacted_A(i) << endl;
	}
	cout << endl;
	cout << "Teste 7 Iterativa ###" << endl;
	for(int i = 0; i < g.compSize; i++){
		cout << g.getMatrixIndexFromCompacted_I(i) << endl;
	}
	cout << endl;
	return 0;
}

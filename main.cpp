#include <iostream>

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

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
		while(local != nullptr){ // sempre que cria um grafo passa por esse while
			if(local->value == end) return true;
			local = local->next;
		}
		return false;
	}
public:
	node** nodesList;
	int n;
	int compSize;
  //construtor O(n + m/2 + 18) = O(2n)
	Graph(int n, int m){ 
		this->n = n;
		nodesList = new node*[n]();
		for(int i = 0; i < n; i++){ //O(n)
			nodesList[i] = nullptr;
		}
		srand(time(NULL)); 
		for(int i = 0; i < ((int)m/2); i++){ //O(m/2)
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
  //destrutor O(n + 1) = O(n)
	~Graph(){
		for(int i = 0; i < this->n; i++){ //O(n)
			delete[] nodesList[i];
		}
		delete[] nodesList;
	}
  
  //função imprime grafo O(3n*2m+1) = O(n^2)
	void printGraph(){
		for(int i = 0; i < n; i++){ //O(4n*2m)
			cout << i << " |";
			node* local = nodesList[i];
			while(local != nullptr){ //O(2m)
				cout << " -> " << local->value;
				local = local->next;
			}
			cout << " -> #" << endl;
		}
	}
  //função que retorna a matriz O(2n + n*2m + 2) = O(n^2)
	int** getMatrix(){ 
		int** matrix = new int*[n];
		for(int i = 0; i < n; i++){ //O(n)
			matrix[i] = new int[n];
		}
		for(int i = 0; i < n; i++){ //O(2n*2m)
			node* local = nodesList[i];
			while(local != nullptr){ //O(2m)
				matrix[i][local->value] = 1;
				local = local->next;
			}
		}
		return matrix;
	}
  
  //função que retorna array binario O(2n^2 + 4) = O(n^2)
	int* getBinaryArray(){
		int* binArray = new int[((int)n*(n-1)/2)];
		int** matrix = getMatrix(); 
		int pos = 0;
		for(int i = 0; i < n; i++){ //O(n*2n)
			for(int j = i+1; j < n; j++){ //O(2n)
				binArray[pos] = matrix[i][j];
				pos++;
			}
		}
		return binArray;
	}
  //função que retorna array compactado O(4n^2 - 2n + 8) = O(n^2)
	int* getCompactedArray(){
		int* binArray = getBinaryArray(); //O(2n^2 + 4)
		int count = 0;
		for(int i = 0; i < ((int)n*(n-1)/2); i++){ //O((n^2 - n)/2)
			count += binArray[i];
		}
		this->compSize = count;
		int* compacted = new int[count];
		int pos = 0;
		for(int i = 0; i < ((int)n*(n-1)/2); i++){  //O(3(n^2 - n)/2)
			if(binArray[i]){
				compacted[pos] = i;
				pos++;
			}
		}
		return compacted;
	}
  
  //função que retorna a matriz O(2n*4n + n + 6) = O(n^2)
	int** genMatrix(int* compacted){
		int** matrix = new int*[n];
		for(int i = 0; i < n; i++){ //O(n)
			matrix[i] = new int[n];
		}
		int index = 0;
		int pos = 0;
		for(int i = 0; i < n; i++){ //O(2n*4n)
			for(int j = i+1; j < n; j++){ //O(4n)
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

//função que printa a matriz O(2n*n) = O(n^2)
void printMatrix(int** matrix, int n){
	for(int i = 0; i < n; i++){ //O(2n*n)
		for(int j = 0; j < n; j++){ //O(n)
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

//função que printa array O(n + 3) = O(n)
void printArray(int* array, int n){
	cout << "[";
	for(int i = 0; i < n; i++){ //O(n)
		cout << array[i] << " ";
	}
	cout << "]" << endl;
}

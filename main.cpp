// Program Information /////////////////////////////////////////////////////////
/**
  * @file main.cpp
  *
  * @brief main driver     
  * 
  * @details calls implementation
  *
  * @version 1.00 Carli DeCapito
  *			 Original Documentation (11/13/17)
  *
  * @note None
  */

#include <iostream>
#include <cstdlib>

using namespace std;


struct Node{
  int currentEnergy;
  int dest;
  struct Node* next;
};

struct AdjList
{
  struct Node *head;
};

class Graph{
  private: 
    int V;
    struct AdjList *arr;

public: 
	Graph( int V )
    	{
      		this->V = V;
      		arr = new AdjList[ V ];
      		for ( int index = 0; index < V; index++ )
	      	{
			arr[ index ].head = NULL;
	      	}
    	}

  	Node * newNode( int currentEnergy, int dest )
    	{
    		Node *newNode = new Node;
    		newNode->currentEnergy = currentEnergy;
    		newNode->dest = dest;
    		newNode->next = NULL;
	
    		return newNode;
    	}

	void addEdge( int src, int currentEnergy, int dest )
	{
		if( )
   		Node *tempNode = newNode( currentEnergy, dest );
   		tempNode->next = arr[ src ].head;
   		arr[ src ].head = tempNode;

		tempNode = newNode( currentEnergy, src );
		tempNode->next = arr[ dest ].head;
		arr[ dest ].head = tempNode;
   	}

	void printGraph()
   	{
   		int index;
   		for ( index = 0; index < V; index++ )
   		{
   			Node *temp = arr[ index ].head;

   			cout << "\n Adjacency list of vertex " << index <<" \n head ";
			cout << "(" << temp->currentEnergy << ")";  			
			while( temp )
   			{
   				cout << "-> " << temp->dest;
   				temp = temp->next;
   			}
   			cout << endl;
   		}
   	}



};

void createGraph( Graph & network, int size );
bool numExists( int arr[], int index, int temp );

int main()
{
	int size; 
	cout << "Enter the number of nodes in the network: ";
	cin >> size;
	cout << endl;

	Graph network( size );

	createGraph( network, size );

	network.printGraph();

	return 0;
}

void createGraph( Graph & network, int size )
{
	int energy[ size ];
	int pointers[ size ];
	int temp;	
	bool exists = false;

	for ( int index = 0; index < size; index ++ )
	{
		//determines energy for each node
		energy[ index ] = rand() % size + 1;
 		//determines node which curr node points to 
		temp = pointers[ index ] = rand() % size;

		while( index == pointers[ index ] )
		{
			temp = pointers[ index ] = rand() % size;
		}

		exists = numExists( pointers, index, temp );
		while( exists )
		{
			temp = pointers[ index ] = rand() % size;

			while( index == pointers[ index ] )
			{
				temp = pointers[ index ] = rand() % size;
			}
			exists = numExists( pointers, index, temp );
		}

		//add edge
		network.addEdge( index, energy[ index ], pointers[ index ] );	
	}

	for ( int index = 0; index < size; index++ )
	{
		cout << "ENERGY " << energy[ index ] << endl;
		cout << "POINT " << pointers[ index ] << endl;
	}
}

bool numExists( int arr[], int index, int temp )
{
	for ( int j = 0; j < index; j++ )
	{
		if( temp == arr[ j ] )
		{
			return true;
		}
	}
	return false;
}





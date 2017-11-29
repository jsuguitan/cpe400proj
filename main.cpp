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
#include <fstream>
#include <cstdlib>
#include <ctime>

#define MAX_NUM 10000

using namespace std;

//////////////////////////
//// Graph Definition ////
//////////////////////////

struct Node{
  float currentEnergy;
  float energyUsed;
  int dest;
  struct Node* next;
};

struct AdjList
{
  struct Node *head;
};

///// Additional Struct
struct PacketInfo{
	int nodeNum;
	int numberOfPackets;
};
///////////////////////////
class Graph{ 
    
public: 
    int V;
    struct AdjList *arr;
	Graph( int V )
    	{
      		this->V = V;
      		arr = new AdjList[ V ];
      		for ( int index = 0; index < V; index++ )
	      	{
				arr[ index ].head = NULL;
	      	}
    	}

  	Node * newNode( int dest )
    	{
    		Node *newNode = new Node;
    		newNode->dest = dest;
    		newNode->next = NULL;
	
    		return newNode;
    	}

	void addEdge( int src, float currentEnergy1, float energyUsed1, float currentEnergy2, float energyUsed2, int dest )
	{
		//hello packets
   		Node *tempNode = newNode( dest );
   		tempNode->currentEnergy = currentEnergy1;
   		tempNode->energyUsed = energyUsed1;
   		tempNode->next = arr[ src ].head;
   		arr[ src ].head = tempNode;

   		//hello packets
		tempNode = newNode( src );
		tempNode->currentEnergy = currentEnergy2;
   		tempNode->energyUsed = energyUsed2;
		tempNode->next = arr[ dest ].head;
		arr[ dest ].head = tempNode;
		
   	}

	void printGraph()
   	{
   		int index;
   		for ( index = 0; index < V; index++ )
   		{
   			Node *temp = arr[ index ].head;

   			cout << endl << "Adjacency list of vertex " << index << endl;
   			cout << "current energy: " << temp->currentEnergy << endl;
   			cout << "energy consumption: " << temp->energyUsed << endl;

   			cout << "head "; 			
			while( temp )
   			{
   				cout << "-> " << temp->dest;
   				temp = temp->next;
   			}
   			cout << endl;
   		}
   	}



};

void createRandomEnergy( float arr[], int totalSize, int sinkSize );
void createRandomPointers( int pointers[], int totalSize, int sinkSize );
void createNetwork( float energy[], int pointers[], Graph & graph );
bool numExists( int arr[], int index, int temp );

int main()
{
	int totalPacketCommands = 0;
	int nodeSize; 
	int sinkSize;
	int totalSize;
	ifstream fin;
	PacketInfo packetArr[ MAX_NUM ];

	fin.open( "input.txt" );

	if( !fin.good() )
	{
		return 0;
	}

	fin >> nodeSize;
	fin >> sinkSize;
	cout << nodeSize;
	cout << sinkSize;

	totalSize = nodeSize + sinkSize;


	 //keep inputting until there is no more in input file
while( !fin.eof() )
{
	fin >> packetArr[ index ]. nodeNum;
	fin >> packetArr[ index ]. numberOfPackets;
	totalPacketCommands++;
}

	int graph[ totalSize ][ totalSize ];

	

	/*
	int size = 8;
	int sinkSize;
	int totalSize;
	

	cout << "Enter the number of sinks (1-2) in the network: ";
	cin >> sinkSize;
	cout << endl;

	totalSize = size + sinkSize;
	Graph graph( totalSize );

	float energy[ totalSize ];
	int pointers[ totalSize ];

	createRandomEnergy( energy, totalSize, sinkSize );
	createRandomPointers( pointers, totalSize, sinkSize );

	createNetwork( energy, pointers, graph );

	graph.printGraph();

	*/
	return 0;
}

void createRandomEnergy( float arr[], int totalSize, int sinkSize )
{

	srand( time( 0 ) );
	for ( int index = 0; index < totalSize; index++ )
	{
		if( index < sinkSize )
		{
			arr[ index ] = 0;
		}
		else
		{
			arr[ index ] = ( float ) ( ( rand() % 100 ) + 1 ) / (float) 100.0;
		}
		cout << "energy " << arr[ index ] << endl;
	}
}

void createRandomPointers( int pointers[], int totalSize, int sinkSize )
{
	srand( time( 0 ) );
	int pointerTemp;
	bool exists = false;
	for ( int index = 0; index < totalSize; index++ )
	{
		pointerTemp = rand() % totalSize;
		//don't want sinks to point to eachother
		if( index < sinkSize )
		{
			while( pointerTemp == index || pointerTemp == index + 1 )
			{
				pointerTemp = rand() % totalSize;
			}
	
			exists = numExists( pointers, index, pointerTemp );

			while( exists )
			{
				pointerTemp = rand() % totalSize;

				while( pointerTemp == index )
				{
					pointerTemp = rand() % totalSize;	
				}

				exists = numExists( pointers, index, pointerTemp );

				if( sinkSize == index + 1 && pointerTemp < sinkSize )
				{
					exists = true;
				}
				if( pointers[ index ] == pointerTemp && pointers[ pointerTemp ] == index )
				{
					exists = true;
				}
			}

			pointers[ index ] = pointerTemp;
		}
		else
		{

			while( pointerTemp == index )
			{
				pointerTemp = rand() % totalSize;	
			}

			exists = numExists( pointers, index, pointerTemp );

			while( exists )
			{
				pointerTemp = rand() % totalSize;

				while( pointerTemp == index )
				{
					pointerTemp = rand() % totalSize;	
				}
				exists = numExists( pointers, index, pointerTemp );

				if( pointers[ index ] == pointerTemp && pointers[ pointerTemp ] == index )
				{
					exists = true;
				}
			}

			pointers[ index ] = pointerTemp;
		}
		cout << "Pointers " << pointers[ index ] << endl;
	}
}


void createNetwork( float energy[], int pointers[], Graph & graph )
{
	for ( int index = 0; index < graph.V; index++ )
	{
		graph.addEdge( index, 100.0, energy[ index ], 100.0, energy[ pointers[ index ]], pointers[ index ] );
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






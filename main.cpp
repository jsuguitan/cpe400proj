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

using namespace std;

//////////////////////////
//// Graph Definition ////
//////////////////////////

struct PacketInfo{
	int nodeNum;
	int numberOfPackets;
};

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

///Added New Struct to contain packetData

struct PacketInfo
{
    int nodeNum;
    int numberOfPackets;
};


class Graph{ 
    
public: 
    int V;
    struct AdjList *arr;

    // function that creates a graph of V verticies
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

    //function that adds an edge to an undirected graph
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

struct MinHeapNode
{

};

struct MinHeap
{

};



void createRandomEnergy( float arr[], int totalSize, int sinkSize );
bool create_links( Graph &graph, int totalSize, int sinkSize );

int main()
{

	int nodeSize; 
	int sinkSize;
	int totalSize;
    int numberOfPacketCommands = 0;
    int index;
    PacketInfo *packetArr;
	bool success;
	ifstream fin;

	fin.open( "links.txt" );

	if( !fin.good() )
	{
		return 0;
	}
	else 
	{
		fin >> nodeSize;
		fin >> sinkSize;
		totalSize = nodeSize + sinkSize;
	}
	fin.close();

    fin.open( "packet.txt" );
    
    if( !fin.good() )
    {
        return 0;
    }
    else
    {
        //read in first number of file that shows how many commands there are
        fin >> numberOfPacketCommands;

        //create a array of PacketInfo
        packetArr = new PacketInfo[ numberOfPacketCommands ];

        //input data into packetArr
        for( index = 0; index < numberOfPacketCommands; index++ )
        {
            fin >> packetArr[ index ].nodeNum;
            fin >> packetArr[ index ].numberOfPackets;           
        }        

    }
    fin.close();
    

    // create a graph given how many sinks and nodes are used
	Graph graph( totalSize );

	success = create_links( graph, totalSize, sinkSize );
	if( !success )
	{
		cout << "Invalid graph file. Exiting now. " << endl;
		return 0;
	}

	graph.printGraph();

	return 0;
}

bool create_links( Graph &graph, int totalSize, int sinkSize )
{
	ifstream fin;
	int vertex;
	int edges;
	int pointer;
	int temp;
	float energy[ totalSize ];
	fin.open( "links.txt" );

	createRandomEnergy( energy, totalSize, sinkSize );

	if( !fin.good() )
	{
		return false;
	}
	fin >> temp;
	fin >> temp;

	for ( int index = 0; index < totalSize; index++ )
	{
		fin >> vertex;
		fin >> edges;
		for ( int subIndex = 0; subIndex < edges; subIndex++ )
		{
			fin >> pointer;
			graph.addEdge( index, 100.00, energy[ index ], 100.0, energy[ pointer ], pointer );
		}
	}

	return true;
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
		//cout << "energy " << arr[ index ] << endl;
	}
}

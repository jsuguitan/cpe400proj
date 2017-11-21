// Program Information /////////////////////////////////////////////////////////
/**
  * @file network.h
  *
  * @brief network class header file    
  * 
  * @details defines class
  *
  * @version 1.00 Carli DeCapito
  *			 Original Documentation (11/13/17)
  *
  * @note None
  */


#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>

using namespace std;



struct Node{
  int currentEnergy;
  int energyUse;
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




};
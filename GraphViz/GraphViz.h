#ifndef GRAPHVIZ_H
#define GRAPHVIZ_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <map>

using namespace std;

class	Node;
typedef string				Key;
typedef Node				Value;
typedef pair<Key, Value>    par;
typedef pair<Key, string>   par2;
typedef map<Key, Value>     MapNodes;
typedef map<Key, string>    MapEdges;
typedef MapNodes::iterator  itNodes;
typedef MapEdges::iterator  itEdges;



//Determine what function will be called
void Menu();

// Check if a graph with same name exist - Return 0 if it exist or 1 if doesn't
int Verify(string);

// Create graph
void createGraph(string, string);

//Open a existing graph and load it information
void openGraph(string, string, MapNodes&, MapEdges&);

//Create a Node
void createNode(MapNodes&);

//Create an Edge
void createEdge(MapEdges&, MapNodes);

// Write the graph in a .txt
void writeGraph(string, string, MapNodes, MapEdges, int);

// Write "}" in .txt file to close the graph
void closeGraph(string);

////////////////////////////////////////////////////////////////////////////////
//Graphviz Class


class GraphV {
  //variables
  MapNodes  nodes_;
	MapEdges  edges_;
  string    out_file_ = "";
  bool      graph_type_;

public:
  GraphV() {}
  GraphV( string, bool );

};


#endif // !GRAPHV_H
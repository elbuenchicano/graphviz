#include "src/GraphViz.h"
#include <fstream>

using namespace std;

int main() {
	//Menu();
/*  lstProp list;
  list.push_back(parProp("shape", "triangle"));
  list.push_back(parProp("color", "gray"));
  
  GraphV g1("g1", false);
  g1.addPropGraph("rankdir", "LR");

  g1.addProp(list, "style", "bold");
  g1.insertNode("D");

  g1.addProp("color", "green");
  g1.addProp("width", "0.7");
  g1.insertNode("A");

  g1.addProp("color", "red");
  g1.addProp("shape", "diamond");
  g1.insertNode("B");

  g1.addProp("shape", "box");
  g1.addProp("style", "dotted");
  g1.insertNode("C");

  g1.addProp("style", "bold");
  g1.insertEdge("A", "B");

  g1.addPropGraph("concentrate", "true");

  g1.addProp("color", "pink");
  g1.addProp("style", "dotted");
  g1.insertEdge("A", "C");

  g1.addProp("width", "1.1");
  g1.insertEdge("C", "B");
  
  ofstream arc("out.txt");
  g1.generate(arc);
  arc.close();
  */

  
  //VGraph g1("hola");

  graphViz::lstProp props{ {"sides","9"}, {"distortion" , "0.936354"}, {"orientation" , "28"}, {"skew" , "-0.126818"}, {"color" , "salmon2"} };
  
  graphViz::VProperties h(props);
  
  h.addProp("color", "red");
  
  graphViz::VNode node1("node1",h);
  graphViz::VNode node2("node2",h);
   
  graphViz::VEdge edge("node1", "node2");

  graphViz::VGraph g1("a", "rankdir","LR", 0);

  g1.addNode(node1);
  g1.addNode(node2);
  g1.addEdge(edge);

  
  ofstream arc("out.txt");
  arc << g1.str();
  arc.close();
  

	return 0;
}



















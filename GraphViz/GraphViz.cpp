#include "GraphViz.h"

class Node
{
public:
	// Constructor Definition
	Node(string name, string shape = "\"\"", string color = "\"\"", string width = "0.6") {
		Name = name;
		Shape = shape;
		Color = color;
		Width = width;
	}
	Node() {}
	string Name;
	string Shape;
	string Color;
	string Width;
};


void Menu() {
	int i = 0, ver, op;
	string myGraph, myGraphWT, Oper;
	MapNodes Nodes;
	MapEdges Edges;

	while (Oper != "8") {
		cout << "1 - Create Graph\n2 - Open Graph" << endl;
		getline(cin, Oper);

		if (Oper == "1") {
			cout << "Graph Name: ";
			getline(cin, myGraphWT);
			myGraph = myGraphWT + ".txt";
			ver = Verify(myGraph);
			if (ver == 1) {
				createGraph(myGraph, myGraphWT);
				Oper = "8";
				op = 1;
			}
			else {
				cout << "This graph already exist\n\n" << endl;
				Oper = "0";
			}
		}
		else if (Oper == "2") {
			cout << "Graph Name: ";
			getline(cin, myGraphWT);
			myGraph = myGraphWT + ".txt";
			ver = Verify(myGraph);
			if (ver == 0) {
				openGraph(myGraph, myGraphWT, Nodes, Edges);
				Oper = "8";
				op = 2;
			}
			else {
				cout << "This graph don't exist\n\n" << endl;
				Oper = "0";
			}
		}
		else {
			cout << "Invalid Operation\n\n" << endl;
			Oper = "0";
		}
	}
	while (Oper != "9") {
		cout << "\n\n1 - Create Node\n2 - Create Edge\n9 - Exit" << endl;
		getline(cin, Oper);

		if (Oper == "1") {
			createNode(Nodes);
		}
		else if (Oper == "2") {
			createEdge(Edges, Nodes);
		}
		else {
			if (Oper != "9") {
				cout << "Invalid Operation\n" << endl;
				Oper = "0";
			}
		}
	}
	writeGraph(myGraph, myGraphWT, Nodes, Edges, op);
	closeGraph(myGraph);
}

// Check if a graph with same name exist - Return 0 if it exist or 1 if doesn't
int Verify(string myGraph) {
	ifstream obj;
	obj.open(myGraph);
	if (obj.is_open())
	{
		obj.close();
		return 0;
	}
	else {
		return 1;
	}
}


void createGraph(string myGraph, string myGraphWT)
{
	fstream outfile;
	outfile.open(myGraph, ios::app);
	outfile << "digraph " << myGraphWT << " {" << endl;
	outfile.close();
}

//Open a existing graph and load it information
void openGraph(string myGraph, string myGraphWT, MapNodes& Nodes, MapEdges& Edges) {
	int i, j, stop_no = 0;
	streamoff pos;
	string line, node, shape, color, width;
	ifstream infile;
	Node getNode;
	pos = myGraphWT.size() + 11;
	infile.open(myGraph, ios::in || ios::beg);
	infile.seekg(pos);
	while (!infile.eof()) {
		getline(infile, line);
		if (line.size() > 10) {
			if (line[0] == 'n' && line[1] == 'o' && line[2] == 'd' && line[3] == 'e' && line[4] == ' ' && line[5] == '[' && line[6] == 's' && line[7] == 'h' && line[8] == 'a' && line[9] == 'p' && line[10] == 'e') {
				for (i = 0; i < line.size(); i++) {
					if (i > 12) {
						if (line[(i - 7)] == 's' && line[(i - 6)] == 'h' && line[(i - 5)] == 'a' && line[(i - 4)] == 'p' && line[(i - 3)] == 'e' && line[(i - 2)] == '=') {
							for (j = 0; (j + i) < line.size(); j++) {
								if (line[(j + i)] == '\"' && line[(j + i + 1)] == ' ' && line[(j + i + 2)] == ',' && line[(j + i + 3)] == 'w') {
									break;
								}
								else {
									shape = shape + line[(j + i)];

								}
							}
						}
						if (line[(i - 6)] == 'w' && line[(i - 5)] == 'i' && line[(i - 4)] == 'd' && line[(i - 3)] == 't' && line[(i - 2)] == 'h' && line[(i - 1)] == '=') {
							for (j = 0; (j + i) < line.size(); j++) {
								if (line[(j + i)] == ' ' && line[(j + i + 1)] == ',' && line[(j + i + 2)] == 'c' && line[(j + i + 3)] == 'o') {
									break;
								}
								else {
									width = width + line[(j + i)];

								}
							}
						}
						if (line[(i - 7)] == 'c' && line[(i - 6)] == 'o' && line[(i - 5)] == 'l' && line[(i - 4)] == 'o' && line[(i - 3)] == 'r' && line[(i - 2)] == '=') {
							for (j = 0; (j + i) < line.size(); j++) {
								if (line[(j + i)] == '"' && line[(j + i + 1)] == ']' && line[(j + i + 2)] == ';' && line[(j + i + 3)] == ' ') {
									break;
								}
								else {
									color = color + line[(j + i)];

								}
							}
						}
						if (line[(i - 4)] == '"' && line[(i - 3)] == ']' && line[(i - 2)] == ';' && line[(i - 1)] == ' ') {
							for (j = 0; (j + i) < line.size(); j++) {
								if (line[(j + i)] == ';') {
									stop_no = 1;
									break;
								}
								else {
									node = node + line[(j + i)];

								}
							}
						}
					}
					if (stop_no == 1) {
						getNode.Name = node;
						getNode.Shape = shape;
						getNode.Width = width;
						getNode.Color = color;
						Nodes.insert(par(getNode.Name, getNode));
						node = "";
						shape = "";
						width = "";
						color = "";
						stop_no = 0;
						break;
					}
					else {
						stop_no = 0;
					}
				}
			}
			else {
				if (line.size() > 2) {
					Edges.insert(par2(line, line));
				}
			}
		}
		else if (line.size() > 2 && line.size() <= 9) {
			Edges.insert(par2(line, line));
		}
	}
}

//Create Node
void createNode(MapNodes& Nodes) {
	string name, shape = "repeat", color = "repeat", width = "repeat";
	itNodes iterNodes;

	cout << "Name: ";
	getline(cin, name);
	while (shape == "repeat") {
		cout << "Shape (1-Square\t 2-Circle\t 3-Triangle\t 4-Default): ";
		getline(cin, shape);
		if (shape == "1") {
			shape = "\"square\"";
		}
		else if (shape == "2") {
			shape = "\"circle\"";
		}
		else if (shape == "3") {
			shape = "\"triangle\"";
		}
		else if (shape == "4") {
			shape = "\"\"";
		}
		else {
			shape = "repeat";
		}
	}
	while (width == "repeat") {
		cout << "Width (0.6 to 1.5): ";
		getline(cin, width);
		if (width == "0.6" || width == "0.7" || width == "0.8" || width == "0.9" || width == "1" || width == "1.0" || width == "1.1" || width == "1.2" || width == "1.3" || width == "1.4" || width == "1.5") {
			break;
		}
		else {
			width = "repeat";
		}
	}
	while (color == "repeat") {
		cout << "Color (1-Blue\t 2-Red\t 3-Green\t 4-Default\t 5-Others): ";
		getline(cin, color);
		if (color == "1") {
			color = "Blue";
		}
		else if (color == "2") {
			color = "Red";
		}
		else if (color == "3") {
			color = "Green";
		}
		else if (color == "4") {
			color = "";
		}
		else if (color == "5") {
			cout << "Color: ";
			getline(cin, color);
		}
		else {
			color = "repeat";
		}
	}

	Node Node1(name, shape, color, width);
	iterNodes = Nodes.find(name);
	if (iterNodes == Nodes.end()) {
		Nodes.insert(par(name, Node1));
	}
	else {
		cout << "A node with the same name already exist" << endl;
	}
}

//Create Edge
void createEdge(MapEdges& Edges, MapNodes Nodes) {
	int check = 1;
	string Node1, Node2, Edge, Label = "", Check_Label = "", Style;
	itNodes iterNodes;
	itEdges iterEdges;

	cout << "Nodes to create the edge: " << endl;
	cout << "Node 1: ";
	getline(cin, Node1);
	iterNodes = Nodes.find(Node1);
	if (iterNodes == Nodes.end()) {
		cout << "Node 1 doesn't exists. Create it before create an edge." << endl;
		check = 0;
	}
	else {
		cout << "Node 2: ";
		getline(cin, Node2);
		iterNodes = Nodes.find(Node2);
		if (iterNodes == Nodes.end()) {
			cout << "Node 2 doesn't exists. Create it before create an edge." << endl;
			check = 0;
		}
	}
	if (check == 1) {
		while (1) {
			cout << "Edge style (1- Bold\t 2- Dotted\t 3- Default): ";
			getline(cin, Style);
			if (Style == "1" || Style == "2" || Style == "3") {
				break;
			}
		}
		while (1) {
			cout << "Add label? (yes or no): ";
			getline(cin, Check_Label);
			if (Check_Label == "yes") {
				cout << "Label: ";
				getline(cin, Label);
				break;
			}
			else if (Check_Label == "no") {
				break;
			}
		}
		Edge = Node1 + " -> " + Node2 + " [label =\"" + Label + "\", style =\"" + Style + "\"];";
		iterEdges = Edges.find(Edge);
		if (iterEdges == Edges.end()) {
			Edges.insert(par2(Edge, Edge));
		}
		else {
			cout << "This edge already exist." << endl;
		}
	}
}

//Create a subgraph
/*void createSubGraph(string myGraph, MapEdges Edges, MapNodes Nodes){

}*/

// Write the graph in a .txt file
void writeGraph(string myGraph, string myGraphWT, MapNodes Nodes, MapEdges Edges, int op) {
	itNodes iterNodes;
	itEdges iterEdges;
	ofstream outfile;
	if (op == 1) {
		outfile.open(myGraph, ios::out || ios::ate);
		outfile.seekp(0, ios::end);
		for (iterNodes = Nodes.begin(); iterNodes != Nodes.end(); iterNodes++) {
			outfile << "node [shape=" << iterNodes->second.Shape << " ,width=" << iterNodes->second.Width << " ,color=\"" << iterNodes->second.Color << "\"]; " << iterNodes->second.Name << ";" << endl;
		}
		for (iterEdges = Edges.begin(); iterEdges != Edges.end(); iterEdges++) {
			outfile << iterEdges->second << endl;
		}
	}
	else if (op == 2) {
		//remove(myGraph.c_str());
		outfile.open(myGraph, ios::out);
		//outfile.seekp(0, ios::end);
		outfile << "digraph " << myGraphWT << " {" << endl;
		for (iterNodes = Nodes.begin(); iterNodes != Nodes.end(); iterNodes++) {
			outfile << "node [shape=" << iterNodes->second.Shape << " ,width=" << iterNodes->second.Width << " ,color=\"" << iterNodes->second.Color << "\"]; " << iterNodes->second.Name << ";" << endl;
		}
		for (iterEdges = Edges.begin(); iterEdges != Edges.end(); iterEdges++) {
			outfile << iterEdges->second << endl;
		}
	}
	outfile.close();
	cout << "Graph was wrote with success" << endl;
}

//Close Graph
void closeGraph(string myGraph) {
	ifstream infile;
	string check;
	int i = 0;

	infile.open(myGraph, ios::in);
	infile.seekg(-1, ios::end);
	infile >> check[0];
	if (check[0] != '}')
		i = 1;
	else {}
	infile.close();

	if (i == 1) {
		ofstream outfile;
		outfile.open(myGraph, ios::app);
		outfile << "}";
		outfile.close();
	}
	else {}
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//Graph Contructor
GraphV::GraphV(string out, bool type = true):
out_file_(out){
   
}



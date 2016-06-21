#ifndef GRAPHVIZ_H
#define GRAPHVIZ_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <map>
#include <list>
#include <sstream>


namespace graphViz {
  
  class VNode;
  class VEdge;

  typedef std::string             strT;
  typedef std::pair<strT, strT>   propT;
  typedef std::list<propT>        lstProp;
  typedef std::map<strT, VNode>   MapVNodes;
  typedef std::pair<strT, VNode>  pStrNode;
  typedef std::list<VEdge>        LstVEdges;


  class VProperties {
    lstProp props_;
  public:
    //main functions............................................................
    VProperties () {}
    VProperties ( strT, strT );
    VProperties ( lstProp &);
    VProperties ( propT   &);
    VProperties ( VProperties &);
    
    //returns the string of the item 
    strT str();
    strT strSingle();
    //property Ex: shape, style, color...
    //property content Ex: square, bold, red....

    void addProp ( strT, strT );
    //list of properties
    //property Ex: shape, style, color...
    //property content Ex: square, bold, red....
    void addProp ( propT );
    //list of properties
    //property Ex: shape, style, color...
    //property content Ex: square, bold, red....
    void addProp (lstProp &);
    //list of properties
    //property Ex: shape, style, color...
    //property content Ex: square, bold, red....
    void addProp(const lstProp &);

    //overloadign operators
    //VProperties & operator = (VProperties & );
    VProperties & operator = (const VProperties &);
    VProperties & operator + (VProperties & );
    lstProp     & operator * ();
  };

  //////////////////////////////////////////////////////////////////////////////
  //class node 
  class VNode {
    strT        id_;

  public:
    //variables.................................................................
    VProperties props_;

    //constructors..............................................................
    VNode () {}
    VNode ( strT, VProperties & );
    VNode ( strT, strT, strT );
    VNode ( strT );

    //main functions............................................................
    strT str();
    strT getId();
  };
  //////////////////////////////////////////////////////////////////////////////
  //class edge
  class VEdge {
    
  public:
    strT        id_out_,
                id_in_;
    VProperties props_;

    //constructors..............................................................
    VEdge( strT, strT, VProperties & );
    VEdge( strT, strT, strT, strT );
    VEdge( strT, strT );
    VEdge( VEdge &&);
    VEdge( const VEdge &);
    VEdge( ){}

    ///main functions............................................................
    //true = graph, false = digraph
    strT str(bool);
    VEdge & operator = (VEdge &);
  };
  //////////////////////////////////////////////////////////////////////////////
  //class graph
  class VGraph {
    strT  id_;
    bool  type_;
  public:
    MapVNodes   nodes_;
    LstVEdges   edges_;
    VProperties props_;

    //constructors..............................................................
    VGraph ( strT, VProperties &, bool );
    VGraph ( strT, strT, strT, bool );
    VGraph ( strT, bool );

    
    ///main functions............................................................
    //true = graph, false = digraph
    strT  str();
    bool  addNode(VNode &);
    bool  addEdge(VEdge &);

    
  };

}




#endif // !GRAPHV_H
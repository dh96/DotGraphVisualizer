

#ifndef NODE_H
#define NODE_H



#include <string>
#include "Liste.h"

using namespace std;

class Edge; //forward Declaration

class Node{
private:
    string node_key;
    Liste<Edge*> *edges;
public:
    Node(string name);
    Node();
    ~Node();
    string getKey(void);
    Liste<Edge*> *getEdges(void);
    void setKey(string k);
    void setNewEdge(Edge* edge);
};
#endif 
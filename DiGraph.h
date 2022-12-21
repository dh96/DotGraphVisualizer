
#ifndef DIGRAPH_H
#define DIGRAPH_H

#include <fstream>
#include "Tokenizer.h"
#include "Edge.h"
#include "PriorityQueue.h"

using namespace std;
class DiGraph{
private:
    Liste<Node*> *nodes;
public:
    DiGraph();
    ~DiGraph();
    void addNode(Node *node);
    void addEdge(string key1,string key2,float weight);
    Liste<Node*> getNeighbours(string key);
    Liste<Edge*>* getEdges(string key);
    Liste<Node*>* getNodes();
    void load();
    void save();
    Liste<Edge*>*dijkstraShortestPath(string start,string end);

};

#endif 
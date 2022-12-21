
#ifndef EDGE_H
#define EDGE_H

using namespace std;
#include <string>

class Node; //forward Declaration

class Edge{
private:
    Node *startnode;
    Node *endnode;
    float weight;

public:
    Edge();
    float getweight(void);
    Node *getStartNode(void);
    Node *getEndNode(void);
    void setWeight(float w);
    void setStartNode(Node *n);
    void setEndNode(Node *n);
};

#endif 
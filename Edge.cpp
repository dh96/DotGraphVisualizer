

#include "Edge.h"

Edge::Edge() {
    startnode=0;
    endnode=0;
    weight=0;
}

Node* Edge::getEndNode() {
    return endnode;
}

Node* Edge::getStartNode() {
    return startnode;
}

float Edge::getweight() {
    return weight;
}

void Edge::setEndNode(Node *n) {
    endnode=n;
}

void Edge::setStartNode(Node *n) {
    startnode=n;
}
void Edge::setWeight(float w) {
    weight=w;
}


#include "Node.h"

Node ::Node(string key) {
    node_key =key;
    edges= new Liste<Edge*>;
}

Node::Node() {
    node_key="";
    edges= new Liste<Edge*>;
}
Node::~Node() {
    delete[] edges;
}
string Node::getKey() {
    return node_key;
}
Liste<Edge*>* Node::getEdges(void){
    return edges;
}

void Node::setKey(string k) {
    node_key=k;

}
void Node::setNewEdge(Edge *edge) {
    edges->append(edge);
}
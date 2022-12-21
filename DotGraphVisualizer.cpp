
#include "DotGraphVisualizer.h"


void DotGraphVisualizer::visualize(DiGraph *graph) {

   cout << "digraph {" << endl;

   for(int i=0; i < graph->getNodes()->size();i++){
       for(int k=0; k < graph->getNodes()->getValueAt(i)->getEdges()->size();k++){
           cout << '"' << graph->getNodes()->getValueAt(i)->getEdges()->getValueAt(k)->getStartNode()->getKey() << '"' << "      ->      "
           <<  '"' << graph->getNodes()->getValueAt(i)->getEdges()->getValueAt(k)->getEndNode()->getKey() << '"' << "       [label=" << graph->getNodes()->getValueAt(i)->getEdges()->getValueAt(k)->getweight() << "]"  << ";"<< endl;
       }
   }

   cout << "}" << endl;
}
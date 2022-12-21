#include <iostream>
#include "DotGraphVisualizer.h"
#include "Exception.h"
using namespace std;

int main() {
    DiGraph *new_graph = new DiGraph();
    DotGraphVisualizer *dotGraph = new DotGraphVisualizer;
    Liste <Edge*>*dijkstra;
    int choice;
    string name, startnode, endnode;
    float weight;
    int result=0;
    int size=0;



    while(1){
        cout << endl;
        cout << "[1]Knoten hinzufuegen" << endl;
        cout << "[2]Knoten entfernen" << endl;
        cout << "[3]Kante hinzufuegen" << endl;
        cout << "[4]Kante entfernen" << endl;
        cout << "[5]Gewicht von Kante veraendern" << endl;
        cout << "[6]Graphen in Datei speichern" << endl;
        cout << "[7]Graphen laden" << endl;
        cout << "[8]Knoten und Kanten loeschen" << endl;
        cout << "[9]Dijkstra-shortest-path" << endl;
        cout << endl;
        cout << "Auswahl: ";
        cin >> choice ;
        switch (choice){
            case 1:
                cout << endl;
                cout << "Namen des Knotens eingeben: ";
                cin >> name;
                try {
                    new_graph->addNode(new Node(name));
                }catch(Exception e){
                    cerr << e.return_error() << endl;
                }
                break;
            case 2:
                int result;
                cout << endl;
                cout<<"[Alle Nodes]"<< endl;
                cout << "Size Nodes: " << new_graph->getNodes()->size() << endl;
                for(int i=0; i < new_graph->getNodes()->size();i++){
                    cout << new_graph->getNodes()->getValueAt(i)->getKey() << endl;
                }

                cout << endl;
                cout << "Namen des Knotens eingeben: ";
                cin >> name;
                cout << "Name: " << name << endl;

                for(int i=0; i < new_graph->getNodes()->size();i++){
                    if(name ==  new_graph->getNodes()->getValueAt(i)->getKey()) {
                        try {
                            new_graph->getNodes()->remove(new_graph->getNodes()->getValueAt(i));
                            result = 1;
                            break;
                        } catch (Exception e) {
                            cerr << e.return_error() << endl;
                        }
                    }
                    else
                        result=0;
                }
                if(result == 1)
                    cout << "Node erfolgreich geloescht." << endl;
                else
                    cout << "Node nicht gefunden." << endl;

                result=0;
                break;

            case 3:
                cout << "[Verfuegbare Knoten]" << endl;
                for(int i=0; i < new_graph->getNodes()->size();i++){
                    cout << "-->" << new_graph->getNodes()->getValueAt(i)->getKey() << "<--"<< endl;
                }
                cout << endl;
                cout << "Startnode: ";
                cin >> startnode ;
                cout << endl;
                cout << "Endnode: " ;
                cin >> endnode;
                cout << endl;
                cout << "Weight: ";
                cin >> weight;

                try {
                    new_graph->addEdge(startnode, endnode, weight);
                }catch(Exception e){
                    cout << e.return_error() << endl;
                }
                break;

            case 4:
                cout << endl;
                cout << "[Alle verfuegbaren Kanten]" << endl;
                for(int i=0; i < new_graph->getNodes()->size();i++){
                    for(int k=0; k < new_graph->getNodes()->getValueAt(i)->getEdges()->size();k++){
                        cout <<"[Startnode]"<< new_graph->getNodes()->getValueAt(i)->getEdges()->getValueAt(k)->getStartNode()->getKey()<< " [Endnode] " << new_graph->getNodes()->getValueAt(i)->getEdges()->getValueAt(k)->getEndNode()->getKey() <<" [Weight] " << new_graph->getNodes()->getValueAt(i)->getEdges()->getValueAt(k)->getweight() << endl;
                    }
                }

                cout << endl;
                cout << "Startnode: ";
                cin >> startnode ;
                cout << endl;
                cout << "Endnode: " ;
                cin >> endnode;
                cout << endl;
                cout << "Weight: ";
                cin >> weight;

                for(int i=0; i < new_graph->getNodes()->size();i++){
                    for(int k=0; k < new_graph->getNodes()->getValueAt(i)->getEdges()->size();k++) {
                        if (startnode == new_graph->getNodes()->getValueAt(i)->getEdges()->getValueAt(k)->getStartNode()->getKey() &&
                            endnode == new_graph->getNodes()->getValueAt(i)->getEdges()->getValueAt(k)->getEndNode()->getKey() &&
                            weight == new_graph->getNodes()->getValueAt(i)->getEdges()->getValueAt(k)->getweight()) {
                            try {
                                new_graph->getNodes()->getValueAt(i)->getEdges()->remove(new_graph->getNodes()->getValueAt(i)->getEdges()->getValueAt(k));
                            } catch (Exception e) {
                                cerr << e.return_error() << endl;
                            }
                            result=1;
                        }
                    }
                }
                if(result == 0)
                    cerr << "Kante wurde nicht gefunden!" << endl;
                else
                    cout << "Kante erfolgreich geloescht!" << endl;

                result=0;
                break;

            case 5:
                cout << endl;
                cout << "[Alle verfuegbaren Kanten]" << endl;
                for(int i=0; i < new_graph->getNodes()->size();i++){
                    for(int k=0; k < new_graph->getNodes()->getValueAt(i)->getEdges()->size();k++){
                        cout <<"[Startnode]"<< new_graph->getNodes()->getValueAt(i)->getEdges()->getValueAt(k)->getStartNode()->getKey()<< " [Endnode] " << new_graph->getNodes()->getValueAt(i)->getEdges()->getValueAt(k)->getEndNode()->getKey() <<" [Weight] " << new_graph->getNodes()->getValueAt(i)->getEdges()->getValueAt(k)->getweight() << endl;
                    }
                }

                cout << endl;
                cout << "Startnode: ";
                cin >> startnode ;
                cout << endl;
                cout << "Endnode: " ;
                cin >> endnode;
                cout << endl;
                cout << "Neues Gewicht: " ;
                cin >> weight;

                for(int i=0; i < new_graph->getNodes()->size();i++){
                    for(int k=0; k < new_graph->getNodes()->getValueAt(i)->getEdges()->size();k++) {
                        if (startnode == new_graph->getNodes()->getValueAt(i)->getEdges()->getValueAt(k)->getStartNode()->getKey() &&
                            endnode == new_graph->getNodes()->getValueAt(i)->getEdges()->getValueAt(k)->getEndNode()->getKey())
                            try {
                                new_graph->getNodes()->getValueAt(i)->getEdges()->getValueAt(k)->setWeight(weight);
                            } catch (Exception e) {
                                cerr << e.return_error() << endl;
                            }
                            result=1;
                        }
                    }
                if(result == 0)
                    cerr << "Veränderung fehlgeschlagen" << endl;
                else
                    cout << "Gewicht erfolgreich verändert" << endl;

                result=0;
                break;

            case 6:
                try {
                    new_graph->save();
                }catch(Exception e){
                    cerr << e.return_error() << endl;
                }
                break;

            case 7:
                try{
                    new_graph->load();
                }catch(Exception e){
                    cerr << e.return_error() << endl;
                }
                break;
            case 8:

                for(int i=0; i < new_graph->getNodes()->size() ;i++){
                    for(int k=0; k < new_graph->getNodes()->getValueAt(i)->getEdges()->size();k++){
                        try {
                            new_graph->getNodes()->getValueAt(i)->getEdges()->remove(
                                    new_graph->getNodes()->getValueAt(i)->getEdges()->getValueAt(k));
                        }catch(Exception e){
                            cout << e.return_error() << endl;
                        }
                    }
                }

                size = new_graph->getNodes()->size();

                for(int n=0; n < size;n++){
                    try {
                        new_graph->getNodes()->remove(new_graph->getNodes()->getValueAt(0));
                    }catch(Exception e){
                        cout << e.return_error() << endl;
                    }
                }
                cout << "Alle Knoten & Kanten erfolgreich geloescht!" << endl;
                size=0;
                break;

            case 9:
                cout << endl;
                cout<<"[Alle Nodes]"<< endl;
                cout << "Size Nodes: " << new_graph->getNodes()->size() << endl;
                for(int i=0; i < new_graph->getNodes()->size();i++){
                    cout << new_graph->getNodes()->getValueAt(i)->getKey() << endl;
                }

                cout << endl;
                cout << "Startnode: ";
                cin >> startnode ;
                cout << endl;
                cout << "Endnode: " ;
                cin >> endnode;

                dijkstra=new_graph->dijkstraShortestPath(startnode,endnode);

                for(int i=0; i < dijkstra->size();i++){
                    cout << "Shortest Path: " << dijkstra->getValueAt(i)->getweight() << endl;
                }

                break;




            default:
                cout << "Eine der Nr. in [] eingeben... " << endl;
                break;
        }
    }

}
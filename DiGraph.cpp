
#include "DiGraph.h"
#include "Exception.h"


void inorder(pqentry<Node*> *root)
{
    if (root != NULL)
    {
        inorder(root->node_left);
        cout << "Priority: " << root->priority << " Value: " << root->value << " ID: " << root->id << endl;
        inorder(root->node_right);
    }
}

Liste<Edge*> *DiGraph::dijkstraShortestPath(string start, string end) {
    PriorityQueue<Node*> priorityQueue(4);
    pqentry<Node*> *root=NULL;
    pqentry<Node*> *smallest;
    Node *smallest_node;
    Liste<Edge*>*result = new Liste<Edge*>;
    float *dist= new float[nodes->size()];
    Node **previous = new Node*[nodes->size()];
    int stelle_u,stelle_v;

    for(int i=0; i < nodes->size();i++){
        if(nodes->getValueAt(i)->getKey() == start) {
            dist[i] = 0;
        }
        else
            dist[i] = 99999;

        previous[i]= NULL;

        if(root == NULL)
            root = priorityQueue.insert(priorityQueue.get_entrys()[0],nodes->getValueAt(i),dist[i]);
        else
            priorityQueue.insert(root,nodes->getValueAt(i),dist[i]);

    }

    while(!priorityQueue.isEmpthy()){
        cout << "NEW RUN" << endl;

        for(int i=0; i < nodes->size();i++){
            cout << "dist["<<i<<"]:"<< dist[i] << endl;
        }

        for(int i=0; i < nodes->size();i++){
            cout << "previous["<<i<<"]:"<< previous[i] << endl;
        }

        smallest = priorityQueue.smallest_node(root);
        cout << "smallest: " << smallest->priority << endl;
        for(int i=0; i < nodes->size();i++){
            if(smallest->value->getKey() == nodes->getValueAt(i)->getKey()){
                stelle_u=i;
                cout << "stelle u: " << stelle_u << endl;
                break;
            }
        }

        //Liste mit allen ausgehenden Kanten von smallest
        Liste<Edge*>*out_smallest_edges = new Liste<Edge*>;

        if(smallest->value->getEdges()->size() == 0) {
            break;
        }

        for(int i=0; i < smallest->value->getEdges()->size();i++){
            out_smallest_edges->append(smallest->value->getEdges()->getValueAt(i));
        }
        cout << "Edges vom Smallest: " << out_smallest_edges->size() << endl;

        smallest_node=smallest->value;

        try{
            root=priorityQueue.extractMin(root,smallest->priority);
        }catch(const char *msg){
            cerr << msg << endl;
        }


        for(int i=0; i < out_smallest_edges->size();i++){
            Node *v = out_smallest_edges->getValueAt(i)->getEndNode();
            cout << "Endnode von Edges: " << v->getKey() << endl;
            float alt = dist[stelle_u] + out_smallest_edges->getValueAt(i)->getweight();

            cout << "alt: " << alt << endl;

            //Hier könnte ein Fehler sein!
            for(int k=0; k < nodes->size();k++) {
                if (nodes->getValueAt(k)->getKey() == out_smallest_edges->getValueAt(i)->getEndNode()->getKey()){
                    stelle_v = k;
                    cout << "Stelle des Ednnodes: " << stelle_v << endl;
                    break;
                }
            }

            cout << "Dist_Stelle_Endnode: " << dist[stelle_v] << endl;
            if(alt < dist[stelle_v]){
                 dist[stelle_v] = alt;
                 previous[stelle_v] = smallest_node;
                 root = priorityQueue.decreaseKey(root,v,alt);

            }
        }
    }


    //Suche Stelle vom Endenode in Nodes
    for(int i=0; i < nodes->size();i++){
        if (nodes->getValueAt(i)->getKey() == end)
            stelle_u = i;
    }


    while(previous[stelle_u] != NULL){

         cout << "Edge von: " << previous[stelle_u]->getKey() << endl;

        for(int i=0; i < nodes->size();i++){
            for(int k=0; k < nodes->getValueAt(i)->getEdges()->size();k++){
                if(dist[stelle_u] == nodes->getValueAt(i)->getEdges()->getValueAt(k)->getweight())
                    result->append(nodes->getValueAt(i)->getEdges()->getValueAt(k));
            }
        }


        for(int k=0; k < nodes->size();k++){
            if (nodes->getValueAt(k)->getKey() == previous[stelle_u]->getKey()){
                stelle_u = k;
                break;
            }
        }


    }

    return result;

}
DiGraph::DiGraph() {
    nodes = new Liste<Node*>;
}

DiGraph::~DiGraph() {
    delete[] nodes;
}

void DiGraph::save() {
    fstream f("C:\\Users\\Dennis\\Desktop\\Prak4.txt.txt",ios::out);
    if(!f.is_open()){
        throw "failed to open file!";
    }

    f << "#" << endl;

    for(int i=0; i < nodes->size();i++){
     f << nodes->getValueAt(i)->getKey() << ';' << endl;
    }
    f << "#" << endl;

    for(int i=0; i < nodes->size();i++){
        for(int k=0; k < nodes->getValueAt(i)->getEdges()->size();k++)
            f << nodes->getValueAt(i)->getEdges()->getValueAt(k)->getStartNode()->getKey() <<" "<< nodes->getValueAt(i)->getEdges()->getValueAt(k)->getEndNode()->getKey() <<" "<<  nodes->getValueAt(i)->getEdges()->getValueAt(k)->getweight() << ';' << endl;
    }
    f << "#" << endl;
    f.close();
}

void DiGraph::load() {
    string buff; string output; string nodes; string edges;
    string startnode; string endnode; float weight;

    fstream f("C:\\Users\\Dennis\\Desktop\\Prak4.txt.txt",ios::in);
    if(!f.is_open()){
        cerr << "failed to open file" << endl;
    }
    while(!f.eof()){
        getline(f,buff);
        output.append(buff);
    }

    //output
    Tokenizer tokenizer(output,"#");
    //Nodes
    nodes=tokenizer.nextToken();
    //Edges
    edges=tokenizer.nextToken();


    Tokenizer nodes_token(nodes,";");
    Tokenizer edges_token(edges,";");

    for(int i=0; i < nodes_token.countTokens();i++){
        //Create and Add Node to Graph
        try {
           addNode(new Node(nodes_token.nextToken()));
        }catch(Exception e){
            cout << e.return_error() << endl;
        }

    }

    for(int i=0; i <edges_token.countTokens();i++){
        //Create Edges
        Tokenizer split_edges(edges_token.nextToken()," ");
        startnode=split_edges.nextToken();
        endnode=split_edges.nextToken();
        weight=std::stof(split_edges.nextToken());

        try{
            addEdge(startnode,endnode,weight);
        }catch(Exception e){
            cout << e.return_error() << endl;
        }

    }
    f.close();
}

void DiGraph::addNode(Node *node) {
    nodes->append(node);
}

void DiGraph::addEdge(string key1, string key2, float weight) {
    int node_position=-1,node_position2=-1;
    //suche node key1

    for(int i=0; i < nodes->size();i++){
        if(nodes->getValueAt(i)->getKey() == key1)
            node_position=i;
    }

    if(node_position == -1)
        throw Exception("add: Node von Key1 ist nicht vorhanden!");

    //suche node key2

    for(int i=0; i < nodes->size();i++){

        if(nodes->getValueAt(i)->getKey() == key2)
            node_position2=i;
    }
    if(node_position2 == -1)
        throw Exception("add: Node von Key2 ist nicht vorhanden!");

    //create new Edge
    Edge *new_edge= new Edge;
    new_edge->setWeight(weight);
    new_edge->setStartNode(nodes->getValueAt(node_position));
    new_edge->setEndNode(nodes->getValueAt(node_position2));
    cout << "ctrl" << endl;

    //füge dem Node key1 hinzu
    nodes->getValueAt(node_position)->setNewEdge(new_edge);

}

Liste<Edge*>*DiGraph::getEdges(string key) {
    int node_position=-1;

    for(int i=0; i < nodes->size();i++){
        //Operator[] überladen
        if(nodes->getValueAt(i)->getKey() == key)
            node_position=i;
    }
    if(node_position == -1)
        throw Exception("getEdges: Node von Key ist nicht vorhanden!");

    return nodes->getValueAt(node_position)->getEdges();
}

//in main als Schleife
Liste<Node*> DiGraph::getNeighbours(string key) {
    int node_position=-1;

    for(int i=0; i < nodes->size();i++){
        //Operator[] überladen
        if(nodes->getValueAt(i)->getKey() == key)
            node_position=i;
    }
    if(node_position == -1)
        throw Exception("getNeighbours: Node von Key ist nicht vorhanden!");

    //Alle Edges von Node Key
    //= Operator Überladung
    Liste<Edge*>*all_edges=nodes->getValueAt(node_position)->getEdges();

    //Liste für alle Nachbarn
    Liste<Node*> allNeighbours;
    //füge alle Endenodes in neue Liste von Typ Node * ein
    for(int i=0; i < all_edges->size();i++){
        allNeighbours.append(all_edges[i].getValueAt(i)->getEndNode());
    }

    return allNeighbours;
}

Liste<Node*> *DiGraph::getNodes() {
    return nodes;
}
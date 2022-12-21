
#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H


#include <iostream>
using namespace std;

template <typename T>
struct pqentry{
    float priority;
    T value;
    pqentry*node_left;
    pqentry *node_right;
    int id; // stelle im Array
};

template <typename T>
class PriorityQueue{
private:
    pqentry<T> **_pqentry;
    int _size,_maxID,_elements,_freeIDs_Last;
    int _next_NULL;
    int *_freeIDs;
    T _extract_value;
    void increase();
    bool isfull();
public:
    PriorityQueue(int size);
    ~PriorityQueue();
    pqentry<T>* insert(pqentry<T>*node,T value,float prio);
    pqentry<T>* extractMin(pqentry<T> *node,float key);
    pqentry<T> *smallest_node(pqentry<T> * l);
    pqentry<T>* decreaseKey(pqentry<T> *node,T value, float priority);
    pqentry<T> ** get_entrys();
    T return_extract_value();
    pqentry<T>* remove(pqentry<T> *,T value);
    void search_value(pqentry<T>* node,T value);
    bool isEmpthy();
    void print();
};


template <typename T>
PriorityQueue<T>::PriorityQueue(int size) {
    cout << "size: " << size << endl;
    _size=size;
    _elements=0;
    _maxID=0;
    _next_NULL=0;
    _freeIDs_Last=0;
    _extract_value=NULL;
    _freeIDs=new int[_size];
    _pqentry= new pqentry<T>*[_size];

    for(int i=0; i < _size; i++){
        _pqentry[i] = NULL;
        _freeIDs[i]=-1;
    }
}
template <typename T>
PriorityQueue<T>::~PriorityQueue() {
    delete[] _pqentry;
    delete[] _freeIDs;
}
template <typename T>
bool PriorityQueue<T>::isfull() {
    if(_elements == _size)
        return 1;
    else
        return 0;
}
template <typename T>
bool PriorityQueue<T>::isEmpthy() {
    if(_elements == 0)
        return 1;
    else
        return 0;
}

template <typename T>
void PriorityQueue<T>::increase() {

    pqentry<T> **tmp= new pqentry<T>*[_size*2];
    int *temp = new int[_size*2];

    for(int i=0; i < _size*2;i++) {
        tmp[i] = NULL;
        temp[i] = -1;
    }


    for(int i=0; i < _size;i++){
        tmp[i] = _pqentry[i];
        temp[i] = _freeIDs[i];
    }
    delete[] _pqentry;
    delete[] _freeIDs;
    _pqentry=tmp;
    _freeIDs=temp;
    _size*=2;
    cout << "increased..." << endl;
}

template <typename T>
pqentry<T>** PriorityQueue<T>::get_entrys() {
    return _pqentry;
}

template <typename T>
pqentry<T>* PriorityQueue<T>::insert(pqentry<T> *node,T value,float prio) {
    if(isfull())
        increase();

    //Erstelle neuen Node und gebe die Addresse zurück.
    if(node == NULL){
        pqentry<T> *temp = new pqentry<T>;
        temp->priority=prio;
        temp->value=value;
        temp->node_right=NULL;
        temp->node_left=NULL;
        temp->id=_maxID;

        //Decrease
        if(_next_NULL != NULL && _freeIDs_Last == NULL) {
            int id=_next_NULL;
            _pqentry[_next_NULL] = temp;
            _pqentry[_next_NULL]->id = _next_NULL;
            _next_NULL=NULL;
            _elements++;
            return _pqentry[id];
        }
            //Falls "NULLEN" im Array sind
        else if(_freeIDs_Last != NULL){
            _pqentry[_freeIDs[0]]=temp;
            _pqentry[_freeIDs[0]]->id=_freeIDs[0];

            for(int i=0; i < _freeIDs_Last;i++){
                _freeIDs[i]=_freeIDs[i+1];
            }
            _freeIDs_Last--;
            _elements++;
            return temp;
        }

            //Normal ans Ende
        else {
            _pqentry[_maxID] = temp;
            _maxID++;
            _elements++;
            return temp;
        }

    }
    //das pre Node bekommt dann die Addresse
    if(prio < node->priority)
        node->node_left=PriorityQueue::insert(node->node_left,value,prio);
    else
        node->node_right=PriorityQueue::insert(node->node_right,value,prio);

    return node;
}

template <typename T>
void PriorityQueue<T>::print() {
    for(int i=0; i < _size; i++){
        if(_pqentry[i] != NULL) {
            cout << "Priority: " << _pqentry[i]->priority << " Value: " << _pqentry[i]->value << " ID: " << _pqentry[i]->id << endl;
        }
        else
            cout << "NULL" <<endl;
    }
    cout << "FreeIDsLAST: " << _freeIDs_Last << endl;
    for(int i=0; i <_freeIDs_Last;i++){
        cout << "Element in " << i << ": " <<  _freeIDs[i] << endl;
    }

}

template <typename T>
pqentry<T>* PriorityQueue<T>::smallest_node(pqentry<T>* l) {
    pqentry <T>* current_smallest = l;


    //das kleinste Node befindet sich unten links
    while(current_smallest->node_left != NULL) {
        current_smallest = current_smallest->node_left;
        cout << current_smallest << endl;
    }

    return current_smallest;
}

template <typename T>
pqentry<T>* PriorityQueue<T>::extractMin(pqentry<T> *node,float prio){ //node == root
    if(node == NULL)
        throw "No Elements in Queue";

    //Ruft sich solange auf bis die Bedingung nicht mehr stimmt. Hier wird später ein Child-Node zurückgegeben und an Node-Left oder Node_Right übergeben.
    if(prio < node->priority)
        node->node_left = PriorityQueue::extractMin(node->node_left,prio);
    else if(prio > node->priority)
        node->node_right = PriorityQueue::extractMin(node->node_right,prio);
    else{
        //Wenn Node nur 1 oder 0 Childs hat, lösche Node und gebe das Kind zurück.
        if(node->node_left == NULL){
            pqentry<T> *temp = node->node_right;
            _pqentry[node->id]=NULL;
            _freeIDs[_freeIDs_Last]=node->id;
            _freeIDs_Last++;
            _elements--;
            _extract_value=node->value;
            delete node;
            return temp;
        }
        else if(node->node_right == NULL){
            pqentry<T> *temp= node->node_left;
            _pqentry[node->id]=NULL;
            _freeIDs[_freeIDs_Last]=node->id;
            _freeIDs_Last++;
            _elements--;
            _extract_value=node->value;
            delete node;
            return temp;
        }
        //Wenns 2 Childs hat , suche von der Rechten Wurzel das kleinste Node.
        pqentry<T> *temp = PriorityQueue::smallest_node(node->node_right);
        //cout << "Smallest Node(right-Subtree): " << temp->priority << endl;
        //Kopiere Content
        node->priority=temp->priority;
        //Setze _search , später für decreaseKey() nötig um die gelöschte Stelle (id) zu merken.
        _next_NULL=temp->id;
        //lösche kleinsten Wert von der rechten Wurzel
        node->node_right=PriorityQueue::extractMin(node->node_right,temp->priority);
    }

    return node;
}

template <typename T>
void PriorityQueue<T>::search_value(pqentry<T>*node,T value){
    if(node != NULL) {
        PriorityQueue::search_value(node->node_left, value);
        if(node->value == value) {
            _next_NULL=node->id;
        }
        PriorityQueue::search_value(node->node_right, value);
    }
}
template <typename T>
pqentry<T>* PriorityQueue<T>::decreaseKey(pqentry<T> *node, T value, float priority) {
    //Suche Node mit Value
    PriorityQueue::search_value(node, value);
    //cout << "Search Value:" << _search->value << endl;
    //Lösche Node mit Value
    if(_next_NULL == 0)
        throw "Value nicht vorhanden!";

    node=PriorityQueue::extractMin(node,_pqentry[_next_NULL]->priority);
    //Füge neuen Node mit neuen Werten ein
    node=PriorityQueue::insert(node,value,priority);

    return node;

}

template <typename T>
T PriorityQueue<T>::return_extract_value() {
    return _extract_value;
}

template <typename T>
pqentry<T>* PriorityQueue<T>::remove(pqentry<T> *node,T value) {
    pqentry *root;
    PriorityQueue::search_value(node, value);
    root = PriorityQueue::extractMin(node, _pqentry[_next_NULL]->priority);
    return root;
}

#endif
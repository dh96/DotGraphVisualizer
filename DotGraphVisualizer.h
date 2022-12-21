
#ifndef DOTGRAPHVISUALIZER_H
#define DOTGRAPHVISUALIZER_H

#include <iostream>
#include "DiGraph.h"
#include <cgraph.h>
#include <gvc.h>
#include <string.h>

using namespace std;

class DotGraphVisualizer{
public:
    void visualize(DiGraph *graph);
};

#endif 
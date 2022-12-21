
#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "Node.h"

class Tokenizer {
private:
    unsigned int _pos;
    Liste<string> _tokens;
    Liste<float>_edges_weight;
public:
    Tokenizer(string data,string separators);
    int countTokens();
    string nextToken();
    bool hasMoreTokens();
};

#endif

#include "Tokenizer.h"

Tokenizer::Tokenizer(string data, string separators) {
    _pos = 0;

    string::size_type beg, end;
    beg = data.find_first_not_of(separators, 0);
    end = data.find_first_of(separators, beg);
    while (string::npos != beg || string::npos != end){
        string s = data.substr(beg,end-beg);
        _tokens.append(s);
        beg = data.find_first_not_of(separators, end);
        end = data.find_first_of(separators, beg);
    }

}

int Tokenizer::countTokens() {
    return _tokens.size();
}
string Tokenizer::nextToken() {
    return _tokens.getValueAt(_pos++);
}

bool Tokenizer::hasMoreTokens() {
    return _pos < _tokens.size();
}
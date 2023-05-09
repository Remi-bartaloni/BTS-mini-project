#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "mesures.h"

using namespace std;

class Parser
{



public:
    Parser();

    Mesures extraire(string &trame);

};

#endif // PARSER_H

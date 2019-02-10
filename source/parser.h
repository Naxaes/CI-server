#include "json.hpp"

#ifndef WEBHOOK_PARSER_H
#define WEBHOOK_PARSER_H

//#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class Parser {

    json test;
    json message;

public:
    Parser();

    Parser(string json_message);

    string GetAction();

    string GetPrURL();

    string GrtCloneURL();

    string GetPrTitle();

    string GetPrBody();

    string GetPrTime();

    string GetPrUser();
};

#endif //WEBHOOK_PARSER_H

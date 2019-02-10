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

    //Initialize the parser with a given string
    Parser(string json_message);

    //Return the pull request action(opened, edited, closed, merged, etc.)
    string GetAction();

    //Return URL of the pull request
    string GetPrURL();

    //Return clone URL of the repo
    string GrtCloneURL();

    //Return the title of the pull request
    string GetPrTitle();

    //Return the body of the pull request
    string GetPrBody();

    //Return the time and data that the pull request was created
    string GetPrTime();

    //Return the username of the creator of the pull request
    string GetPrUser();
};

#endif //WEBHOOK_PARSER_H

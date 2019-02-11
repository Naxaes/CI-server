#include "json.hpp"
#include <string>

#ifndef WEBHOOK_PARSER_H
#define WEBHOOK_PARSER_H

using json = nlohmann::json;

class Parser {

    json test;
    json message;

public:
    Parser();

    //Initialize the parser with a given string
    Parser(std::string json_message);

    //Return the pull request action(opened, edited, closed, merged, etc.)
    std::string GetAction();

    //Return URL of the pull request
    std::string GetPrURL();

    //Return clone URL of the repo
    std::string GetCloneURL();

    //Return the title of the pull request
    std::string GetPrTitle();

    //Return the body of the pull request
    std::string GetPrBody();

    //Return the time and data that the pull request was created
    std::string GetPrTime();

    //Return the username of the creator of the pull request
    std::string GetPrUser();

    //Return the commit sha of the given payload
    std::string GetPrSha();
};

#endif //WEBHOOK_PARSER_H

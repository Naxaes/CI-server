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

    Parser(std::string json_message);

    std::string GetAction();

    std::string GetPrURL();

    std::string GetCloneURL();

    std::string GetPrTitle();

    std::string GetPrBody();

    std::string GetPrTime();

    std::string GetPrUser();

    std::string GetPrSha();
};

#endif //WEBHOOK_PARSER_H

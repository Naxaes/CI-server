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

    std::string get_action();

    std::string get_pr_url();

    std::string get_clone_url();

    std::string get_pr_title();

    std::string get_pr_body();

    std::string get_pr_time();

    std::string get_pr_user();

    std::string get_pr_sha();
};

#endif //WEBHOOK_PARSER_H

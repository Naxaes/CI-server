#include "gtest/gtest.h"
#include "../source/parser.cpp"
#include <json.hpp>

using json = nlohmann::json;


// Test file to test the functions in the Parser class

// Help variable
std::string test_string = R"V0G0N(
    {
      "action": "closed",
      "pull_request": {
        "url": "https://api.github.com/repos/Codertocat/Hello-World/pulls/1",
        "title": "Update the README with new information",
        "user": {
          "login": "Codertocat"
        },
        "body": "This is a pretty simple change that we need to pull into master.",
        "created_at": "2018-05-30T20:18:30Z",
        "head": {
          "label": "Codertocat:changes",
          "ref": "changes",
          "sha": "34c5c7793cb3b279e22454cb6750c80560547b3a",
          "repo": {
            "id": 135493233,
            "node_id": "MDEwOlJlcG9zaXRvcnkxMzU0OTMyMzM=",
            "name": "Hello-World",
            "url": "https://api.github.com/repos/Codertocat/Hello-World",
            "created_at": "2018-05-30T20:18:04Z",
            "clone_url": "https://github.com/Codertocat/Hello-World.git",
            "svn_url": "https://github.com/Codertocat/Hello-World"
          }
        }
      }
    })V0G0N";

//Test functions

TEST(Parser, GetAction)
{
    Parser parser(test_string);
    ASSERT_EQ(parser.GetAction(), "closed");
}

TEST(Parser, GetURL)
{
    Parser parser(test_string);
    ASSERT_EQ(parser.GetPrURL(), "https://api.github.com/repos/Codertocat/Hello-World/pulls/1");
}

TEST(Parser, GetCloneURL)
{
    Parser parser(test_string);
    ASSERT_EQ(parser.GetCloneURL(), "https://github.com/Codertocat/Hello-World.git");
}

TEST(Parser, GetTitle)
{
    Parser parser(test_string);
    ASSERT_EQ(parser.GetPrTitle(), "Update the README with new information");
}

TEST(Parser, GetBody)
{
    Parser parser(test_string);
    ASSERT_EQ(parser.GetPrBody(), "This is a pretty simple change that we need to pull into master.");
}

TEST(Parser, GetTime)
{
    Parser parser(test_string);
    ASSERT_EQ(parser.GetPrTime(), "2018-05-30T20:18:30Z");
}

TEST(Parser, GetUser)
{
    Parser parser(test_string);
    ASSERT_EQ(parser.GetPrUser(), "Codertocat");
}

TEST(Parser, GetSHA)
{
    Parser parser(test_string);
    ASSERT_EQ(parser.GetPrSha(), "34c5c7793cb3b279e22454cb6750c80560547b3a");
}
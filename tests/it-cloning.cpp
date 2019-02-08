#include "gtest/gtest.h"
#include "integrationTest.hpp"

/*
*   This test will determine if the cloning part of integration test works as intended
*   The function should be able to determine if the cloning was done correcly and report
*   that. It should also know if something went wrong and report that aswell.
*/


// report cloning(std::string sourceFolder, std::string repo)
TEST(cloning, correctly)
{
    // Folders creatade during testing
    std::string buildFolder = "./temp/build";
    std::string sourceFolder = "./temp/src";
    std::string cacheFolder = "./temp/cache";

    // Create folders
    std::string cmd = "mkdir -p " + buildFolder + " " + sourceFolder + " " + cacheFolder;
    std::string cmd_output = exec(cmd.c_str());


    std::string repo = "git@github.com:Pihlqvist/ci_test.git";

    report r = cloning(sourceFolder, cacheFolder, repo);

    EXPECT_STREQ("Cloning done.", r.message.c_str());
    EXPECT_EQ(0, r.errorcode);

    // Cleanup
    system("rm -rf ./temp");
}



// report cloning(std::string sourceFolder, std::string repo)
TEST(cloning, fatal)
{
    // Folders creatade during testing
    std::string buildFolder = "./temp/build";
    std::string sourceFolder = "./temp/src";
    std::string cacheFolder = "./temp/cache";

    // Create folders
    std::string cmd = "mkdir -p " + buildFolder + " " + sourceFolder + " " + cacheFolder;
    std::string cmd_output = exec(cmd.c_str());


    std::string repo = "git@github.com:Pihlqvist/ci_test_WRONG.git";

    report r = cloning(sourceFolder, cacheFolder, repo);

    EXPECT_STREQ("Fatal error while cloning.", r.message.c_str());
    EXPECT_EQ(2, r.errorcode);

    // Cleanup
    system("rm -rf ./temp");
}
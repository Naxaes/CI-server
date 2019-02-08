#ifndef INCLUDE_INTEGRATIONTEST_H_
#define INCLUDE_INTEGRATIONTEST_H_

#include <cstdio>
#include <stdio.h>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>


/*
*   This file is indentent to hold the function that conducts the test of the commit
*   
*
*/

struct report
{ 
    int errorcode;          // 0 -> good, 1 > -> bad
    std::string message;    // message for more info
};

// Performes a system call and returns the output as a string
std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}


// Clone the current repo into a selected folder
report cloning(std::string sourceFolder, std::string cacheFolder, std::string repo)
{
    // Clone the repo and save the output to a cache
    std::string cmd = "git clone --progress " + repo + " " + sourceFolder + " 2>  " + cacheFolder + "/git_clone_cache.txt";
    system(cmd.c_str());

    // Get the info from the cach into the method
    cmd = "cat " + cacheFolder + "/git_clone_cache.txt";
    std::string cmd_output = exec(cmd.c_str());

    // Determine if the cloning went alright
    report rep;
    if (cmd_output.find("Checking connectivity... done.") != std::string::npos)
    {
        rep.message = "Cloning done.";
        rep.errorcode = 0;
    }
    else if (cmd_output.find("fatal:") != std::string::npos)
    {
        rep.message = "Fatal error while cloning.";
        rep.errorcode = 1;
    }
    else
    {
        rep.message = "Unknown error while cloning.";
        rep.errorcode = 1;
    }

    return rep;
}

// Checkout the given 'commit'
report checkout(std::string sourceFolder, std::string cacheFolder, std::string commit)
{
    // Checkout commit and save output to cache
    std::string cmd = "git --git-dir " + sourceFolder + "/.git checkout " + commit + " 2>  " + cacheFolder + "/git_checkout_cache.txt";
    std::string cmd_output = exec(cmd.c_str());

    // Get the info from the cach into the method
    cmd = "cat " + cacheFolder + "/git_checkout_cache.txt";
    cmd_output = exec(cmd.c_str());

    // TODO(fredrik): the find should determine the commit id
    report rep;
    if (cmd_output.find("HEAD is now at") != std::string::npos)
    {
        rep.message = "We could set HEAD to commit.";
        rep.errorcode = 0;
    }
    else
    {
        rep.message = "Unknown Error while git checkout";
        rep.errorcode = 2;
    }

    return rep;
}


// Merge to the target branch and determine if it could be done
report merge(std::string sourceFolder, std::string targetBranch)
{
    // Performe merge and take output
    std::string cmd = "git --git-dir " + sourceFolder + "/.git merge " + targetBranch;
    std::string cmd_output = exec(cmd.c_str());

    report rep;
    if (cmd_output.find("Already up-to-date.") != std::string::npos)
    {
        rep.message = "Merge went fine.";
        rep.errorcode = 0;
    }
    else
    {
        rep.message = "Unkown error in merge";
        rep.errorcode = 3;
    }

    return rep;
}

// Determine if CMake could compile the code
report compileCMake(std::string sourceFolder, std::string buildFolder)
{
    // Performe cmake
    std::string cmd = "cmake -B" + buildFolder + " -H" + sourceFolder;
    std::string cmd_output = exec(cmd.c_str());

    //std::cerr << cmd_output; // USED IN DEBUGGING
    report rep;
    if (cmd_output.find("Generating done") != std::string::npos)
    {
        rep.message = "CMake compiled fine.";
        rep.errorcode = 0;
    }
    else 
    {
        rep.message = "CMake din't compile.";
        rep.errorcode = 4;
    }

    return rep;
}

// Compile with the make file cretade by CMake in prev step
report compileMake(std::string buildFolder)
{
    std::string cmd = "make -C " + buildFolder;
    std::string cmd_output = exec(cmd.c_str());    

    report rep;
    if (cmd_output.find("100%") != std::string::npos)
    {
        rep.message = "Make compiled fine.";
        rep.errorcode = 0;
    }
    else 
    {
        rep.message = "Make din't compile.";
        rep.errorcode = 5;
    }

    return rep;
}

// Run unittests in build folder
report runUnittest(std::string buildFolder)
{
    std::string cmd = buildFolder + "/unittest"; 
    std::string cmd_output = exec(cmd.c_str());

    report rep;
    if (cmd_output.find("PASSED") != std::string::npos)
    {
        rep.message = "Passed all unittests.";
        rep.errorcode = 0;
    }
    else 
    {
        rep.message = "Failed unittests.";
        rep.errorcode = 6;
    }
    
    return rep;
}

report integrationTest(std::string commit, std::string repo, std::string targetBranch)
{
    // Folders creatade during testing
    std::string buildFolder = "./temp/build";
    std::string sourceFolder = "./temp/src";
    std::string cacheFolder = "./temp/cache";

    // Create folders
    std::string cmd = "mkdir -p " + buildFolder + " " + sourceFolder + " " + cacheFolder;
    std::string cmd_output = exec(cmd.c_str());

    std::array<report, 6> reports;

    // Clone the repo into 'sourceFolder'
    reports[0] = cloning(sourceFolder, cacheFolder, repo);
    if (reports[0].errorcode != 0)
    {
        // something is not correct
        std::cerr << "cloning fail\n";
        exec("rm -rf ./temp");
        return reports[0];
    }

    // Checkout the given 'commit'
    reports[1] = checkout(sourceFolder, cacheFolder, commit);
    if (reports[1].errorcode != 0)
    {
        // something is not correct
        std::cerr << "checkout fail\n";
        exec("rm -rf ./temp");
        return reports[1];
    }

    // Performe a merge into 'targetBranch' to see if it can be done without issue
    reports[2] = merge(sourceFolder, targetBranch);
    if (reports[2].errorcode != 0)
    {
        // something is not correct
        std::cerr << "merge fail\n";
        exec("rm -rf ./temp");
        return reports[2];
    }    

    // Compile the code with 'CMake'
    reports[3] = compileCMake(sourceFolder, buildFolder);
    if (reports[3].errorcode != 0)
    {
        // something is not correct
        std::cerr << "compileCMake fail\n";
        exec("rm -rf ./temp");
        return reports[3];
    }

    // Comple the code with 'make'
    reports[4] = compileMake(buildFolder);
    if (reports[4].errorcode != 0)
    {
        // something is not correct
        std::cerr << "compileMake fail\n";
        exec("rm -rf ./temp");
        return reports[4];
    }

    // Performe unittest
    reports[5] = runUnittest(buildFolder);
    if (reports[5].errorcode != 0)
    {
        // something is not correct
        std::cerr << "runUnittest fail\n";
        exec("rm -rf ./temp");
        return reports[5];
    }

    // Cleanup
    exec("rm -rf ./temp");


    // Report results
    report rep;
    rep.message = "Everthing is good.";
    rep.errorcode = 0;

    return rep;
}


#endif  // INCLUDE_INTEGRATIONTEST_H_
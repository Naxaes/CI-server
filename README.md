# CI-server

## Summary
This is an implementation of a small continuous integration CI-server that automatically tests code. The server is connected to a GitHub repository 
through a webhook, and whenever a pull request is made, the server runs the tests and notifies the user of the results on the pull request page.

## License
This project is licensed under the MIT License - see the LICENSE.md file for details.

## Prerequisites
The project requires CMake (version 3.2 or higher), C++ (14 or higher) and ngrok.

## Naming conventions
We will use [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html) for the code, and 
[this Git Style Guide](https://github.com/agis/git-style-guide) for commit messages.

## Compiling

This is one way to compile the project on a linux/debian based machine while in the project dir.

First running cmake to construct a Makefile
```
ci_test$ cmake -B./build -H.
```
Secondly run the make file to create executables
```
ci_test$ make -C ./build
```
There are now executables in the build folder one of them should be unittest, example of a executable being ran.
```
ci_test$ ./build/unittest
```

## How to use the project
After compiling, you'll have an executable of the project. To get it actively running in your GitHub repository, here's the steps you need to take.

#### 1. Run the executable
The executable is the actual CI-server. When it runs it will wait for incomming connections. You run it by typing the following in the terminal:
```
/build/WebHook
```

#### 2. Run ngrok
ngrok is a simple program that creates a temporary connection between the internet and your local machine. You can run ngrok by typing the following in the terminal:
```
/resources/ngrok http 8080
```
#### 3. Add the public link to GitHub
When running ngrok, you'll get two links for _"Forwarding"_, which will look somehing like this _"https://b650839b.ngrok.io"_. Copy the link that starts with _"https"_ and go to your project at github.com. Under the tab settings, there's a tab called Webhooks. There you have the ability to _"Add webhook"_. From here, set the following settings:
* Payload URL: https://b650839b.ngrok.io (or whatever your temporary link you got)
* Content type: application/json
* Which events would you like to trigger this webhook? Just the push event.

And then press _"Add webhook"_.

Now you should be up and running with an active CI-server!

## Running test
To make sure the project is in a working state, you can run the tests. If you've successfully compiled the project, you can run the tests by running the executable "unittest".
```
/build/unittest
```

## Contributions

### Emma Good
* Created the JSON parser class that extracts data from the HTTP payload.

### Ted Klein Bergman
* Owner of the repository.
* Created structure template.
* Created the server.

### Fredrik Pilhqvist
* Created integrationTest function that compiles and tests a commit.
* Documented compiling.
* Testing server

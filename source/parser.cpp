#include "parser.h"
#include <iostream>
#include <string>

using json = nlohmann::json;


    json test = R"({
      "action": "closed",
      "number": 1,
      "pull_request": {
        "url": "https://api.github.com/repos/Codertocat/Hello-World/pulls/1",
        "id": 191568743,
        "node_id": "MDExOlB1bGxSZXF1ZXN0MTkxNTY4NzQz",
        "html_url": "https://github.com/Codertocat/Hello-World/pull/1",
        "diff_url": "https://github.com/Codertocat/Hello-World/pull/1.diff",
        "patch_url": "https://github.com/Codertocat/Hello-World/pull/1.patch",
        "issue_url": "https://api.github.com/repos/Codertocat/Hello-World/issues/1",
        "number": 1,
        "state": "closed",
        "locked": false,
        "title": "Update the README with new information",
        "user": {
          "login": "Codertocat",
          "id": 21031067,
          "node_id": "MDQ6VXNlcjIxMDMxMDY3"
        },
        "body": "This is a pretty simple change that we need to pull into master.",
        "created_at": "2018-05-30T20:18:30Z",
        "updated_at": "2018-05-30T20:18:50Z",
        "closed_at": "2018-05-30T20:18:50Z",
        "merged_at": null,
        "merge_commit_sha": "414cb0069601a32b00bd122a2380cd283626a8e5",
        "assignee": null,
        "milestone": null,
        "commits_url": "https://api.github.com/repos/Codertocat/Hello-World/pulls/1/commits",
        "head": {
          "label": "Codertocat:changes",
          "ref": "changes",
          "sha": "34c5c7793cb3b279e22454cb6750c80560547b3a",
          "user": {
            "login": "Codertocat",
            "id": 21031067,
            "node_id": "MDQ6VXNlcjIxMDMxMDY3"
          },
          "repo": {
            "id": 135493233,
            "node_id": "MDEwOlJlcG9zaXRvcnkxMzU0OTMyMzM=",
            "name": "Hello-World",
            "full_name": "Codertocat/Hello-World",
            "owner": {
              "login": "Codertocat",
              "id": 21031067,
              "node_id": "MDQ6VXNlcjIxMDMxMDY3"
            },
            "private": false,
            "html_url": "https://github.com/Codertocat/Hello-World",
            "description": null,
            "fork": false,
            "url": "https://api.github.com/repos/Codertocat/Hello-World",
            "created_at": "2018-05-30T20:18:04Z",
            "updated_at": "2018-05-30T20:18:50Z",
            "pushed_at": "2018-05-30T20:18:48Z",
            "git_url": "git://github.com/Codertocat/Hello-World.git",
            "ssh_url": "git@github.com:Codertocat/Hello-World.git",
            "clone_url": "https://github.com/Codertocat/Hello-World.git",
            "svn_url": "https://github.com/Codertocat/Hello-World",
            "homepage": null,
            "size": 0,
            "archived": false,
            "open_issues_count": 1,
            "license": null,
            "forks": 0,
            "open_issues": 1,
            "watchers": 0,
            "default_branch": "master"
          }
        },
        "base": {
          "label": "Codertocat:master",
          "ref": "master",
          "sha": "a10867b14bb761a232cd80139fbd4c0d33264240",
          "user": {
            "login": "Codertocat",
            "id": 21031067,
            "node_id": "MDQ6VXNlcjIxMDMxMDY3"
          },
          "repo": {
            "id": 135493233,
            "node_id": "MDEwOlJlcG9zaXRvcnkxMzU0OTMyMzM=",
            "name": "Hello-World",
            "full_name": "Codertocat/Hello-World",
            "owner": {
              "login": "Codertocat",
              "id": 21031067,
              "node_id": "MDQ6VXNlcjIxMDMxMDY3"
            },
            "private": false,
            "html_url": "https://github.com/Codertocat/Hello-World",
            "description": null,
            "fork": false,
            "url": "https://api.github.com/repos/Codertocat/Hello-World",
            "created_at": "2018-05-30T20:18:04Z",
            "updated_at": "2018-05-30T20:18:50Z",
            "pushed_at": "2018-05-30T20:18:48Z",
            "git_url": "git://github.com/Codertocat/Hello-World.git",
            "ssh_url": "git@github.com:Codertocat/Hello-World.git",
            "clone_url": "https://github.com/Codertocat/Hello-World.git",
            "svn_url": "https://github.com/Codertocat/Hello-World",
            "homepage": null,
            "size": 0,
            "archived": false,
            "open_issues_count": 1,
            "license": null,
            "forks": 0,
            "open_issues": 1,
            "watchers": 0,
            "default_branch": "master"
          }
        },
        "_links": {
          "self": {
            "href": "https://api.github.com/repos/Codertocat/Hello-World/pulls/1"
          },
          "html": {
            "href": "https://github.com/Codertocat/Hello-World/pull/1"
          },
          "issue": {
            "href": "https://api.github.com/repos/Codertocat/Hello-World/issues/1"
          },
          "comments": {
            "href": "https://api.github.com/repos/Codertocat/Hello-World/issues/1/comments"
          },
          "review_comments": {
            "href": "https://api.github.com/repos/Codertocat/Hello-World/pulls/1/comments"
          },
          "review_comment": {
            "href": "https://api.github.com/repos/Codertocat/Hello-World/pulls/comments{/number}"
          },
          "commits": {
            "href": "https://api.github.com/repos/Codertocat/Hello-World/pulls/1/commits"
          },
          "statuses": {
            "href": "https://api.github.com/repos/Codertocat/Hello-World/statuses/34c5c7793cb3b279e22454cb6750c80560547b3a"
          }
        },
        "author_association": "OWNER",
        "merged": false,
        "mergeable": true,
        "rebaseable": true,
        "mergeable_state": "clean",
        "merged_by": null,
        "comments": 0,
        "review_comments": 1,
        "maintainer_can_modify": false,
        "commits": 1,
        "additions": 1,
        "deletions": 1,
        "changed_files": 1
      },
      "repository": {
        "id": 135493233,
        "node_id": "MDEwOlJlcG9zaXRvcnkxMzU0OTMyMzM=",
        "name": "Hello-World",
        "full_name": "Codertocat/Hello-World",
        "owner": {
          "login": "Codertocat",
          "id": 21031067,
          "node_id": "MDQ6VXNlcjIxMDMxMDY3"
        },
        "private": false,
        "html_url": "https://github.com/Codertocat/Hello-World",
        "description": null,
        "fork": false,
        "url": "https://api.github.com/repos/Codertocat/Hello-World",
        "created_at": "2018-05-30T20:18:04Z",
        "updated_at": "2018-05-30T20:18:50Z",
        "pushed_at": "2018-05-30T20:18:48Z",
        "git_url": "git://github.com/Codertocat/Hello-World.git",
        "ssh_url": "git@github.com:Codertocat/Hello-World.git",
        "clone_url": "https://github.com/Codertocat/Hello-World.git",
        "svn_url": "https://github.com/Codertocat/Hello-World",
        "homepage": null,
        "size": 0,
        "archived": false,
        "open_issues_count": 1,
        "license": null,
        "forks": 0,
        "open_issues": 1,
        "watchers": 0,
        "default_branch": "master"
      },
      "sender": {
        "login": "Codertocat",
        "id": 21031067,
        "node_id": "MDQ6VXNlcjIxMDMxMDY3"
      }
    })"_json;

    json message;

    // Initialize with test JSON
    Parser::Parser(){
        this->message = test;
    }
    // Initialize with a given string
    Parser::Parser(std::string json_message){
        this->message = json::parse(json_message);
    }

    // Return the pull request action (opened, edited, closed, merged, etc)
    std::string Parser::get_action(){
        return this->message["action"];
    }

    // Returns the url of the pull request
    std::string Parser::get_pr_url(){
        return this->message["pull_request"]["url"];
    }

    // Returns the clone url of the repo
    std::string Parser::get_clone_url(){
        return this->message["pull_request"]["head"]["repo"]["clone_url"];
    }

    // Returns the title of the pull request
    std::string Parser::get_pr_title(){
        return this->message["pull_request"]["title"];
    }

    // Returns the body of the pull request
    std::string Parser::get_pr_body(){
        return this->message["pull_request"]["body"];
    }

    // Returns the time and date that the pull request was created
    std::string Parser::get_pr_time(){
        return this->message["pull_request"]["created_at"];
    }

    // Returns the username of the creator of the pull request
    std::string Parser::get_pr_user(){
        return this->message["pull_request"]["user"]["login"];
    }

    // Returns the sha of the pull request
    std::string Parser::get_pr_sha(){
        return this->message["pull_request"]["head"]["sha"];
    }

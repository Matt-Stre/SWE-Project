//
// Created by Aiden Zepp on 2024-03-18.
//

#include "Server.h"

// std...
#include <fstream>
#include <sstream>

// src...
#include "Status.h"

// lib...
#include "json/single_include/nlohmann/json.hpp"
using json = nlohmann::json;

namespace http {
    //
    // --- PUBLIC ---
    //

    //
    // Constructors / Destructors
    //

    Server::Server() {
        db = db::Database("src/backend/Database.csv");
    }

    Server::~Server() = default;

    //
    // Methods
    //

    void Server::init() {
        // -----------------------------------
        // ENDPOINT: FIXME (REMOVE) "/ex"
        // -----------------------------------
        Get("/ex", [](const httplib::Request& req, httplib::Response& res) {
            // Send back HTML.
            std::ifstream file("src/frontend/ex/index.html");
            if (!file.is_open()) {
                res.status = http::Status::InternalServerError;
                res.set_content("Could not find file to serve.", "text/plain");
                return;
            }
            std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

            res.status = http::Status::Ok;
            res.set_content(content, "text/html");
        });

        // -----------------------------------
        // ENDPOINT: "/"
        // -----------------------------------
        Get("/", [](const httplib::Request& _, httplib::Response& res) {
            res.status = http::Status::Ok;
            res.set_content("Hello, World!", "text/plain");
        });
        Post("/", [](const httplib::Request& req, httplib::Response& res) {
            try {
                auto json = json::parse(req.body);
                json["status"] = http::Status::Ok;

                res.set_content(json.dump(), "application/json");
            } catch (const json::parse_error& _) {
                res.status = http::Status::BadRequest;
                res.set_content("Bad JSON format", "text/plain");
            }
        });

        // -----------------------------------
        // ENDPOINT: "/app/<username>"
        // -----------------------------------
        Get(R"(/app/([^/]+)/preferences)", [](const httplib::Request& req, httplib::Response& res) {
            // Extract the username from the request, which is captured by the first "([^/]+)" regex in the URL pattern.
            std::string _ = req.matches[1];

            // Send back HTML.
            std::ifstream file("src/frontend/username/preferences/index.html");
            if (!file.is_open()) {
                res.status = http::Status::InternalServerError;
                res.set_content("Could not find file to serve.", "text/plain");
                return;
            }
            std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

            res.status = http::Status::Ok;
            res.set_content(content, "text/html");
        });
        Get(R"(/app/([^/]+)/opportunities)", [](const httplib::Request& req, httplib::Response& res) {
            // Extract the username from the request, which is captured by the first "([^/]+)" regex in the URL pattern.
            std::string _ = req.matches[1];

            // Send back HTML.
            std::ifstream file("src/frontend/username/opportunities/index.html");
            if (!file.is_open()) {
                res.status = http::Status::InternalServerError;
                res.set_content("Could not find file to serve.", "text/plain");
                return;
            }
            std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

            res.status = http::Status::Ok;
            res.set_content(content, "text/html");
        });

        // -----------------------------------
        // ENDPOINT: "/api/users"
        // -----------------------------------
        Get("/api/users", [&](const httplib::Request& req, httplib::Response& res) {
           json response = db.users;
           res.status = http::Status::Ok;
           res.set_content(response.dump(), "application/json");
        });
        Post("/api/users", [&](const httplib::Request& req, httplib::Response& res) {
            json response;

            try {
                auto json = json::parse(req.body);
                std::string username = json["username"];
                std::string password = json["password"];

                auto it = std::find_if(db.users.begin(), db.users.end(), [&username](const db::User& user) -> bool {
                   return user.username == username;
                });
                if (it != db.users.end()) {
                    it->password = password;
                } else {
                    db.users.emplace_back(username, password);
                }

                res.status = http::Status::Ok;
                response["username"] = username;
                response["password"] = password;
            } catch (const json::exception& e) {
                res.status = http::Status::BadRequest;
                response["error"] = e.what();
            }

            res.set_content(response.dump(), "application/json");
        });

        // -----------------------------------
        // ENDPOINT: "/api/users/auth"
        // -----------------------------------
        Post("/api/users/auth", [&](const httplib::Request& req, httplib::Response& res) {
            json response;

            try {
                auto json = json::parse(req.body);
                std::string username = json["username"];
                std::string password = json["password"];
                bool verified = false;

                auto it = std::find_if(db.users.begin(), db.users.end(), [&username, &password](const db::User& user) -> bool {
                    return user.username == username && user.password == password;
                });
                if (it != db.users.end()) {
                    verified = true;
                }

                res.status = http::Status::Ok;
                response["verified"] = verified;
            } catch (const json::exception& e) {
                res.status = http::Status::BadRequest;
                response["error"] = e.what();
            }

            res.set_content(response.dump(), "application/json");
        });

        // -----------------------------------
        // ENDPOINT: "/api/preferences"
        // -----------------------------------
        Get(R"(/api/preferences/([^/]+))", [](const httplib::Request& req, httplib::Response& res) {
            // FIXME (remove): This sends pseudo-JSON.
            json obj;
            obj["username"] = req.matches[1];
            obj["password"] = "password12345";
            obj["preferences"] = {
                    {"1", "Example Preference A", "(000)-000-0000"},
                    {"2", "Example Preference B", "(000)-000-0000"},
                    {"3", "Example Preference C", "(000)-000-0000"},
            };

            res.status = http::Status::Ok;
            res.set_content(obj.dump(), "application/json");
        });

        // -----------------------------------
        // ENDPOINT: "/api/opportunities"
        // -----------------------------------
        Get("/api/opportunities", [&](const httplib::Request& req, httplib::Response& res) {
            json response = db.opportunities;
            res.status = http::Status::Ok;
            res.set_content(response.dump(), "application/json");
        });
        Put("/api/opportunities", [&](const httplib::Request& req, httplib::Response& res) {
            try {
                auto json = json::parse(req.body);

                // Store data fields.
                std::string name = json["name"];
                std::string pnum = json["phoneNumber"];
                std::string desc = json["description"];
                std::vector<std::string> keys = json["keywords"];
                db.opportunities.emplace_back(name, pnum, desc, keys);

                res.status = http::Status::Ok;
            } catch (const json::parse_error& _) {
                res.status = http::Status::BadRequest;
                res.set_content("Bad JSON format", "text/plain");
            }
        });
    }

    bool Server::listen() {
        return static_cast<httplib::Server*>(this)->listen("127.0.0.1", 8080);
    }
} // http

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
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace http {
    //
    // --- PUBLIC ---
    //

    //
    // Constructors / Destructors
    //

    Server::Server() {
        db = csv::parse("src/backend/Database.csv");
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
            json obj = db;

            res.status = http::Status::Ok;
            res.set_content(obj.dump(), "application/json");
        });
    }

    bool Server::listen() {
        return static_cast<httplib::Server*>(this)->listen("127.0.0.1", 8080);
    }
} // http

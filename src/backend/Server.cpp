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
        // ENDPOINT: "/app"
        // -----------------------------------
        /*
         * Serve the login page.
         */
        Get("/app/login", [](const httplib::Request& req, httplib::Response& res) {
            // Send back HTML.
            std::ifstream file("src/frontend/login.html");
            if (!file.is_open()) {
                res.status = http::Status::InternalServerError;
                res.set_content("Could not find file to serve.", "text/plain");
                return;
            }
            std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

            res.status = http::Status::Ok;
            res.set_content(content, "text/html");
        });
        /*
         * Serve the signup page.
         */
        Get("/app/signup", [](const httplib::Request& req, httplib::Response& res) {
            // Send back HTML.
            std::ifstream file("src/frontend/signup.html");
            if (!file.is_open()) {
                res.status = http::Status::InternalServerError;
                res.set_content("Could not find file to serve.", "text/plain");
                return;
            }
            std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

            res.status = http::Status::Ok;
            res.set_content(content, "text/html");
        });
        /*
         * Serve the opportunities page.
         */
        Get("/app/opportunities", [](const httplib::Request& req, httplib::Response& res) {
            // Send back HTML.
            std::ifstream file("src/frontend/opportunities.html");
            if (!file.is_open()) {
                res.status = http::Status::InternalServerError;
                res.set_content("Could not find file to serve.", "text/plain");
                return;
            }
            std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

            res.status = http::Status::Ok;
            res.set_content(content, "text/html");
        });
        /*
         * Serve the profile page.
         */
        Get("/app/profile", [](const httplib::Request& req, httplib::Response& res) {
            // Send back HTML.
            std::ifstream file("src/frontend/profile.html");
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
        // ENDPOINT: "/app/<username>"
        // -----------------------------------
        /*
         * Respond with the preferences associated with the provided user information.
         */
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

        // -----------------------------------
        // ENDPOINT: "/api/users"
        // -----------------------------------
        /*
         * Respond with all users currently stored.
         */
        Get("/api/users", [&](const httplib::Request& req, httplib::Response& res) {
           json response = db.users;
           res.status = http::Status::Ok;
           res.set_content(response.dump(), "application/json");
        });
        /*
         * Save a user to the database.
         */
        Post("/api/users", [&](const httplib::Request& req, httplib::Response& res) {
            json response;

            try {
                auto json = json::parse(req.body);
                std::string username = json["username"];
                std::string password = json["password"];
                std::string email = json["email"];
                std::string bio = "";

                // The bio field may not be found; if not, don't use anything.
                if (json.contains("bio")) {
                    bio = json["bio"];
                }

                // Find the user. If found, store their new information; if not, add them to the database.
                auto it = std::find_if(db.users.begin(), db.users.end(), [&username](const db::User& user) -> bool {
                   return user.username == username;
                });
                if (it != db.users.end()) {
                    it->password = password;
                    it->email = email;

                    // If there was no bio JSON field, don't add/change anything about the user's bio information.
                    if (it->bio.empty()) {
                        bio = bio;
                    }
                } else {
                    db.users.emplace_back(username, password, email, bio);
                }

                // Return back the information given for ease-of-use.
                res.status = http::Status::Ok;
                response["username"] = username;
                response["password"] = password;
                response["email"] = email;
                response["bio"] = bio;
            } catch (const json::exception& e) {
                // Return back the error status encountered.
                res.status = http::Status::BadRequest;
                response["error"] = e.what();
            }

            res.set_content(response.dump(), "application/json");
        });

        // -----------------------------------
        // ENDPOINT: "/api/users/auth"
        // -----------------------------------
        /*
         * Verify that the user's information matches a user's information stored in the database.
         */
        Post("/api/users/auth", [&](const httplib::Request& req, httplib::Response& res) {
            json response;

            try {
                auto json = json::parse(req.body);
                std::string username = json["username"];
                std::string password = json["password"];
                bool verified = false;

                // Find the user. If found, store that they've been found.
                auto it = std::find_if(db.users.begin(), db.users.end(), [&username, &password](const db::User& user) -> bool {
                    return user.username == username && user.password == password;
                });
                if (it != db.users.end()) {
                    verified = true;
                }

                res.status = http::Status::Ok;
                response["verified"] = verified;
            } catch (const json::exception& e) {
                // Return back the error status encountered.
                res.status = http::Status::BadRequest;
                response["error"] = e.what();
            }

            res.set_content(response.dump(), "application/json");
        });

        // -----------------------------------
        // ENDPOINT: "/api/opportunities"
        // -----------------------------------
        /*
         * Respond with all opportunities in the database.
         */
        Get("/api/opportunities", [&](const httplib::Request& req, httplib::Response& res) {
            json response = db.opportunities;
            res.status = http::Status::Ok;
            res.set_content(response.dump(), "application/json");
        });
        /*
         * Add a new opportunity to the database.
         */
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
                // Return back the error status encountered.
                res.status = http::Status::BadRequest;
                res.set_content("Bad JSON format", "text/plain");
            }
        });
    }

    bool Server::listen() {
        return static_cast<httplib::Server*>(this)->listen("127.0.0.1", 8080);
    }
} // http

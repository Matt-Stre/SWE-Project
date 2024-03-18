//
// Created by Aiden Zepp on 2024-03-18.
//

#include "Server.h"

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

    Server::Server() = default;

    Server::~Server() = default;

    //
    // Methods
    //

    void Server::init() {
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
    }

    bool Server::listen() {
        return static_cast<httplib::Server*>(this)->listen("127.0.0.1", 8080);
    }

} // http
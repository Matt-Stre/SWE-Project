//
// Created by Aiden Zepp on 2024-03-18.
//

#ifndef SWE_PROJECT_SERVER_H
#define SWE_PROJECT_SERVER_H

// src...
#include "Database.h"

// lib...
#include "httplib/httplib.h"

namespace http {

    class Server : private httplib::Server {
    public:
        //
        // Constructors / Destructors
        //

        Server();
        ~Server();

        //
        // Methods
        //

        /*
         * Start up the server, initializing all route endpoints.
         */
        void init();

        /*
         * Run the server, listening on address 'http://127.0.0.1' and port '8080'.
         */
        bool listen();

    private:
        db::Database db;
    };

} // http

#endif //SWE_PROJECT_SERVER_H

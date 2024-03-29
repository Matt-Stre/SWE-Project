//
// Created by Aiden Zepp on 2024-03-18.
//

#ifndef SWE_PROJECT_SERVER_H
#define SWE_PROJECT_SERVER_H

// src...
#include "Database.h"

// lib...
#include <httplib/httplib.h>

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

        void init();

        bool listen();

    private:
        db::Database db;
    };

} // http

#endif //SWE_PROJECT_SERVER_H

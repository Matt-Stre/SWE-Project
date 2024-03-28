//
// Created by Aiden Zepp on 2024-03-18.
//

#ifndef SWE_PROJECT_SERVER_H
#define SWE_PROJECT_SERVER_H

// src...
#include "CSV.h"

// lib...
#include <cpp-httplib/httplib.h>

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
        csv::Data db;
    };

} // http

#endif //SWE_PROJECT_SERVER_H

//
// Created by Aiden Zepp on 2024-03-18.
//

#ifndef SWE_PROJECT_SERVER_H
#define SWE_PROJECT_SERVER_H

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
    };

} // http

#endif //SWE_PROJECT_SERVER_H

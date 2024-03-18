//
// Created by Aiden Zepp on 2024-03-17.
//

#include "Server.h"

int main() {
    http::Server server;
    server.init();
    server.listen();
    return 0;
}

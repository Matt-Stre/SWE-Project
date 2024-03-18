//
// Created by Aiden Zepp on 2024-03-18.
//

#ifndef SWE_PROJECT_STATUS_H
#define SWE_PROJECT_STATUS_H

namespace http {
    enum Status : int {
        Ok = 200,
        Created = 201,
        Accepted = 202,

        BadRequest = 400,
        Unauthorized = 401,
        Forbidden = 403,
        NotFound = 404,

        InternalServerError = 500,
        NotImplemented = 501,
    };
} // http

#endif //SWE_PROJECT_STATUS_H

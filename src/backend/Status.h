//
// Created by Aiden Zepp on 2024-03-18.
//

#ifndef SWE_PROJECT_STATUS_H
#define SWE_PROJECT_STATUS_H

namespace http {
    enum Status : int {
        //
        // 200+
        //
        Ok = 200,
        Created = 201,

        //
        // 400+
        //
        BadRequest = 400,

        //
        // 500+
        //
        InternalServerError = 500,
    };
} // http

#endif //SWE_PROJECT_STATUS_H

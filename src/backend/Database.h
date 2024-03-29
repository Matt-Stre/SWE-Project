//
// Created by Aiden Zepp on 2024-03-29.
//

#ifndef SWE_PROJECT_DATABASE_H
#define SWE_PROJECT_DATABASE_H

// std...
#include <string>

// src...
#include "Opportunity.h"

namespace db {
    struct Database {
        //
        // Properties
        //

        Opportunities opportunities;

        //
        // Constructors / Destructors
        //

        Database();

        Database(const std::string& filepath);

        //
        // Methods
        //

        Opportunities filter(const std::string& keyword);

        Opportunities filter(const std::vector<std::string>& keywords);

    private:
        //
        // Static Methods
        //

        static std::string trim(const std::string& str);

        static std::vector<std::string> split(const std::string& str, char delimiter);
    };
} // db

#endif //SWE_PROJECT_DATABASE_H

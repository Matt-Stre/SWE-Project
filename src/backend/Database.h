//
// Created by Aiden Zepp on 2024-03-29.
//

#ifndef SWE_PROJECT_DATABASE_H
#define SWE_PROJECT_DATABASE_H

// std...
#include <string>

// src...
#include "Opportunity.h"
#include "User.h"

namespace db {
    struct Database {
        //
        // Properties
        //

        Opportunities opportunities = Opportunities();

        Users users = Users();

        //
        // Constructors / Destructors
        //

        Database() = default;

        Database(const std::string& filepath);

        //
        // Methods
        //

        /*
         * Find all opportunities associated with a given keyword.
         */
        Opportunities filter(const std::string& keyword);

        /*
         * Find all opportunities associated with a given set of keywords.
         */
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

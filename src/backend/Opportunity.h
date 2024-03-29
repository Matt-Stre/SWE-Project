//
// Created by Aiden Zepp on 2024-03-29.
//

#ifndef SWE_PROJECT_OPPORTUNITY_H
#define SWE_PROJECT_OPPORTUNITY_H

// std...
#include <string>
#include <vector>

namespace db {
    //
    // Typedefs
    //

    struct Opportunity {
        //
        // Properties
        //

        std::string name;
        std::string phone_number;
        std::string description;
        std::vector<std::string> keywords;

        //
        // Constructors / Destructors
        //

        Opportunity(std::string name, std::string phone_number, std::string description, std::vector<std::string> keywords);

        //
        // Methods
        //

        bool has(const std::string& keyword) const;

        bool has(const std::vector<std::string>& keywords) const;
    };

    using Opportunities = std::vector<Opportunity>;

    //
    // Functions
    //

    Opportunities filter(const Opportunities& opportunities, const std::string& keyword);

    Opportunities filter(const Opportunities& opportunities, const std::vector<std::string>& keywords);
} // db

#endif //SWE_PROJECT_OPPORTUNITY_H

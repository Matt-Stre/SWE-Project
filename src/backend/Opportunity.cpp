//
// Created by Aiden Zepp on 2024-03-29.
//

#include "Opportunity.h"

// std...
#include <algorithm>
#include <unordered_set>
#include <utility>

namespace db {
    //
    // --- PUBLIC ---
    //

    //
    // Constructors / Destructors
    //

    Opportunity::Opportunity(std::string name, std::string phone_number, std::string description,
                             std::vector<std::string> keywords) {
        this->name = std::move(name);
        this->phone_number = std::move(phone_number);
        this->description = std::move(description);
        this->keywords = std::move(keywords);
    }

    //
    // Methods
    //

    bool Opportunity::has(const std::string& keyword) const {
        return std::find(keywords.begin(), keywords.end(), keyword) != keywords.end();
    }

    bool Opportunity::has(const std::vector<std::string>& keywords) const {
        std::unordered_set<std::string> keywords_set(this->keywords.begin(), this->keywords.end());

        for (const std::string& kw : keywords) {
            if (keywords_set.find(kw) == keywords_set.end()) return false;
        }

        return true;
    }

} // db
//
// Created by Aiden Zepp on 2024-03-28.
//

#ifndef SWE_PROJECT_CSV_H
#define SWE_PROJECT_CSV_H

// std...
#include <map>
#include <string>
#include <vector>

namespace csv {
    //
    // Typedefs
    //

    using Data = std::map<std::string, std::vector<std::string>>;

    //
    // Functions
    //

    Data parse(const std::string& filepath);
} // csv

#endif //SWE_PROJECT_CSV_H

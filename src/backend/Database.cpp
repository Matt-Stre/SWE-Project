//
// Created by Aiden Zepp on 2024-03-29.
//

#include "Database.h"

// std...
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace db {
    //
    // --- PUBLIC ---
    //

    //
    // Constructors / Destructors
    //

    Database::Database() = default;

    Database::Database(const std::string &filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + filepath);
        }

        std::string line;
        std::getline(file, line); // Skip the header.
        while (std::getline(file, line)) {
            std::vector<std::string> tokens = split(line, ',');

            // Check for a valid number of columns.
            if (tokens.size() < 4) {
                throw std::runtime_error("Expected 4 columns per row in CSV, found " + std::to_string(tokens.size()));
            }

            // Generate the keywords into a vector.
            std::string keywords_str = tokens[3];
            if (keywords_str.front() == '"' && keywords_str.back() == '"') {
                keywords_str = keywords_str.substr(1, keywords_str.length() - 2);
            }
            std::vector<std::string> keywords = split(keywords_str, ',');

            // Remove last opportunity's trailing carriage return (i.e., '\r').
            if (!keywords.empty() && keywords.back().back() == '\r') {
                std::string& keyword = keywords.back();
                keyword = keyword.substr(0, keyword.size() - 1);
            }

            opportunities.emplace_back(tokens[0], tokens[1], tokens[2], keywords);
        }
    }

    //
    // Methods
    //

    Opportunities Database::filter(const std::string& keyword) {
        Opportunities filtered = Opportunities();

        for (const Opportunity& opportunity : opportunities) {
            if (opportunity.has(keyword)) {
                filtered.push_back(opportunity);
            }
        }

        return filtered;
    }

    Opportunities Database::filter(const std::vector<std::string>& keywords) {
        Opportunities filtered = Opportunities();

        for (const Opportunity& opportunity : opportunities) {
            if (opportunity.has(keywords)) {
                filtered.push_back(opportunity);
            }
        }

        return filtered;
    }

    //
    // --- PRIVATE ---

    //
    // Static Methods
    //

    std::string Database::trim(const std::string &str) {
        size_t first = str.find_first_not_of(' ');
        if (first == std::string::npos) {
            return str;
        }
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

    std::vector<std::string> Database::split(const std::string &str, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        bool inside_quotes = false;

        std::istringstream stream(str);
        while (stream.good()) {
            char c = static_cast<char>(stream.get());

            if (c == '"' && inside_quotes && stream.peek() == '"') {
                token += static_cast<char>(stream.get());
            } else if (c == '"') {
                inside_quotes = !inside_quotes;
            } else if (c == delimiter && !inside_quotes) {
                tokens.push_back(trim(token));
                token.clear();
            } else if (stream.eof()) {
                break;
            } else {
                token += c;
            }
        }

        // Add the last token.
        tokens.push_back(token);
        return tokens;
    }
} // db
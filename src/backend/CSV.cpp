//
// Created by Aiden Zepp on 2024-03-28.
//

#include "CSV.h"

// std...
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace csv {
    //
    // Functions
    //

    Data parse(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + filepath);
        }

        Data data;
        std::string line;
        // Read the header line
        std::getline(file, line);
        std::vector<std::string> headers;
        std::stringstream headerStream(line);
        std::string header;
        while (std::getline(headerStream, header, ',')) {
            headers.push_back(header);
        }

        // Check if "Name" is in the headers and find its index
        auto it = std::find(headers.begin(), headers.end(), "Name");
        if (it == headers.end()) {
            throw std::runtime_error("'Name' column not found in the CSV file.");
        }
        size_t nameIndex = std::distance(headers.begin(), it);

        // Read the data rows
        while (std::getline(file, line)) {
            std::stringstream lineStream(line);
            std::string cell;
            std::vector<std::string> rowValues;
            while (std::getline(lineStream, cell, ',')) {
                // Handle potential quoted strings with commas
                if (!cell.empty() && cell.front() == '"') {
                    std::string remainder;
                    while (std::getline(lineStream, remainder, ',')) {
                        cell += ',' + remainder;
                        if (!remainder.empty() && remainder.back() == '"') {
                            break;
                        }
                    }
                }
                rowValues.push_back(cell);
            }

            if (rowValues.size() < headers.size()) {
                throw std::runtime_error("Row has fewer columns than expected.");
            }

            // Extract name and rest of the data for the current row
            std::string name = rowValues.at(nameIndex);
            std::vector<std::string> rowData;
            for (size_t i = 0; i < rowValues.size(); ++i) {
                if (i != nameIndex) { // Skip 'Name' column
                    rowData.push_back(rowValues[i]);
                }
            }
            data.emplace(name, rowData);
        }

        return data;
    }
} // csv
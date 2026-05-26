#include "csv_loader.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool DataFrame::load_csv(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return false;
    }

    std::string line;

    // --- Read header ---
    if (!std::getline(file, line)) {
        std::cerr << "Error: Empty CSV file\n";
        return false;
    }

    std::stringstream header_stream(line);
    std::string col_name;
    std::vector<std::string> col_names;

    while (std::getline(header_stream, col_name, ',')) {
        col_names.push_back(col_name);
        table_[col_name] = {};
    }

    // --- Read rows ---
    while (std::getline(file, line)) {
        std::stringstream row_stream(line);
        std::string cell;
        size_t i = 0;

        while (std::getline(row_stream, cell, ',')) {
            table_[col_names[i]].push_back(std::stod(cell));
            i++;
        }
    }

    return true;
}

std::vector<std::string> DataFrame::columns() const {
    std::vector<std::string> names;
    names.reserve(table_.size());
    for (const auto& kv : table_) {
        names.push_back(kv.first);
    }
    return names;
}

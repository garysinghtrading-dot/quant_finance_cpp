#include "csv_loader.h"
#include <iostream>

int main() {
    DataFrame df;

    if (!df.load_csv("data/CRM.csv")) {
        return 1;
    }

    std::cout << "Loaded columns:\n";
    for (const auto& col : df.columns()) {
        std::cout << " - " << col << "\n";
    }

    return 0;
}

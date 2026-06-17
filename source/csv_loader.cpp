#include "csv_loader.h"

AnalyzerSecurity::AnalyzerSecurity(){
}

void AnalyzerSecurity::readFile(string filepath) {
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filepath << std::endl;
        return;
    }

    std::string line;
    // Skip header if there is one
    std::getline(file, line); 

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        
        // Create a new StoreData object on the heap
        StoreData* newRow = new StoreData();
        
        // Read 4 columns separated by commas
        std::getline(ss, cell, ','); newRow->col0 = std::stof(cell); 
        std::getline(ss, cell, ','); newRow->col1 = std::stof(cell);
        std::getline(ss, cell, ','); newRow->col2 = std::stof(cell);
        std::getline(ss, cell, ','); newRow->col3 = std::stof(cell);
        std::getline(ss, cell, ','); newRow->col4 = std::stof(cell);
        
        // Add to our vector
        sd.push_back(newRow);
    }
    file.close();
}

void AnalyzerSecurity::printValue(size_t index, string column){
  // Check if index is within bounds to avoid a crash
  if (index >= sd.size()) {
    std::cout << "Index out of bounds!" << std::endl;
    return;
  }

  if (column == "col1") {
    std::cout << sd[index]->col1 << std::endl;
  } else if (column == "col2") {
      std::cout << sd[index]->col2 << std::endl;
  } else if (column == "col3") {
    std::cout << sd[index]->col3 << std::endl;
  } else if (column == "col4") {
      std::cout << sd[index]->col4 << std::endl;
  } else {
      std::cout << "Invalid column name." << std::endl;
  }
}

AnalyzerSecurity::~AnalyzerSecurity() {
    //delete sd; // Clean up the memory here
}
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

    //int rowIndex = 0; // Track row number for the training offset
    while (std::getline(file, line)) {
      std::stringstream ss(line);
      std::string cell;
      vector<float> rowdata;
            
      while (std::getline(ss, cell, ',')) {
          // Strip trailing carriage return if present (fixes Windows line-ending issues)
          if (!cell.empty() && cell.back() == '\r') {
              cell.pop_back();
          }

          if (cell.empty() || cell == "nan" || cell == "NaN") {
              rowdata.push_back(0.0f); 
          } else {
              try {
                  rowdata.push_back(std::stof(cell));
              } catch (const std::exception& e) {
                  std::cerr << "Error parsing cell value: '" << cell << "' -> " << e.what() << std::endl;
                  rowdata.push_back(0.0f); // Fallback safely
              }
          }
      }
          AllData.push_back(rowdata);
        //rowIndex++;
    }
    file.close();
}

void AnalyzerSecurity::printValue(size_t index, string column){
  // Check if index is within bounds to avoid a crash
  int col_index = 0;
  for(int i=0; i<colNames.size(); i++){
    if(colNames[i] == column){
      col_index=i;
    }
  }

  if (index >= AllData.size()) {
    std::cout << "Index out of bounds!" << std::endl;
    return;
  }

  cout << AllData[index][col_index] << " " << endl;
}

AnalyzerSecurity::~AnalyzerSecurity() {
    //delete sd; // Clean up the memory here
}
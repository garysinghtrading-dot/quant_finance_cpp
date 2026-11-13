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
  std::vector<std::string> headers; // Keep track of column names in order

  // 1. Read header line first
  if (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string colName;
    int index = 0;

    while (std::getline(ss, colName, ',')) {
      // Remove trailing carriage return
      if (!colName.empty() && colName.back() == '\r') {
        colName.pop_back();
      }

      // Strip UTF-8 BOM if present on the first column
      if (index == 0 && colName.rfind("\xEF\xBB\xBF", 0) == 0) {
        colName.erase(0, 3);
      }

      // FIX: Strip surrounding quotes if the CSV header is quoted (e.g., "Open" -> Open)
      if (!colName.empty() && colName.front() == '"' && colName.back() == '"') {
        colName = colName.substr(1, colName.size() - 2);
      }

      // Trim any remaining whitespace
      // (Optional safeguard if your CSV has spaces like " Open")
      // colName.erase(0, colName.find_first_not_of(" \t"));
      // colName.erase(colName.find_last_not_of(" \t") + 1);

      headers.push_back(colName);
      
      // Only map it if it's NOT a date
      if (colName != "Date") {
        colNameIndex[colName] = colNameIndex.size(); 
      }
      index++;
    } 
  } 

  // 2. Read the remaining data rows
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string cell;
    std::vector<double> rowdata;
    size_t col_idx = 0;

    while (std::getline(ss, cell, ',')) {
      if (!cell.empty() && cell.back() == '\r') {
        cell.pop_back();
      }

      // GUARD: If this column is the "Date" column, completely ignore it!
      if (col_idx < headers.size() && headers[col_idx] == "Date") {
        col_idx++;
        continue; 
      }

      // Parse the rest normally as numbers
      if (cell.empty() || cell == "nan" || cell == "NaN") {
        rowdata.push_back(0.0);
      } 
      else {
        try {
          rowdata.push_back(std::stod(cell));
        } catch (const std::exception& e) {
          rowdata.push_back(0.0);
        }
      }
      col_idx++;
    } 
    AllData.push_back(rowdata);
  }
  file.close();
}

void AnalyzerSecurity::printValue(size_t index, string column){
  // Check if index is within bounds to avoid a crash
  auto it = colNameIndex.find(column);

  // check if the column exists
  if(it == colNameIndex.end()){
    std::cout << "Column " << column << " does not exist" << std::endl;
    return; // return immediately
  }

  // check if tht row exists (not out of bounds)
  if (index >= AllData.size()) {
    std::cout << "Index out of bounds!" << std::endl;
    return; // return 
  }

  int col_index = it->second;
  cout << AllData[index][col_index] << " " << endl;
}

vector<vector<double>> AnalyzerSecurity::GetAllData(){
  return AllData; //wx+b
}

AnalyzerSecurity::~AnalyzerSecurity() {
    //delete sd; // Clean up the memory here
}
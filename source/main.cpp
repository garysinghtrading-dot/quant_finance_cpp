#include "csv_loader.h"
#include <iostream>
using namespace std; 

int main(int argc, char* argv[]) {
  // 1. Check if the argument was provided
  // argc is at least 1 (the program name), so 2 means 1 argument was passed
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <filepath_to_csv>" << std::endl;
    return 1; // Return 1 to indicate an error
  }

  // 2. Extract the argument (it's a C-style string, so cast to std::string)
  std::string csvPath = argv[1];
  csvPath = "data/" + csvPath + ".csv"; 

  cout << "Relative Path: " << csvPath << endl;
  AnalyzerSecurity analyzer;
  analyzer.readFile(csvPath);
  analyzer.printValue(0, "col4");



  return 0;
}

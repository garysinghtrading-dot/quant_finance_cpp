#include "csv_loader.h"
#include "feature_engineering.h"
#include "linear_algebra.h"
#include <iostream>
#include<vector>
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
  
  int _idx = 0;
  vector<string> features = {"Open", "High", "Low", "Close"};
  for(size_t i=0; i<features.size(); i++){
    analyzer.printValue(_idx, features[i]);
  }

  /*
  Feature Engineering
    1. Add SMA's
  */
  FeatureEngineering Fe; // Class object of Feature Engineering Class
  analyzer.AddSma(Fe);

  vector<string> MAs = {"SMA_10", "SMA_20", "SMA_50"};
  string feature_ = "Close";

  for(size_t i=0; i<MAs.size(); i++){
    analyzer.ComputePctDiff(feature_, MAs[i], Fe);
  }

  return 0;
}

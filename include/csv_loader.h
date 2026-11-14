#ifndef CSV_LOADER_H
#define CSV_LOADER_H

#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<string>
#include<unordered_map>
#include "feature_engineering.h"

using namespace std;

class AnalyzerSecurity{
  private: 
    /*
      - 2D Matrix to store row and column values
    */
    vector<vector<double>> AllData;

    // Hashmap to store feature name and their respective columns
    unordered_map<string, int> colNameIndex;

  public:
    AnalyzerSecurity();
    void readFile(string filepath);
    void printValue(size_t index, string column);
    void AddFeature(string name);
    void AddVector(vector<double> new_data);
    vector<vector<double>> GetAllData();
    int get_index(string col_name);
    void AddSma(FeatureEngineering Fe);
    void ComputePctDiff(string col1, string col2, FeatureEngineering Fe);
    ~AnalyzerSecurity();
};
#endif
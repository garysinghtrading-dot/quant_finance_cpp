#ifndef CSV_LOADER_H
#define CSV_LOADER_H

#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<string>
#include<unordered_map>

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
    vector<vector<double>> GetAllData();
    ~AnalyzerSecurity();
};
#endif
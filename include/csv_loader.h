#ifndef CSV_LOADER_H
#define CSV_LOADER_H


#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<string>
using namespace std;

struct StoreData{
  float col0=0, col1=0, col2=0, col3=0, col4=0;
};

class AnalyzerSecurity{
  private: 
    vector<StoreData*> sd; 
  public:
    AnalyzerSecurity();
    void readFile(string filepath);
    void printValue(size_t index, string column);
    ~AnalyzerSecurity();
};
#endif
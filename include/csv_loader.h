#ifndef CSV_LOADER_H
#define CSV_LOADER_H

#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<string>

using namespace std;




class AnalyzerSecurity{
  private: 
    /*
      - 2D Matrix to store row and column values
    */
    vector<vector<float>> AllData;
    /*
      * Vector of string to store feature column names
    */
    vector<string> colNames = {
        "Temporal_Velocity_Alpha",
        "Manifold_Proximity_Scalar",
        "Barycentric_Divergence_Index",
        "Normalized_Deviation_Magnitude",
        "Distribution_Curvature_Coefficient",
        "Distribution_Asymmetry_Coefficient",
        "Dispersion_Magnitude_Metric",
        "Target"
    };
  public:
    AnalyzerSecurity();
    void readFile(string filepath);
    void printValue(size_t index, string column);
    ~AnalyzerSecurity();
};
#endif
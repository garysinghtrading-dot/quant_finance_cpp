#ifndef FEATURE_ENGINEERING_H
#define FEATURE_ENGINEERING_H

#include<iostream>
#include <vector>

class FeatureEngineering {
  private:
    int val = 0; // placeholder

  public:
    FeatureEngineering(); // Default Constructor 
    std::vector<double> ComputeSMA(const std::vector<double>& data, int period);
}; 

#endif
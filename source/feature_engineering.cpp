#include "feature_engineering.h"

FeatureEngineering::FeatureEngineering(){} // Defo Constructor 

std::vector<double> FeatureEngineering::ComputeSMA(const std::vector<double>& data, int period){
  size_t total_rows = data.size(); // How many rows 
  std::vector<double> smaValues(total_rows, 0.0);

  if(period <=0 || total_rows < static_cast<size_t>(period)){
    std::cerr << "Invalid period or insufficient data for SMA_" << period << std::endl;
    return smaValues;
  }

  double windowSum = 0.0;
  
  for(size_t i=0; i<total_rows; i++){
    windowSum += data[i];
    if(i==static_cast<size_t>(period) -1){
      // first datapoint to write data to
      smaValues[i] = (windowSum/period);
    }     
    if(i >= static_cast<size_t>(period)){
      windowSum -= data[i-period]; // if i = 20, we subtract 1-20, so we reduce the windowSum by the datapoint that just left the window
      smaValues[i] = (windowSum/period);
    }
  } // end for loop

  return smaValues;
}

double FeatureEngineering::PercentDifference(double val1, double val2){ 
  if(val2 == 0.0) return val2; // just return 0, we don't have enough data to compute this value
  return (val1 - val2)/val2;
}
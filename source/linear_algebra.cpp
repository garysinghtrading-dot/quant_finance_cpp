#include "linear_algebra.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

// ClassName: LinearAlgebra
double LinearAlgebra::DotProduct(const std::vector<double>& X1, const std::vector<double>& X2){

  // Check for empty arrays and non-equal size arrays
  if(X1.empty() || X2.empty() || X1.size() != X2.size()){
    throw std::invalid_argument("Vectors must be of equal size and not be empty");
  }

  double sum = 0.0;

  for(size_t i=0; i<X2.size(); i++){
    sum += X1[i] * X2[i];
  }
  return sum;
  
}

double LinearAlgebra::Magnitude(const std::vector<double>& v){
  if(v.empty()){
    throw std::invalid_argument("Cant compute magnitude of empty vector");
  }

  return std::sqrt(LinearAlgebra::DotProduct(v,v));
}

double LinearAlgebra::EuclideanDistance(const std::vector<double>& X1, const std::vector<double>& X2){
  if(X1.empty() || X2.empty() || X1.size() != X2.size()){
    throw std::invalid_argument("Vectors must be of equal size and not be empty");
  }
  double dist = 0.0;
  for(size_t i=0; i<X2.size(); i++){
    double diff = (X1[i] - X2[i]);
    dist += (diff * diff);
  }
  return std::sqrt(dist);
}

double LinearAlgebra::ScalarProjection(const std::vector<double>& X1, const std::vector<double>& X2){
  if(X1.empty() || X2.empty() || X1.size() != X2.size()){
    throw std::invalid_argument("Vectors must be of equal size and not be empty");
  }

  double dot_product = LinearAlgebra::DotProduct(X1, X2);
  double mag_x2 = LinearAlgebra::Magnitude(X2);
  if(mag_x2 == 0.0){
    throw std::runtime_error("Cant divide by 0");
  }

  double scaler_projection = dot_product/mag_x2;
  return scaler_projection;

}
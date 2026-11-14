#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

#include <vector>

class LinearAlgebra {
  public:
    // Core Vector Operations
    static double DotProduct(const std::vector<double>& X1, const std::vector<double>& X2);
    static double Magnitude(const std::vector<double>& v);
    static double EuclideanDistance(const std::vector<double>& X1, const std::vector<double>& X2);
    static double ManhattanDistance(const std::vector<double>& X1, const std::vector<double>& X2);
    static double ScalarProjection(const std::vector<double>& X1, const std::vector<double>& b);
    static double CosineSimilarity(const std::vector<double>& X1, const std::vector<double>& X2);
};

#endif
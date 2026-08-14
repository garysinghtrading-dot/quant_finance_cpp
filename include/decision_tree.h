#ifndef CSV_LOADER_H
#define CSV_LOADER_H

#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<string>

using namespace std;




class TrainDecisionTree{
  private:
    struct TreeNode {
      int feature_index;
      float threshold;          // Fixed spacing/name
      TreeNode* left;           // Fixed pointer syntax
      TreeNode* right;          // Fixed pointer syntax
      float prediction;         // If this is a leaf node
    };
    float calculate_variance(const vector<vector<float>>& subset);
    TreeNode* build_tree(const vector<vector<float>>& data, int current_depth, int max_depth, int min_samples_leaf);

    public:
    TrainDecisionTree();
    void fit(const vector<vector<float>>& data, int max_depth, int min_samples_split);
    
    ~TrainDecisionTree();
};
#endif
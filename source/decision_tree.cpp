#include "decision_tree.h"

TrainDecisionTree::TrainDecisionTree(){
  // DeFo Constructor
}

float TrainDecisionTree::calculate_variance(const vector<vector<float>>& subset) {
    if (subset.empty()) return 0.0f;

    size_t target_col = subset[0].size() - 1;
    float sum = 0.0f;

    // 1. Calculate the mean of the target values
    for (const auto& row : subset) {
        sum += row[target_col];
    }
    float mean = sum / subset.size();

    // 2. Calculate the average of the squared differences from the mean (Variance)
    float squared_diff_sum = 0.0f;
    for (const auto& row : subset) {
        float diff = row[target_col] - mean;
        squared_diff_sum += (diff * diff);
    }

    return squared_diff_sum / subset.size();
}

TreeNode* TrainDecisionTree::build_tree(const vector<vector<float>>& data, int current_depth, int max_depth, int min_samples_leaf){
  if(current_depth >= max_depth || data.size() < size_t(2)*min_samples_leaf){
    // Leaf Node
    TreeNode* leaf = new TreeNode();
    leaf->feature_index = -1;

    // compute target sum
    float target_sum = 0.0f;
    size_t target_col data[0].size() - 1; // <-- target column is the last row

    for(const auto&row : data){
      target_sum += row[target_col]; 
    }
    // leaf predeiction
    leaf->prediction = target_sum/data[0].size();

    // set its left and right as nullptr, this is a leaf nod
    leaf->left = nullptr;
    leaf->right = nullptr;

    return leaf;
  }

  // 2. Search for the best split
  float best_variance = std::numeric_limits<float>::max();
  int best_feature = -1;
  float best_threshold = 0.0f;

  vector<vector<float>> best_left_data;
  vector<vector<float>> best_right_data;

  size_t num_features = data[0].size() - 1; // number of features 
  for (size_t f = 0; f < num_features; ++f) {
    for(size_t i =0; i<data.size(); ++i){
      float threshold = data[i][f];

      vector<vector<float>> left_subset;
      vector<vector<float>> right_subset;

      // partiton based on threshold
      (const auto& row : data){
        if(row[f] < threshold)
      }

    }
  }
}


void TrainDecisionTree::const vector<vector<float>>& data, int max_depth, int min_samples_split{

}
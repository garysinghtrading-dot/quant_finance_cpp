import numpy as np
import pandas as pd 


class Compute_Centroid_Features:
    def __init__(self, dataframe):
        self.class_name = "centroid class"
        self.dataframe = dataframe

    def split_data_frame(self, current_index, window_size):
        window_data = self.dataframe.iloc[current_index - window_size: current_index + 1]
        return window_data 

    def compute_euclidiean_distance(self, last_data, current_centroid, curr_centroid_norm):
        '''
        * Method to compute the Euclidean Distance of two values
        * Gives us a measure of how far is current feature to its centroid feature
        * ARGS:
            * last_data -> (NumPy Array) current index, current values
            * current_centroid -> (NumPy Array) Row Vector of current centroid
            * curr_centroid_norm -> (Scaler) Current distance to origin
        * OPERATIONS:
            1. Computes Euclidean Distance of last datapoint to its current centroid
            2. Standardizes the distance by dividing it by current centroid_norm (dist to origin)
        * RETURNS:
            - returns standardized Euclidean Distance
                - (The Euclidean Distance is standardized, it scales to the data)
        '''
        cur_euclidean_dist = np.linalg.norm(last_data - current_centroid)
        cur_relative_distance = cur_euclidean_dist / curr_centroid_norm
        return cur_relative_distance

    def compute_relative_manhattan_distance(self, last_data, current_centroid, cur_centroid_norm):
        '''
        * Method to compute the Manhattan Distance of two values
        * Gives us a measure of how far is current feature to its centroid feature
        * ARGS:
            * last_data -> (NumPy Array) current index, current values
            * current_centroid -> (NumPy Array) Row Vector of current centroid
            * curr_centroid_norm -> (Scaler) Current distance to origin
        * OPERATIONS:
            1. Computes Manhattan Distance of last datapoint to its current centroid
            2. Standardizes the distance by dividing it by current centroid_norm (dist to origin)
        * RETURNS:
            - returns standardized Manhattan Distance
                - (The Manhattan Distance is standardized, it scales to the data)
        '''
        man_dist = np.sum(np.abs(last_data - current_centroid))
        relative_mah_dist = man_dist / cur_centroid_norm
        return relative_mah_dist

    def compute_signed_deviation(self, last_data, current_centroid, centroid_norm):
        diff = last_data - current_centroid
        signed_dev = np.dot(diff, current_centroid) / (centroid_norm ** 2)
        return signed_dev 
    
    def compute_z_scores(self, today_mean_col, window_mean_val, std_dev_val, window_size):
        '''
        * Computes a z-score of todays data relative to its window data
        * ARGS:
            * today_mean_col -> (float) Mean of todays input vector
            * window_mean_val -> (float) Mean value of the current window
            * std_dev_val -> (float) Standard Deviation of the current window
            * window_size -> (int) Size of the current window
        * RETURNS:
            NONE
            - All operations are stored in the dataframe that is already a class object
        '''
        self.dataframe[f'today_z_score_{window_size}'] = (
            (self.dataframe[today_mean_col] - self.dataframe[window_mean_val]) 
            / self.dataframe[std_dev_val]
        )
        
    def compute_centroid(self, features, window_size):
        '''
        * Method to compute a centroid of data given various inputs
        * This method assumes input features do not need scaling
        * ARGS:
            * df -> (pd.dataframe) Pandas dataframe that contains the data
            * features -> (list) input features (feature names) as a list
            * window_size -> (int)
        * RETURNS:
            NONE -> the results are stored in a dataframe that is a class object 
        * WARNING:
            - If inputs are not standardized (on same scale) prior to this method
                - The features with the largest magnitude will dominate the data and results
        '''
        for i in range(window_size - 1, len(self.dataframe)):
            # Split data for appropriate window size
            window_data = self.split_data_frame(i, window_size)
            data = window_data[features].values

            if data.size == 0 or np.all(np.isnan(data)):
                # The Column for this row has NaN we need to continue
                continue

            # Compute Centroid
            current_centroid = np.mean(data, axis=0) 

            # If the centroid itself is all NaNs after mean
            if np.all(np.isnan(current_centroid)):
                continue

            centroid_norm = np.linalg.norm(current_centroid) # Distance to origin
            self.dataframe.loc[i, f"centroid_dist_origin_{window_size}"] = centroid_norm
            
            # Relative Distance of Euclidean Distance to Centroid Norm
            last_data = data[-1]
            self.dataframe.loc[i, f"relative_euclidean_distance_to_centroid_norm_{window_size}"] = (
                self.compute_euclidiean_distance(last_data, current_centroid, centroid_norm)
            )

            # Relative Manhattan Distance
            self.dataframe.loc[i, f"relative_manhattan_distance_to_centroid_norm_{window_size}"] = (
                self.compute_relative_manhattan_distance(last_data, current_centroid, centroid_norm)
            )

            # Relative Deviation
            self.dataframe.loc[i, f"relative_centroid_deviation_{window_size}"] = (
                self.compute_signed_deviation(last_data, current_centroid, centroid_norm)
            )

            # Windowed Mean Across All Features
            self.dataframe.loc[i, f"windowed_mean_{window_size}"] = np.mean(data)
            self.dataframe.loc[i, f"windowed_std_dev_{window_size}"] = np.std(data)
            
            if i % 1000 == 0:
                print(f"Processed {i} rows")

        print(f"Done with {window_size}")

import numpy as np
import pandas as pd 

class Compute_Centroid_Features:
    def __init__(self, dataframe):
        self.class_name = "centroid class"
        self.dataframe = dataframe

    
    def split_data_frame(self, current_index, window_size):
        window_data = self.dataframe.iloc[current_index - window_size: current_index+1]
        return window_data 
    

    def compute_euclidiean_distance(self,index, features, current_centroid):
        '''
        * Method to compute the Euclidean Distance of two values
        * Gives us a measure of how far is current feature to its centroid feature
        * ARGS:
            * index -> (int) current index we are looking at
            * features -> (list) a list of the input features to be used
            * current_centroid (numpy array) -> centroid values to take the difference of
        * RETURNS:
            - returns np.linalg.norm() of 
        '''

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
        for i in range(window_size-1, len(self.df)):
            # Split data for appropriate window size
            window_data = self.split_data_frame(i, window_size)# df.iloc[i - window_size: i+1]
            data = window_data[features].values

            if data.size == 0 or np.all(np.isnan(data)):
                # The Column for this row has NaN we need to continue
                continue

            # Compute Centroid
            current_centroid = np.mean(data, axis=0) # Mean of all datapoints per column in the window size (axis=0 means per column)

            # If the centroid itself is all NaNs after nanmean (e.g., if all values in a feature column were NaN in the window)
            if np.all(np.isnan(current_centroid)):
                continue

            centroid_norm = np.linalg.norm(current_centroid) # Distance to origin

            self.df.iloc[i, f"centroid_dist_origin_{window_size}"] = centroid_norm
            
            # Compute Euclidean Distance


            if i%1000 == 0:
                print(f"Processed {i} rows")

        print(f"Done with {window_size}")

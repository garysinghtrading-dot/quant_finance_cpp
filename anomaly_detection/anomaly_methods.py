import pandas as pd
import numpy as np
from sklearn.covariance import MinCovDet
from sklearn.ensemble import IsolationForest
from sklearn.preprocessing import StandardScaler

class AnomalyDetector:
    def __init__(self, contamination: float = 0.1):
        self.contamination = contamination
        self.fast_mcd = None
        self.iso_forest = None
        self.scaler = StandardScaler()

    def fit_predict(
        self, 
        df: pd.DataFrame, 
        feature_cols: list[str], 
        start_idx: int = None, 
        end_idx: int = None
    ) -> pd.DataFrame:
        """
        Scales input data using [start_idx:end_idx] slice, runs FastMCD and Isolation Forest,
        computes decision boundary distances, and appends results to the DataFrame.
        """
        result_df = df.copy()
        
        # Slice for fitting scaler
        fit_slice = df[feature_cols].iloc[start_idx:end_idx]
        self.scaler.fit(fit_slice)
        
        # Scale the full slice for transformation & model inputs
        scaled_data = self.scaler.transform(df[feature_cols])
        
        # 1. FastMCD (Minimum Covariance Determinant)
        self.fast_mcd = MinCovDet(random_state=42)
        # Fit FastMCD on the designated slice of scaled data
        scaled_fit_slice = scaled_data[start_idx:end_idx] if start_idx is not None or end_idx is not None else scaled_data
        self.fast_mcd.fit(scaled_fit_slice)
        
        # Mahalanobis distance calculation on full dataset
        mahal_dist = self.fast_mcd.mahalanobis(scaled_data)
        result_df["fastmcd_dist"] = mahal_dist
        
        # Decision boundary distance threshold for FastMCD based on quantile
        mcd_threshold = np.quantile(mahal_dist[start_idx:end_idx], 1 - self.contamination)
        result_df["fastmcd_boundary_dist"] = mahal_dist - mcd_threshold
        result_df["fastmcd_anomaly"] = (mahal_dist > mcd_threshold).astype(int)

        # 2. Isolation Forest
        self.iso_forest = IsolationForest(
            contamination=self.contamination, 
            random_state=42, 
            n_jobs=-1
        )
        self.iso_forest.fit(scaled_fit_slice)
        
        # decision_function returns positive for inliers, negative for outliers
        # Distance to boundary: 0 is exact boundary, negative is anomalous
        iso_boundary_dist = self.iso_forest.decision_function(scaled_data)
        iso_preds = self.iso_forest.predict(scaled_data)
        
        result_df["iso_boundary_dist"] = iso_boundary_dist
        result_df["iso_anomaly"] = np.where(iso_preds == -1, 1, 0)

        return result_df
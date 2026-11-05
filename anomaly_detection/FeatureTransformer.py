import pandas as pd
import numpy as np
from sklearn.preprocessing import StandardScaler

class FeatureTransformer:
    def __init__(self, df: pd.DataFrame):
        self.df = df.copy()
        
    def add_moving_averages(self, feature_cols: list[str], window: int) -> pd.DataFrame:
        """
        Computes Simple Moving Average (SMA) and Exponential Moving Average (EMA)
        for specified features over a given window and appends them to the dataframe.
        """
        for col in feature_cols:
            if col not in self.df.columns:
                raise KeyError(f"Column '{col}' not found in DataFrame.")
                
            sma_col = f"{col}_sma_{window}"
            ema_col = f"{col}_ema_{window}"
            
            self.df[sma_col] = self.df[col].rolling(window=window).mean()
            self.df[ema_col] = self.df[col].ewm(span=window, adjust=False).mean()
            
        return self.df

    def scale_features(
        self, 
        feature_cols: list[str], 
        start_idx: int = None, 
        end_idx: int = None
    ) -> tuple[pd.DataFrame, StandardScaler]:
        """
        Fits a StandardScaler strictly on df.iloc[start_idx:end_idx] (or full slice if None)
        and transforms the entire feature set to avoid data leakage.
        Returns scaled DataFrame and fitted scaler.
        """
        scaler = StandardScaler()

        # Determine fit slice bounds
        fit_data = self.df[feature_cols].iloc[start_idx:end_idx]
        X_train_scaled = scaler.fit_transform(fit_data)

        return X_train_scaled, scaler 


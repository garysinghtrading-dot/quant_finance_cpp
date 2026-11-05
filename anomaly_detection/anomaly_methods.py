import numpy as np
from scipy.stats import percentileofscore
from sklearn.covariance import MinCovDet
from sklearn.ensemble import IsolationForest
import warnings

class AnomalyDetector:
    def __init__(self, contamination: float = 0.1, random_state: int = 42):
        self.contamination = contamination
        self.random_state = random_state
        
        # FastMCD attributes
        self.mcd_model = None
        self.mcd_train_boundary_dists = None
        self.mcd_threshold = None
        
        # Isolation Forest attributes
        self.iso_model = None
        self.iso_train_boundary_dists = None

    # =========================================================================
    # FAST MCD METHODS
    # =========================================================================
    
    def fit_fastmcd(self, X_train_scaled: np.ndarray, support_fraction: float = 0.75) -> tuple[MinCovDet, np.ndarray]:
        """
        Fits FastMCD on scaled training slice with increased support_fraction
        and rank check to eliminate determinant divergence warnings.
        """
        # 1. Check for constant/zero-variance features in the slice
        variances = np.var(X_train_scaled, axis=0)
        if np.any(variances < 1e-8):
            zero_var_indices = np.where(variances < 1e-8)[0]
            warnings.warn(f"Features at indices {zero_var_indices} have near-zero variance in slice.")

        # 2. Fit FastMCD with higher support_fraction and suppressed C-step noise
        with warnings.catch_warnings():
            warnings.filterwarnings("ignore", category=RuntimeWarning, module="sklearn.covariance._robust_covariance")
            warnings.filterwarnings("ignore", category=UserWarning, module="sklearn.covariance._robust_covariance")
            
            self.mcd_model = MinCovDet(
                support_fraction=support_fraction, 
                random_state=self.random_state
            )
            self.mcd_model.fit(X_train_scaled)
        
        # 3. Compute distances and boundary threshold
        train_mahal_dists = self.mcd_model.mahalanobis(X_train_scaled)
        self.mcd_threshold = np.quantile(train_mahal_dists, 1 - self.contamination)
        self.mcd_train_boundary_dists = train_mahal_dists - self.mcd_threshold
        
        return self.mcd_model, self.mcd_train_boundary_dists

    def predict_fastmcd(self, X_test_scaled: np.ndarray) -> tuple[np.ndarray, np.ndarray, np.ndarray]:
        """
        Predicts anomalies for test points using fitted FastMCD model.
        
        Returns:
            is_anomaly: 1 if anomaly, 0 if inlier
            boundary_distance: distance to decision boundary (positive = anomalous)
            percentile_rank: percentile rank relative to training boundary distances
        """
        if self.mcd_model is None or self.mcd_train_boundary_dists is None:
            raise RuntimeError("FastMCD model must be fitted prior to running predictions.")
            
        test_mahal_dists = self.mcd_model.mahalanobis(X_test_scaled)
        boundary_dists = test_mahal_dists - self.mcd_threshold
        is_anomaly = (test_mahal_dists > self.mcd_threshold).astype(int)
        
        # Percentile rank of test distances relative to training distances
        percentiles = np.array([
            percentileofscore(self.mcd_train_boundary_dists, dist, kind='weak')
            for dist in boundary_dists
        ])
        
        return is_anomaly, boundary_dists, percentiles

    # =========================================================================
    # ISOLATION FOREST METHODS
    # =========================================================================

    def fit_isolation_forest(self, X_train_scaled: np.ndarray) -> tuple[IsolationForest, np.ndarray]:
        """
        Fits Isolation Forest on scaled training data.
        Computes decision boundary distances for X_train_scaled.
        
        Returns:
            (fitted_iso_model, train_boundary_distances)
        """
        self.iso_model = IsolationForest(
            contamination=self.contamination, 
            random_state=self.random_state, 
            n_jobs=-1
        )
        self.iso_model.fit(X_train_scaled)
        
        # decision_function: 0 is decision boundary, negative is anomalous, positive is inlier
        self.iso_train_boundary_dists = self.iso_model.decision_function(X_train_scaled)
        
        return self.iso_model, self.iso_train_boundary_dists

    def predict_isolation_forest(self, X_test_scaled: np.ndarray) -> tuple[np.ndarray, np.ndarray, np.ndarray]:
        """
        Predicts anomalies for test points using fitted Isolation Forest model.
        
        Returns:
            is_anomaly: 1 if anomaly, 0 if inlier
            boundary_distance: raw decision_function output (negative = anomalous)
            percentile_rank: percentile rank relative to training boundary distances
        """
        if self.iso_model is None or self.iso_train_boundary_dists is None:
            raise RuntimeError("Isolation Forest model must be fitted prior to running predictions.")
            
        boundary_dists = self.iso_model.decision_function(X_test_scaled)
        raw_preds = self.iso_model.predict(X_test_scaled)
        is_anomaly = np.where(raw_preds == -1, 1, 0)
        
        # Percentile rank relative to training decision scores
        percentiles = np.array([
            percentileofscore(self.iso_train_boundary_dists, dist, kind='weak')
            for dist in boundary_dists
        ])
        
        return is_anomaly, boundary_dists, percentiles
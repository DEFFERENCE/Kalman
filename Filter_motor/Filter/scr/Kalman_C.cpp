#include "Kalman_C.h"
#include <iostream>
KalmanFilter::KalmanFilter(float initial_est, float initial_error, float error_measure, float threshold)
    : initial_est_(initial_est), initial_error_(initial_error), error_meas_(error_measure), threshold_(threshold),
      estimate_high_(initial_est), estimate_low_(-initial_est), error_est_before_low_(initial_error),
      error_est_before_high_(initial_error), err_est_current_low_(initial_error), err_est_current_high_(initial_error), signal_(0.0) {}

void KalmanFilter::get_Signal(float signal)
{
    signal_ = signal;
}

float KalmanFilter::Kalman_Gain(float error_est, float error_measure)
{
    return error_est / (error_est + error_measure);
}

float KalmanFilter::Est_current(float KG, float Mea, float Est_before)
{
    return Est_before + KG * (Mea - Est_before);
}

float KalmanFilter::Error_Est_current(float KG, float error_est_before)
{
    return (1 - KG) * error_est_before;
}

float KalmanFilter::filter()
{
    float Mea = signal_;
    if (Mea >= threshold_)
    {
        float KG_High = Kalman_Gain(err_est_current_high_, error_meas_);
        estimate_high_ = Est_current(KG_High, Mea, estimate_high_);
        err_est_current_high_ = Error_Est_current(KG_High, error_est_before_high_);
        error_est_before_high_ = err_est_current_high_;
        return estimate_high_;
    }
    else if (Mea <= -threshold_)
    {
        float KG_Low = Kalman_Gain(err_est_current_low_, error_meas_);
        estimate_low_ = Est_current(KG_Low, Mea, estimate_low_);
        err_est_current_low_ = Error_Est_current(KG_Low, error_est_before_low_);
        error_est_before_low_ = err_est_current_low_;
        return estimate_low_;
    }
    else
    {
        return Mea;
    }
}

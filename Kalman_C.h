#ifndef Kalman_C_H
#define Kalman_C_H

class KalmanFilter
{
public:
    KalmanFilter(float initial_est, float initial_error, float error_measure, float threshold);
    float filter();
    void get_Signal(float signal);
    float Kalman_Gain(float error_est, float error_measure);
    float Est_current(float KG, float Mea, float Est_before);
    float Error_Est_current(float KG, float error_est_before);

private:
    float signal_ = 0;
    float initial_est_ = signal_;
    float estimate_high_ = signal_;
    float estimate_low_ = signal_;
    float initial_error_ = 0.5;
    float error_meas_ = 0.2;
    float threshold_ = 0.2;
    float error_est_before_low_ = initial_error_;
    float error_est_before_high_ = initial_error_;
    float err_est_current_low_ = initial_error_;
    float err_est_current_high_ = initial_error_;
};

#endif

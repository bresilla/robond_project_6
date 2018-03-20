#include <iostream>
#include <math.h>
#include <tuple>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/LU>

using namespace std;
using namespace Eigen;

double new_mean, new_var;

double gauss(double mean, double sigma2, double x){
    return 1.0/sqrt(2.0 * M_PI * sigma2) * exp(-0.5 * pow((x-mean), 2.0) / sigma2);
}

tuple<double, double> measurement_update(double mean1, double var1, double mean2, double var2){
    new_mean = (var2*mean1+var1*mean2)/(var1+var2);
    new_var = 1.0/(1.0/var1+1.0/var2);
    return make_tuple(new_mean, new_var);
}
tuple<double, double> state_prediction(double mean1, double var1, double mean2, double var2){
    new_mean = mean1 + mean2;
    new_var =var1 + var2;
    return make_tuple(new_mean, new_var);
}

int main(){
    //Measurements and measurement variance
    double measurements[5] = { 5, 6, 7, 9, 10 };
    double measurement_sig = 4;
    
    //Motions and motion variance
    double motion[5] = { 1, 1, 2, 1, 1 };
    double motion_sig = 2;
    
    //Initial state
    double mu = 10;
    double sig = 1;
    
    //Put your code here:
    for (int a = 0; a < sizeof(measurements)/sizeof(measurements[0]); a++){
        tie(mu, sig) = measurement_update(mu, sig, measurements[a], measurement_sig);
        printf("update:  [%f, %f]\n", mu, sig);
        tie(mu, sig) = state_prediction(mu, sig, motion[a], motion_sig);
        printf("predict: [%f, %f]\n", mu, sig);
    }
    return 0;
}
#include<cmath>
#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Dense>
#include<iostream>

const double Pi = acos(-1);

int main(){

    Eigen::Vector3f P(2.0f, 1.0f, 1.0f);
    Eigen::Matrix3f Transform_Matrix;
    double angle = 45.0 / 180.0 * Pi;
    Transform_Matrix << cos(angle), -sin(angle), 1,
                        sin(angle), cos(angle), 2,
                        0, 0, 1;
    Eigen::Vector3f P_Prime = Transform_Matrix * P;
    std::cout << P_Prime[0] << std::endl << P_Prime[1] << std::endl;
    return 0;
}
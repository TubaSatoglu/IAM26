#include <iostream>
#include <fstream>
#include <cmath>

int main() {
    std::ifstream fin1("sums.txt");

    double a;
    double sum = 0.0;
    int n = 0;
    while (fin1 >> a) {
        sum += a;
        ++n;
    }
    fin1.close();

    double mean = sum / n;
    std::cout << "Mean: " << mean << std::endl;

    std::ifstream fin2("sums.txt");
    double sum_sq_diff = 0.0;
    while (fin2 >> a) {
        double diff = a - mean;
        sum_sq_diff += diff * diff;
    }
    fin2.close();

    double variance = sum_sq_diff / n;
    std::cout << "Variance: " << variance << std::endl;

    double std_dev = std::sqrt(variance);
    std::cout << "Standard deviation: " << std_dev << std::endl;

    return 0;
}
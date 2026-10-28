#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

int main() {
    std::ifstream fin("sums.txt");
    std::vector<double> numbers;
    double val;
    while (fin >> val) {
        numbers.push_back(val);
    }
    fin.close();

    std::ofstream fmeans("means.txt");
    std::ofstream fvars("variances.txt");

    int chunk_size = 9;
    int total_elements = numbers.size();

    for (int i = 0; i <= total_elements - chunk_size; i += chunk_size) {
        double sum = 0.0;
        for (int j = 0; j < chunk_size; ++j) {
            sum += numbers[i + j];
        }
        double mean = sum / chunk_size;

        double sum_sq_diff = 0.0;
        for (int j = 0; j < chunk_size; ++j) {
            double diff = numbers[i + j] - mean;
            sum_sq_diff += diff * diff;
        }
        double variance = sum_sq_diff / chunk_size;

        fmeans << mean << std::endl;
        fvars << variance << std::endl;
    }

    fmeans.close();
    fvars.close();
    return 0;
}
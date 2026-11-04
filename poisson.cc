
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

double poisson(double mu, int k) {
    return (std::pow(mu, k) * std::exp(-mu)) / std::tgamma(k + 1);
}

int main() {
    std::vector<int> counts(11);
    std::ifstream fin("sums.txt");

    int N = 0;
    double sum = 0;
    int number;

    while(fin >> number) {
        sum += number;
        N += 1;
        counts.at(number) += 1;
    }
    
    double mean = sum / N;
    std::cout << "N = " << N << ", Mean: " << mean << std::endl;

    for(unsigned int k = 0 ; k < counts . size () ; ++ k) {
        std::cout << k << ":" << counts [k] << std :: endl ;
    }

    std::ofstream hist("hist.txt");
    std::ofstream histpoi("histpoi.txt");
    for(unsigned int k = 0 ; k < counts . size () ; ++ k) {
        hist << k << " " << counts[k] << std :: endl ;
        histpoi << k << " " << counts[k] << " " << N * poisson(mean, k) << std :: endl ;
    }
    fin.close();
    return 0;
}
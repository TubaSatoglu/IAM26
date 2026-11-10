#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

double poisson(int k, double mu) {
    return (std::pow(mu, k) * std::exp(-mu)) / std::tgamma(k + 1);
}

double prob(const std::vector<int>& data, double mu) {
    double L = 1;
    for (int k : data) {
        L *= poisson(k, mu);
    }
    return L;
}

double nll(const std::vector<int>& data, double mu) {
    double sum = 0;
    for (int k : data) {
        sum += -2 * std::log(poisson(k, mu));
    }
    return sum;
}

int main() {
    std::vector<int> data;
    std::ifstream fin("sums.txt");

    int N = 0;
    double sum = 0;
    int number;

    while (fin >> number) {
        N += 1;
        sum += number;
        data.push_back(number);
    }
    fin.close();

    double mean = sum / N;
    std::cout << "N = " << N << ", Mean: " << mean << std::endl;
    std::cout << "L(mean) = " << prob(data, mean) << std::endl;

    std::ofstream flike("likelihood.txt");
    for (int i = 0; i <= 600; ++i) {
        double mu = i * 0.01;
        flike << mu << " " << prob(data, mu) << std::endl;
    }
    flike.close();

    std::ofstream fnll("nll.txt");
    for (int i = 0; i <= 600; ++i) {
        double mu = i * 0.01;
        fnll << mu << " " << nll(data, mu) << std::endl;
    }
    fnll.close();

    double nllmin = nll(data, mean);
    std::ofstream fdelta("deltanll.txt");
    for (int i = 0; i <= 600; ++i) {
        double mu = i * 0.01;
        fdelta << mu << " " << nll(data, mu) - nllmin << std::endl;
    }
    fdelta.close();

    double muhat = mean;
    double dmin = 1e300;
    double lower = 0;
    double upper = 0;
    for (int i = 0; i <= 100000; ++i) {
        double mu = mean - 0.5 + i * 0.00001;
        double delta = nll(data, mu) - nllmin;
        if (delta < dmin) {
            dmin = delta;
            muhat = mu;
        }
        if (delta < 1 && lower == 0) {
            lower = mu;
        }
        if (delta < 1) {
            upper = mu;
        }
    }
    std::cout << "mu_hat = " << muhat << std::endl;
    std::cout << "Interval: [" << lower << ", " << upper << "]" << std::endl;
    std::cout << "Uncertainty: -" << muhat - lower << " +" << upper - muhat << std::endl;

    double var = 0;
    for (int k : data) {
        var += (k - mean) * (k - mean);
    }
    double sigma = std::sqrt(var / (N - 1));
    std::cout << "sigma/sqrt(N) = " << sigma / std::sqrt(N) << std::endl;
    std::cout << "sqrt(mu_hat/N) = " << std::sqrt(muhat / N) << std::endl;

    double nllsat = 0;
    for (int k : data) {
        nllsat += -2 * std::log(poisson(k, k));
    }
    double lambda = nll(data, mean) - nllsat;
    int ndof = N - 1;
    double z = (lambda - ndof) / std::sqrt(2.0 * ndof);
    std::cout << "-2 ln Lambda = " << lambda << std::endl;
    std::cout << "z = " << z << std::endl;
    std::cout << "z (simulation) = " << (lambda - 254) / 24 << std::endl;

    return 0;
}

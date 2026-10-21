
#include <iostream>
#include <fstream>

int main() {
    std::ifstream fin("data.txt");

    int num1, num2;
    for (int i = 0; i < 234; ++i) {
        if (fin >> num1 >> num2) {
            int sum = num1 + num2;
            fout << sum << std::endl;
        }
    }

    fin.close();
    std::ofstream fout("sums.txt");

    return 0;
}
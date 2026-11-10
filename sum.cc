
#include <iostream>
#include <fstream>

int main() {
    std::ifstream fin("data.txt");
    std::ofstream fout("sums.txt");

    int a;
    int b;
    for (int i = 0; i < 234; ++i) {
        fin >> a >> b;
        fout << a + b << std::endl;
    }

    fin.close();
    fout.close();
    return 0;
}
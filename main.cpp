#include "template.h"

void partA();
void partB();

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(12);
    cout << setprecision(12);
    freopen("./input.txt","r",stdin);
    using namespace chrono;
    auto start = high_resolution_clock::now();
    argv[1][0] == 'A' ? partA() : partB();
    auto end = high_resolution_clock::now();
    cout << duration_cast<microseconds>(end - start).count() << "us" << endl;
}
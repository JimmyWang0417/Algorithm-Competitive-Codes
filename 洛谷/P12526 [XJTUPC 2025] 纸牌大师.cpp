#include <iostream>
using namespace std;

int main() {
    int a1, a2, a3;
    cin >> a1 >> a2 >> a3;
    int sum = a1 + a2 + a3;
    if (a1 == a2 && a2 == a3) {
        sum += 100;
    }
    cout << sum << endl;
    return 0;
}
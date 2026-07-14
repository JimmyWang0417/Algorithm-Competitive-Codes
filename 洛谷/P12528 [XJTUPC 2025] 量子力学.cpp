#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    int size = 1 << n;
    vector<double> prob0(n, 0.0);
    vector<double> prob1(n, 0.0);
    
    for (int i = 0; i < size; ++i) {
        double a, b;
        cin >> a >> b;
        double p = a * a + b * b;
        
        for (int j = 0; j < n; ++j) {
            if ((i >> j) & 1) {
                prob1[j] += p;
            } else {
                prob0[j] += p;
            }
        }
    }
    
    cout.precision(8);
    cout << fixed;
    for (int i = 0; i < n; ++i) {
        cout << prob0[i] << ' ' << prob1[i] << '\n';
    }
    
    return 0;
}
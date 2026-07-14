#include <iostream>
using namespace std;

long long mod(long long x, long long m) {
    return (x % m + m) % m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long a, c, p;
    cin >> a >> c >> p;
    
    long long a_mod_p = mod(a, p);
    long long delta = mod(c - a_mod_p, p);
    
    // 计算b的表达式：b = (p-1)*delta + c
    long long b = (p - 1) * delta + c;
    
    // 确保b >= 1
    while (b < 1) {
        b += (p - 1) * p;
    }
    
    cout << b << endl;
    
    return 0;
}
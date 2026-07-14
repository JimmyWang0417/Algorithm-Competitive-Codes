#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    cin >> s;
    int n = s.size();
    long long steps = 0;
    
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'H') {
            steps += (n - i);
        }
        // F状态会立刻流光，相当于空，E也是空
    }
    
    if (steps % 2 == 1) {
        cout << "Alice" << '\n';
    } else {
        cout << "Bob" << '\n';
    }
    
    return 0;
}
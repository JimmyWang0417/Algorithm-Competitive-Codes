#include <bits/stdc++.h>
using namespace std;

using ai3 = array<int, 3>;

struct Main {
    int n;
    vector<int> p;
    vector<int> a;
    void main() {
        cin >> n;
        p.resize(n + 5);
        for (int i = 1; i <= n; ++i) {
            cin >> p[i];
        }
        a.resize(n + 5);
        vector<int> dp(n + 5);
        dp[1] = 1;
        for (int i = 1, j = 1; i <= n; i = j) {
            while (j <= n && p[i] == p[j])
                ++j;
            for (int k = i; k < j; ++k)
                a[k] = i;
        }
        for (int i = 2; i <= n; ++i) {
            
        }
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) Main{}.main();
    return 0;
}
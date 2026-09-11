#include <bits/stdc++.h>
using namespace std;

using ai3 = array<int, 3>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    int res = 0;
    int las = 0;
    for (int i = 0; i < n; ++i) {
        int now = 0;
        for (int j = 0; j < m; ++j) {
            int x;
            cin >> x;
            now += x;
        }
        res += (las > now);
        las = now;
    }
    cout << res << '\n';
    return 0;
}
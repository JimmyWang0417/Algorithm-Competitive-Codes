#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #define dbg(...) fprintf(stderr, ##__VA_ARGS__)
#else
    #define dbg(...) 42
#endif

#define all(x) (x).begin(), (x).end()
using LL = long long;

#define NO return void(cout << "NO\n")
struct Main {
    int n, m;
    string s;
    void main() {
        cin >> n >> m >> s;
        int X = (s[0] - '0') * 10 + (s[1] - '0');
        int Y = (s[3] - '0') * 10 + (s[4] - '0');
        if (m >= 50 || m * 5 >= n || X * 60 + Y >= 240)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
};

int main() {
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    int T = 1;
    cin >> T;
    while (T--)
    Main{}.main();
    return 0;
}

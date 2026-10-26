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
    LL n;
    void main() {
        cin >> n;
        if (n % 2)
        {
            cout << "-1\n";
        }
        else
        {
            cout << "1 -1 " << n / 2 << '\n';
        }
    }
};

int main() {
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    int T = 1;
    // cin >> T;
    while (T--)
    Main{}.main();
    return 0;
}

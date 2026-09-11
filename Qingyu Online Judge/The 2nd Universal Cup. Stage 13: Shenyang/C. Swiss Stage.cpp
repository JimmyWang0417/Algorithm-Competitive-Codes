#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include <local/dbg.h>
#else
    #define dbg(...) 42
#endif

using LL = long long;

// clang-format off
#define ai(x) using ai##x = array<int, x>;
ai(2); ai(3); ai(4); ai(5); ai(6); ai(7); ai(8); ai(9); ai(10); ai(26);
#undef ai
// clang-format on

#define all(x) (x).begin(), (x).end()
#define allr(x) (x).rbegin(), (x).rend()
template <class T>
inline bool updmx(T &x, const T &y) { return x < y ? x = y, 1 : 0; }
template <class T>
inline bool updmn(T &x, const T &y) { return y < x ? x = y, 1 : 0; }
template <class T>
inline void clr(T &x) { T().swap(x); }
template <class T>
inline void sortuniq(T &x) {
    sort(all(x));
    x.erase(unique(all(x)), x.end());
}

mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());
LL rand(LL l, LL r) { return rng() % (r - l + 1) + l; }

struct Main {
    void main() {
        int x, y;
        cin >> x >> y;
        assert(0 <= x && x <= 2);
        assert(0 <= y && y <= 2);
        cout << dfs(x, y) << "\n";
    }
    int dfs(const int x, const int y) const {
        if (x >= 3) return 0;
        int add = 0;
        if (x == 0) {
            if (y == 0)
                add = 1;
            else if (y == 1)
                add = 1;
            else // y == 2
                add = 2;
        } else if (x == 1) {
            if (y == 0)
                add = 1;
            else if (y == 1)
                add = 1;
            else // y == 2
                add = 2;
        } else { // x == 2
            add = 2;
        }
        return add + dfs(x + 1, y);
    }
};
int main() {
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    Main{}.main();
    return 0;
}
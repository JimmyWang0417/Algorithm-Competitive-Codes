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

using ALH = array<int, 2>; // array-LL-Hash
namespace HC { // Hash Const
    constexpr int N = 1e5;
    constexpr int P[2] = {13331, 233};
    constexpr int MOD[2] = {(int)(1e9 + 7), 998244353};
    LL ksm[N][2];
    const bool init = []() -> bool {
        for (int j = 0; j < 2; j++) {
            ksm[0][j] = 1;
            for (int i = 1; i < N; i++) {
                ksm[i][j] = (1ll * ksm[i - 1][j] * P[j]) % MOD[j];
            }
        }
        return 1;
    }();
} // namespace HC
class Hash {
private:
    vector<ALH> h;

public:
    Hash() {}
    Hash(const char *s, int n) {
        init(s, n);
    }
    void init(const char *s, int n) { // s stores at pos [1,n], and just give para s (NOT s+1)
        h.resize(n + 2);
        for (int j = 0; j < 2; j++) {
            h[0][j] = 0;
            for (int i = 1; i <= n; i++) {
                h[i][j] = (1ll * h[i - 1][j] * HC::P[j] + s[i] - 'a' + 1) % HC::MOD[j];
            }
        }
    }
    ALH calc(const int l, const int r) {
        static ALH ret;
        for (int j = 0; j < 2; j++) {
            ret[j] = (1ll * h[r][j] - 1ll * h[l - 1][j] * HC::ksm[r - l + 1][j]) % HC::MOD[j];
        }
        for (int j = 0; j < 2; j++) {
            if (ret[j] < 0) ret[j] += HC::MOD[j];
        }
        return ret;
    }
};

void calc_dp(const string_view s, auto &&dp) {
    const int n = int(s.size()) - 1;
    dp.assign(n + 1, vector<int>(n + 1, 0));
    for (int len = n; len >= 2; --len) {
        for (int r = len; r <= n; ++r) {
            const int l = r - len + 1;
            if (s[l] == s[r]) {
                dp[l][r] = 1;
                if (l > 1 && s[l - 1] == s[r - 1]) {
                    dp[l][r] += dp[l - 1][r - 1];
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            dp[i][j] = 0;
        }
        for (int j = i + 1; j <= n; ++j) {
            updmn(dp[i][j], j - i - 1);
        }
    }
}

template <bool _>
void calc_cnt(auto &&dp, auto &&cnt, const int n) {
    cnt.assign(n + 1, vector<LL>(n + 1, 0));
    for (int i = 1; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            ++cnt[i + 1][j - dp[i][j]];
            --cnt[i + 1][j];
        }
    }
    for (int i = 1; i <= n; ++i) {
        if constexpr (_) ++cnt[i][i];
        for (int j = i; j <= n; ++j) {
            cnt[i][j] += cnt[i][j - 1];
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            cnt[i][j] += cnt[i][j - 1];
        }
    }
}

struct Main {
    string s, t;
    int n, m;
    vector<vector<int>> dp;
    vector<vector<LL>> cnts, cntt; // ?????
    Hash hs, ht;
    LL ans = 0;
    void main() {
        cin >> s >> t;
        n = int(s.size());
        m = int(t.size());
        s = "$" + s;
        t = "$" + t;
        calc_dp(s, dp);
        calc_cnt<1>(dp, cnts, n);
        calc_dp(t, dp);
        calc_cnt<0>(dp, cntt, m);
#ifdef LOCAL
        dbg("dps");
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j < i; ++j) cerr << "  ";
            for (int j = i; j <= n; ++j) {
                cerr << dps[i][j] << " \n"[j == n];
            }
        }
        dbg("cnts");
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j < i; ++j) cerr << "  ";
            for (int j = i; j <= n; ++j) {
                cerr << cnts[i][j] << " \n"[j == n];
            }
        }
        dbg("dpt");
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j < i; ++j) cerr << "  ";
            for (int j = i; j <= m; ++j) {
                cerr << dpt[i][j] << " \n"[j == m];
            }
        }
        dbg("cntt");
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j < i; ++j) cerr << "  ";
            for (int j = i; j <= m; ++j) {
                cerr << cntt[i][j] << " \n"[j == m];
            }
        }
#endif
        hs.init(s.c_str(), n);
        ht.init(t.c_str(), m);
        dp.assign(n + 1, vector<int>(m + 1, 0));
        for (int i = n; i > 0; --i) {
            for (int j = m; j > 0; --j) {
                if (s[i] != t[j]) continue;
                dp[i][j] = 1;
                if (i < n && j < m) {
                    dp[i][j] += dp[i + 1][j + 1];
                }
                const int l = dp[i][j];
                ans += cnts[i][i + l - 1] + cntt[j][j + l - 1];
            }
        }
        cout << ans << "\n";
    }
};
int main() {
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    Main{}.main();
    return 0;
}
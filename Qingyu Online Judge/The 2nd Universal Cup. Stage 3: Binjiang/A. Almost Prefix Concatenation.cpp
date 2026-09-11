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

#define D constexpr MI
#define C const
#define O operator
template <unsigned int mod>
struct MI {
    D() : v(0) {}
    template <typename T>
    D(T x) : v(x % mod) {
        if (v < 0) v += mod;
    }
    template <typename T>
    static D raw(T x) {
        MI z;
        z.v = x;
        return z;
    }
    D pow(LL n) C {
        MI x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    D inv() C { return pow(mod - 2); }
    D &O += (C MI & x) {
        if (unsigned(v += x.v) >= mod) v -= mod;
        return *this;
    }
    D &O -= (C MI & x) {
        if ((v -= x.v) < 0) v += mod;
        return *this;
    }
    D &O *= (C MI & x) {
        LL z = v;
        z *= x.v;
        v = z % mod;
        return *this;
    }
    D &O /= (C MI & x) { return *this = *this * x.inv(); }
    constexpr int val() C { return v; }
    static constexpr unsigned int umod() { return mod; }
    friend constexpr bool O == (C MI & x, C MI &y) { return x.val() == y.val(); }
#define OP(s, t) \
    friend D O s(C MI &x, C MI &y) { return MI(x) t y; }
    OP(+, +=)
    OP(-, -=)
    OP(*, *=)
    OP(/, /=)
#undef OP
    friend ostream &operator<<(ostream &o, C MI x) {
        o << x.val();
        return o;
    }

private:
    int v;
};
#undef D
#undef C
#undef O

using Z = MI<998244353>;
#define raw(x) Z::raw(x)

using ALH = array<LL, 2>; // array-LL-Hash
namespace HC { // Hash Const
    constexpr int N = int(1e6) + 5;
    constexpr int P[2] = {13331, 233};
    constexpr int MOD[2] = {(int)(1e9 + 7), 998244353};
    LL ksm[N][2];
    const bool init = []() -> bool {
        for (int j = 0; j < 2; j++) {
            ksm[0][j] = 1;
            for (int i = 1; i < N; i++) {
                ksm[i][j] = (ksm[i - 1][j] * P[j]) % MOD[j];
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
                h[i][j] = (h[i - 1][j] * HC::P[j] + s[i - 1] - 'a' + 1) % HC::MOD[j];
            }
        }
    }
    ALH calc(const int l, const int r) {
        static ALH ret;
        for (int j = 0; j < 2; j++) {
            ret[j] = h[r][j] - h[l - 1][j] * HC::ksm[r - l + 1][j];
        }
        for (int j = 0; j < 2; j++) {
            ret[j] = (ret[j] % HC::MOD[j] + HC::MOD[j]) % HC::MOD[j];
        }
        return ret;
    }
};

struct Main {
    string s, t;
    Hash hs, ht;
    vector<int> R;
    int n, m;
    vector<Z> dp, sum, cnt;
    void main() {
        cin >> s >> t;
        n = int(s.size()), m = int(t.size());
        hs.init(s.c_str(), n);
        ht.init(t.c_str(), m);
        R.assign(n + 1, 0);
        for (int l = 1; l <= n; ++l) {
            R[l] = l + calc(l) - 1;
        }
        dbg(R | views::drop(1));
        dp.assign(n + 2, 0);
        sum.assign(n + 2, 0);
        cnt.assign(n + 2, 0);
        dp[1] = sum[1] = cnt[1] = 1;
        dp[R[1] + 1] = sum[R[1] + 1] = cnt[R[1] + 1] = Z(0) - Z(1);
        dbg(R[1] + 1, dp[R[1] + 1]);
        for (int i = 2; i <= n; ++i) {
            const int j = R[i] + 1;
            dbg(i, j);
            dp[i] += dp[i - 1] + dp[i - 1] + sum[i - 1] * 2 + cnt[i - 1];
            sum[i] += sum[i - 1] + sum[i - 1] + cnt[i - 1];
            cnt[i] += cnt[i - 1] + cnt[i - 1];
            dp[j] -= dp[i - 1] + sum[i - 1] * 2 + cnt[i - 1];
            sum[j] -= sum[i - 1] + cnt[i - 1];
            cnt[j] -= cnt[i - 1];
        }
        dbg(dp | views::drop(1));
        dbg(sum | views::drop(1));
        dbg(cnt | views::drop(1));
        cout << dp[n].val() << "\n";
    }
    int calc(const int i) { // return len
        const int lim = min(n - i + 1, m);
        int l = 1, r = lim, ans = 0;
        while (l <= r) {
            const int mid = (l + r) >> 1;
            if (hs.calc(i, i + mid - 1) == ht.calc(1, mid)) {
                ans = mid;
                l = mid + 1;
            } else
                r = mid - 1;
        }
        ans = min(ans + 1, lim);
        if (ans == lim) return ans;
        l = 1, r = lim - ans;
        int opt = 0;
        while (l <= r) {
            const int mid = (l + r) >> 1;
            if (hs.calc(i + ans, i + ans + mid - 1) == ht.calc(ans + 1, ans + mid)) {
                opt = mid;
                l = mid + 1;
            } else
                r = mid - 1;
        }
        return ans + opt;
    }
};
int main() {
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    Main{}.main();
    return 0;
}
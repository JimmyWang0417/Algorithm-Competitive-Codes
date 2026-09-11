#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include <local/dbg.h>
#else
    #define dbg(...) 42
#endif

using LL = long long;
using ai3 = array<int, 3>;
using ai26 = array<int, 26>;

template <class T>
inline bool updmx(T &x, const T y) {
    if (x < y) {
        x = y;
        return 1;
    }
    return 0;
}

struct Trie {
    vector<ai26> trie;
    vector<int> cnt;
    Trie() {}
    void init(const int n) {
        trie.assign(1, {});
        cnt.assign(1, 0);
        trie.reserve(n);
        cnt.reserve(n);
    }
    void insert(const string_view s, auto &&buc) {
        int p = 0;
        for (int len = 1; auto c : s) {
            const int i = c - 'a';
            if (!trie[p][i]) {
                trie[p][i] = int(trie.size());
                trie.push_back({});
                cnt.push_back(0);
            }
            ++cnt[p = trie[p][i]];
            updmx(buc[len], cnt[p]);
            ++len;
        }
    }
};

struct Main {
    int n, len_mx = 0;
    vector<string> s;
    Trie trie;
    vector<int> buc;
    static constexpr int B = 19;
    array<vector<int>, B> pre_bit;
    LL ans = 0;
    void main() {
        cin >> n;
        init_bit();
        s.assign(n, "");
        int tot = 0;
        for (auto &t : s) {
            cin >> t;
            tot += int(t.size());
            if (int(t.size()) > len_mx) len_mx = int(t.size());
        }
        trie.init(tot + 1);
        buc.assign(len_mx + 1, 0);
        for (int i = 1; const string_view t : s) {
            ans -= calc(int(t.size()));
            trie.insert(t, buc);
            buc[0] = i;
            ans += calc(int(t.size()));
            cout << ans << "\n";
            ++i;
            dbg(i, buc);
        }
    }
    LL calc(const int r) const {
        int nw = r < len_mx ? buc[r + 1] : 0;
        LL res = 0;
        for (int i = r; i >= 0; --i) {
            res += calc(i, nw + 1, buc[i]);
            nw = buc[i];
        }
        return res;
    }
    LL calc(const int x, const int l, const int r) const {
        dbg(x, l, r);
        if (l > r) return 0ll;
        LL res = 0;
        for (int p = 0; p < B; ++p) {
            const int c1 = pre_bit[p][r] - pre_bit[p][l - 1];
            const int c0 = (r - l + 1) - c1;
            if (x >> p & 1)
                res += 1ll * (1ll << p) * c0;
            else
                res += 1ll * (1ll << p) * c1;
        }
        return res;
    }
    void init_bit() {
        for (int p = 0; p < B; ++p) {
            pre_bit[p].assign(n + 1, 0);
            for (int i = 1; i <= n; ++i) {
                pre_bit[p][i] = pre_bit[p][i - 1] + (i >> p & 1);
            }
        }
    }
};

int main() {
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    Main{}.main();
    return 0;
}
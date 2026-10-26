#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
constexpr int mod = 998244353;
struct SG
{
    vector<int> sg;
    SG(int n) : sg(n + 5)
    {
        sg[0] = sg[1] = 0;
        int maxx = 0;
        for (int i = 2; i <= n; ++i)
        {
            vector<bool> vis(maxx * 2 + 5);
            for (int j = 0; j <= i - 2; ++j)
                vis[sg[j] ^ sg[i - 2 - j]] = true;
            while (vis[sg[i]])
                ++sg[i];
            maxx = max(maxx, sg[i]);
        }
    }
    auto find(int x)
    {
        if (x <= 60)
            return sg[x];
        else
            return sg[(x - 60) % 34 + 60];
    }
} sg(100);
struct Main
{
    mt19937_64 rng;
    Main(u64 _key = chrono::steady_clock::now().time_since_epoch().count()) : rng(_key)
    {
        int n, m;
        cin >> n >> m;
        vector<u128> rnd(m);
        for (auto &i : rnd)
            i = (u128(rng()) << 64) | rng();
        vector<pair<int, int>> p(2 * m);
        for (int i = 0; i < m; ++i)
        {
            int x, y;
            cin >> x >> y;
            p[i * 2] = {x, i};
            p[i * 2 + 1] = {y, i};
        }
        sort(p.begin(), p.end());
        map<u128, int> mp;
        {
            int cur = 0;
            u128 now = 0;
            vector<bool> in(m);
            for (auto [x, id] : p)
            {
                mp[now] += x - cur;
                cur = x + 1;
                if (in[id])
                    now -= rnd[id];
                else
                    now += rnd[id];
                in[id] = !in[id];
            }
            mp[now] += n - cur;
        }
        int res = 0;
        for (auto [_, v] : mp)
            res ^= sg.find(v);
        cout << (res ? "YES" : "NO") << '\n';
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main(T);
    return 0;
}

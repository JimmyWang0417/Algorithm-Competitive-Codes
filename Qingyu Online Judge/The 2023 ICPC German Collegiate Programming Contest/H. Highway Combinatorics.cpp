#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 1e5 + 5;
constexpr int mod = 1e9 + 7;
auto quickpow(ll a, int b)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}
unordered_map<int, vector<int>> mp;
auto _main()
{
    int n;
    cin >> n;
    if (n == 0)
    {
        cout << "##.\n.##\n";
        return;
    }
    vector<int> f = {1, 1};
    for (int i = 2; i <= 200; ++i)
        f.push_back((f[i - 1] + f[i - 2]) % mod);
    function<void(int, int, int, vector<int>)> dfs = [&](int las, int mul, int len, vector<int> p)
    {
        if (mp[mul].empty())
            mp[mul] = p;
        else
            return;
        for (int i = las; len + i + 1 <= 83; ++i)
        {
            vector<int> q = p;
            q.push_back(i);
            dfs(i, (int)((ll)f[i] * mul % mod), len + i + 1, q);
        }
    };
    dfs(2, 1, 0, {});
    for (auto [u, v] : mp)
    {
        int where = (int)(n * quickpow(u, mod - 2) % mod);
        if (mp.find(where) != mp.end())
        {
            string answer;
            for (auto i : v)
            {
                for (int j = 0; j < i; ++j)
                    answer.push_back('.');
                answer.push_back('#');
            }
            for (auto i : mp[where])
            {
                for (int j = 0; j < i; ++j)
                    answer.push_back('.');
                answer.push_back('#');
            }
            cout << answer << '\n' << answer << '\n';
            return;
        }
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas)
        _main();
    return 0;
}

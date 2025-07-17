#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
constexpr int N = 1e6 + 5;
int prime[N], tot;
bool not_prime[N];
int prod[N], omega[N];
int fa[N];
inline int find(int x)
{
    return !fa[x] ? x : fa[x] = find(fa[x]);
}
inline void init(int n = N - 5)
{
    for (int i = 2; i <= n; ++i)
    {
        if (!not_prime[i])
        {
            prime[++tot] = i;
            prod[i] = i, omega[i] = 1;
        }
        for (int j = 1; j <= tot; ++j)
        {
            if (i * prime[j] > n)
                break;
            not_prime[i * prime[j]] = true;
            if (i % prime[j])
            {
                prod[i * prime[j]] = prod[i] * prime[j];
                omega[i * prime[j]] = omega[i] + 1;
            }
            else
            {
                prod[i * prime[j]] = prod[i];
                omega[i * prime[j]] = omega[i];
            }
        }
    }
}
int cnt[N];
vector<int> g[N];
vector<pair<int, int>> edge[N];
inline void work()
{
    int l, r;
    cin >> l >> r;
    if (l == 1)
    {
        int answer = 0;
        for (int i = l; i <= r; ++i)
            answer += omega[i];
        cout << answer << '\n';
        return;
    }
    int root = 0;
    for (int i = l; i <= r; ++i)
        if (!not_prime[i])
        {
            root = i;
            break;
        }
    auto solve1 = [l, r]()
    {
        for (int i = l; i <= r; ++i)
            for (int j = i + 1; j <= r; ++j)
                edge[omega[i] + omega[j] - omega[__gcd(i, j)]].emplace_back(i, j);
    };
    auto solve2 = [l, r]()
    {
        for (int i = l; i <= r; ++i)
            ++cnt[prod[i]];
        for (int i = 1; i <= r; ++i)
            if (cnt[i])
            {
                g[omega[i]].push_back(i);
                for (int j = i << 1; j <= r; j += i)
                    if (cnt[j])
                        edge[omega[j]].emplace_back(i, j);
            }
    };
    int answer = 0;
    auto merge = [](int x, int y)
    {
        x = find(x), y = find(y);
        if (x == y)
            return false;
        fa[x] = y;
        return true;
    };
    if (root)
        solve2();
    else
        solve1();
    for (int now = 1; now < 20; ++now)
    {
        int qwq = 0;
        for (int u : g[now])
            answer += (cnt[u] - 1) * now;
        for (auto [u, v] : edge[now])
            answer += merge(u, v) * now;
        for (int u : g[now])
            answer += merge(root, u) * (now + 1);
        edge[now].clear();
        g[now].clear();
    }
    for (int i = 1; i <= r; ++i)
        fa[i] = cnt[i] = 0;
    cout << answer << '\n';
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    init();
    int T = 1;
    cin >> T;
    while (T--)
        work();
    return 0;
}
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
constexpr int mod = 998244353;
template <typename T>
auto &operator<<(ostream &in, const vector<T> &rhs)
{
    for (auto i : rhs)
        in << i << ' ';
    return in;
}
struct Main
{
    int n;
    vector<int> in, a;
    Main()
    {
        cin >> n;
        a.resize(n + 5);
        in.resize(n + 5);
        for (int i = 1; i <= n; ++i)
        {
            cin >> a[i];
            ++in[a[i]];
        }
        vector<bool> pick(n + 5, true);
        queue<int> q;
        for (int i = 1; i <= n; ++i)
            if (!in[i])
                q.push(i);
        int res = 0;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            res += pick[u];
            int v = a[u];
            if (pick[u])
                pick[v] = false;
            if (!--in[v])
                q.push(v);
        }
        for (int i = 1; i <= n; ++i)
        {
            if (in[i] && !pick[i])
                q.push(i);
        }
        vector<bool> vis(n + 5);
        while (!q.empty())
        {
            int cnt = 0;
            vis[q.front()] = true;
            for (int i = a[q.front()]; pick[i]; i = a[i])
            {
                vis[i] = true;
                ++cnt;
            }
            res += (cnt + 1) / 2;
            q.pop();
        }
        for (int i = 1; i <= n; ++i)
            if (in[i])
            {
                int cnt = 0;
                for (int j = i; !vis[j]; j = a[j])
                {
                    ++cnt;
                    vis[j] = true;
                }
                res += cnt / 2;
            }
        cout << res << '\n';
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}


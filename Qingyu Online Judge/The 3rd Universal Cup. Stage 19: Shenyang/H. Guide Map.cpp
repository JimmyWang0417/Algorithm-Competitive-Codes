#include <iostream>

using namespace std;

constexpr int N = 2e5, mod = 998244353, phi = mod - 1;

int ft[N], ord[N], cd[N], ss[N], ans;
basic_string<int> nei[N];
bool vis[N];

auto &add(auto &&a, auto b)
{
    return a -= (a += b) >= mod ? mod : 0;
}
auto &mul(auto &&a, auto b)
{
    return a = a * 1ull * b % mod;
}
int pw(auto b)
{
    int r = 1, a = 2;

    for (; b; b /= 2, mul(a, a))
        if (b % 2)
            mul(r, a);

    return r;
}
void walk(int v, int p)
{
    vis[v] = 1;

    for (auto u : nei[v])
        if (u != p)
            walk(u, v);
}
void inc(int i)
{
    for (i = N - i - 1; i < N; i |= i + 1)
        ++ft[i];
}
int que(int i)
{
    int x = 0;

    for (i = N - i - 1; i; i &= i - 1)
        x += ft[i - 1];

    return x;
}

void down(int v, int p)
{
    int t;
    cd[v] -= t = que(v), inc(v);

    for (auto u : nei[v])
        if (u != p)
            down(u, v), (ss[v] += ss[u] + cd[u]) %= phi, cd[u] -= t, cd[u] += t = que(v);

    cd[v] += t;
}

void up(int v, int p)
{
    for (auto u : nei[v])
        if (u != p)
            ss[u] = (ord[v] + ss[v] + phi - cd[u]) % phi, up(u, v);
}

void solve(int v, int p, int64_t cur)
{
    add(ans, pw(cur));

    for (auto u : nei[v])
        if (u != p)
            solve(u, v, cur + ord[u]);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, r, c = 0;
    cin >> n;

    for (int i = 2, a, b; i < n; ++i)
        cin >> a >> b, nei[--a].push_back(--b), nei[b].push_back(a);

    walk(0, 0);

    for (int i = n; --i;)
        ord[i - 1] = ord[i] + !vis[i], r = vis[i] ? r : i;

    down(0, 0);
    down(r, r);
    up(r, r);

    for (int i = n; i--;)
        if (!vis[i])
            add(c, pw(ord[i] + ss[i] + ss[0]));

    solve(0, 0, 0);
    cout << add(mul(ans, c), (ord[0] == 1) * pw(ss[0])) << '\n';
}
#include <bits/stdc++.h>
using namespace std;

#define ONLINE
#ifndef ONLINE
char DEBUG_BUFFER[1000];
#define debug(...)                                                        \
    {                                                                     \
        sprintf(DEBUG_BUFFER, ##__VA_ARGS__);                             \
        cerr << "\033[1;36m" << DEBUG_BUFFER << "\033[0;2m" << "\033[0m"; \
    }
#else
#define debug(...) ;
#endif

using LL = long long;
using PII = pair<int, int>;

#define all(x) (x).begin(), (x).end()
#define allr(x) (x).rbegin(), (x).rend()

#define FAST_IO                      \
    {                                \
        ios::sync_with_stdio(false); \
        cin.tie(nullptr);            \
    }
inline int read()
{
    static int x;
    cin >> x;
    return x;
}
inline LL readLL()
{
    static LL x;
    cin >> x;
    return x;
}
mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());

using LD = long double;
const LD eps = 1e-6;

bool sign(const LD &x)
{
    return !(fabs(x) < eps);
}

LD calc(const vector<LD> &a)
{
    return sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
}

int cnt = 0;
void dfs(const vector<LD> &a, stringstream &ans)
{
    vector<int> vec{255, 255, 255};
    vector<LD> add(3);
    LD lambda = 1e9;
    bool ok = 0;
    for (int i = 0; i < 3; i++)
    {
        if (sign(a[i]))
        {
            if (sign(-a[i] + 255))
            {
                add[i] = -a[i] + 255;
                lambda = fmin(lambda, a[i] / add[i]);
                ok = 1;
            }
            else
                add[i] = 0.0;
        }
        else
            add[i] = vec[i] = 0;
    }
    if (!ok)
    {
        lambda = 1.0;
        for (int i = 0; i < 3; i++)
            add[i] = vec[i];
    }
    debug("lambda-%.6Lf\n", lambda);
    vector<LD> b = a;
    for (int i = 0; i < 3; i++)
    {
        b[i] -= lambda * add[i];
    }
    bool _ = 0;
    for (int i = 0; i < 3; i++)
    {
        _ |= sign(b[i]);
    }
    if (_)
        dfs(b, ans);
    ++cnt;
    for (int i = 0; i < 3; i++)
    {
        ans << vec[i] << ' ';
    }
    debug("\n");
    debug("b\t{%.6Lf,%.6Lf,%.6Lf}\n", b[0], b[1], b[2]);
    debug("add_vec\t{%.6Lf,%.6Lf,%.6Lf}\n", add[0], add[1], add[2]);
    debug("l\t%.6Lf\n", lambda);
    debug("add\t{%.6Lf,%.6Lf,%.6Lf}\n", a[0] - b[0], a[1] - b[1], a[2] - b[2]);
    ans << fixed << setprecision(12) << calc({a[0] - b[0], a[1] - b[1], a[2] - b[2]}) << "\n";
}
void solve()
{
    stringstream ans;
    vector<int> a(3);
    cin >> a[0] >> a[1] >> a[2];
    vector<LD> b{a[0], a[1], a[2]};
    cnt = 0;
    dfs(b, ans);
    cout << cnt << "\n"
         << ans.str();
}

int main()
{
    FAST_IO;
    int T = 1;
    cin >> T; // remember this !!!!!!
    while (T--)
        solve();
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
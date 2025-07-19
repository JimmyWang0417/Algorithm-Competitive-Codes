#include <bits/stdc++.h>
using namespace std;

// #define ONLINE
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

int main()
{
    FAST_IO;
    int n = read();
    vector<string> s(n);
    vector t(n, vector<char>(n, 0));
    for (int i = 0; i < n; i++)
        cin >> s[i];
    string opt;
    for (int sum = 0; sum <= n * 2 - 2; sum++)
    {
        if (sum & 1)
        {
            for (int i = 0;; i++)
            {
                if (sum - i < 0)
                    break;
                if (i >= n || sum - i >= n)
                    continue;
                opt += s[i][sum - i];
            }
        }
        else
        {
            for (int j = 0;; j++)
            {
                if (sum - j < 0)
                    break;
                if (j >= n || sum - j >= n)
                    continue;
                opt += s[sum - j][j];
            }
        }
    }
    {
        int i = 0, j = 0, nw = 0;
        while (nw < opt.size() - 1)
        {
            while (j + 1 < n && !t[i][j + 1])
            {
                t[i][j] = opt[nw++];
                ++j;
            }
            while (i + 1 < n && !t[i + 1][j])
            {
                t[i][j] = opt[nw++];
                ++i;
            }
            while (j - 1 >= 0 && !t[i][j - 1])
            {
                t[i][j] = opt[nw++];
                --j;
            }
            while (i - 1 >= 0 && !t[i - 1][j])
            {
                t[i][j] = opt[nw++];
                --i;
            }
        }
        t[i][j] = opt[nw];
    }
    for (int i = 0; i < n; i++)
    {
        for (auto c : t[i])
            cout << c;
        cout << "\n";
    }
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
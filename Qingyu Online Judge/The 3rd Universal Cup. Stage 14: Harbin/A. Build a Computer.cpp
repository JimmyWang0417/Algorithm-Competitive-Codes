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

inline int get_bits(const int &x)
{
    for (int i = 25; i >= 0; i--)
    {
        if (x >> i & 1)
            return i + 1;
    }
}

#define N 1000010
int L, R;

vector<vector<PII>> e(3);
int New()
{
    int x = e.size();
    e.push_back({});
    return x;
}

vector<int> A;
void Construct(int x)
{
    while ((int)A.size() <= x)
    {
        int v = A.empty() ? 2 : A.back();
        int u = New();
        A.push_back(u);
        e[u].push_back({v, 0});
        e[u].push_back({v, 1});
    }
}

void fuckl(int u, int x, int p)
{
    for (; p >= 0; p--)
    {
        if (!(x >> p & 1))
        {
            Construct(p - 1);
            int v = p ? A[p - 1] : 2;
            e[u].push_back({v, 1});
        }
        int v = p ? New() : 2;
        e[u].push_back({v, x >> p & 1});
        u = v;
    }
}
void fuckr(int u, int x, int p)
{
    for (; p >= 0; p--)
    {
        if (x >> p & 1)
        {
            Construct(p - 1);
            int v = p ? A[p - 1] : 2;
            e[u].push_back({v, 0});
        }
        int v = p ? New() : 2;
        e[u].push_back({v, x >> p & 1});
        u = v;
    }
}

int main()
{
    //	freopen("A_output.txt","w",stdout);
    cin >> L >> R;
    if (L == 1 && R == 1)
    {
        printf("2\n1 2 1\n0\n");
        return 0;
    }
    if (L == 1)
    {
        e[1].push_back({2, 1});
        ++L;
    }
    int l = get_bits(L), r = get_bits(R);
    if (l == r)
    {
        if (L + 1 >= R)
        {
            int last = 1;
            for (int i = r - 1; i >= 0; i--)
            {
                int x = i ? New() : 2;
                e[last].push_back({x, L >> i & 1});
                last = x;
            }
            if (L != R)
            {
                last = 1;
                for (int i = r - 1; i >= 0; i--)
                {
                    int x = i ? New() : 2;
                    e[last].push_back({x, R >> i & 1});
                    last = x;
                }
            }
            goto OUTPUT;
        }
        int last = 1;
        for (int i = r - 1; i >= 0; i--)
        {
            if ((L >> i & 1) == (R >> i & 1))
            {
                int x = New();
                e[last].push_back({x, L >> i & 1});
                last = x;
            }
            else
            {
                int x = New();
                e[last].push_back({x, 0});
                fuckl(x, L, i - 1);
                x = New();
                e[last].push_back({x, 1});
                fuckr(x, R, i - 1);
                break;
            }
        }
        for (int i = 0; i < A.size(); i++)
        {
            debug("A[%d]=%d\n", i, A[i]);
        }
    }
    else
    {
        if (l + 1 < r)
        {
            vector<int> B;
            while ((int)B.size() <= r - 3)
            {
                int v = B.empty() ? 2 : B.back();
                int u = New();
                B.push_back(u);
                e[u].push_back({v, 0});
                e[u].push_back({v, 1});
            }
            e[1].push_back({B.back(), 1});
            for (int i = l + 1; i <= r - 2; i++)
            {
                debug("%d|B[%d]\n", i, r - i);
                e[B[r - i - 1]].push_back({2, 0});
                e[B[r - i - 1]].push_back({2, 1});
            }
            for (int i = 0; i <= r - 3; i++)
            {
                debug("B[%d]=%d\n", i, B[i]);
            }
        }
        int x = New();
        e[1].push_back({x, 1});
        fuckl(x, L, l - 2);
        fuckr(x, R, r - 2);
        for (int i = 0; i < A.size(); i++)
        {
            debug("A[%d]=%d\n", i, A[i]);
        }
    }
OUTPUT:
    int n = e.size() - 1;
    cout << n << "\n";
    for (int i = 1; i <= n; i++)
    {
        cout << e[i].size() << ' ';
        for (int j = 0; j < e[i].size(); j++)
        {
            cout << e[i][j].first << ' ' << e[i][j].second << ' ';
        }
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
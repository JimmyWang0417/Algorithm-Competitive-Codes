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
mt19937 rnd((random_device())());
struct Main
{
    Main()
    {
        vector<int> fa(26);
        iota(fa.begin(), fa.end(), 0);
        function<int(int)> find = [&](int x)
        {
            return fa[x] == x ? x : fa[x] = find(fa[x]);
        };
        string s1, s2, s3;
        cin >> s1 >> s2 >> s3;
        if (s1.length() != s2.length())
        {
            cout << "NO\n";
            return;
        }
        if (s1.length() != s3.length())
        {
            cout << "YES\n";
            return;
        }
        int n = (int)s1.length();
        for (int i = 0; i < n; ++i)
        {
            int c = s1[i] - 'a', d = s2[i] - 'a';
            fa[find(c)] = find(d);
        }
        for (int i = 0; i < n; ++i)
        {
            int c = s1[i] - 'a', d = s3[i] - 'a';
            if (find(c) != find(d))
            {
                cout << "YES\n";
                return;
            }
        }
        cout << "NO\n";
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
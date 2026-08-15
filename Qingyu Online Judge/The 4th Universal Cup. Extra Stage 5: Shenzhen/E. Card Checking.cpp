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
struct Main
{
    int n, m;
    auto checkA(set<int> A, set<int> B, set<int> C, set<int> F, set<int> G, set<int> H)
    {
        while (A.size() > 1)
        {
            if (!B.empty() && !G.empty())
            {
                int x = *A.begin();
                int y = *G.begin();
                auto it = B.upper_bound(y);
                if (it != B.end())
                {
                    A.erase(x);
                    G.erase(y);
                    B.erase(it);
                    continue;
                }
            }
            if (!G.empty() && !H.empty())
            {
                int x = *A.begin();
                int y = *G.begin();
                int z = *H.begin();
                auto it = C.upper_bound(z);
                if (it != C.end())
                {
                    A.erase(x);
                    G.erase(y);
                    H.erase(z);
                    C.erase(it);
                    continue;
                }
            }
            return false;
        }
        return true;
    }
    auto checkB(set<int> A, set<int> B, set<int> C, set<int> F, set<int> G, set<int> H)
    {
        if (F.size() > 1)
            return false;
        if ((!A.empty() && !G.empty() && *A.begin() < *G.rbegin()) ||
            (!B.empty() && !G.empty() && *B.begin() < *G.rbegin()) || 
            (!C.empty() && !H.empty() && *C.begin() < *H.rbegin()))
                return true;
        if (G.empty() && H.empty() && !A.empty() && !F.empty() && *A.begin() < *F.rbegin())
            return true;
        return false;
    }
    Main()
    {
        cin >> n;
        string s, t;
        cin >> s >> t;
        cin >> m;
        set<int> A, B, C;
        set<int> F, G, H;
        for (int i = 0; i < n; ++i)
            if (s[i] == '1')
            {
                if (i + 1 < m)
                    A.emplace(i + 1);
                else
                    B.emplace(i + 1);
            }
            else if (s[i] == '2')
                C.emplace(i + 1);
        for (int i = 0; i < n; ++i)
            if (t[i] == '1')
            {
                if (i + 1 < m)
                    F.emplace(i + 1);
                else
                    G.emplace(i + 1);
            }
            else if (t[i] == '2')
                H.emplace(i + 1);
        if (checkA(A, B, C, F, G, H) || checkB(A, B, C, F, G, H))
            cout << "Yes\n";
        else
            cout << "No\n";
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}


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
    Main() : m(-1)
    {
        cin >> n;
        vector<vector<int>> p{{}};

        for (int i = 0; i < n; ++i)
        {
            char op;
            cin >> op;
            if (op == 'F')
            {
                int x;
                cin >> x;
                p.back().emplace_back(x);
            }
            else
                p.emplace_back();
        }
        priority_queue<int, vector<int>, greater<>> A;
        priority_queue<int> B;
        i64 Asum = 0, ans = 0;
        for (const auto &a : p)
        {
            ++m;
            priority_queue<i64> C;
            for (int i = 0; i < (int)a.size(); ++i)
                C.emplace(((i64)a.size() - i) * a[i]);
            const int round = (int)a.size() + 1;
            i64 cur = 0;
            while ((int)A.size() < m && !B.empty())
            {
                Asum += B.top();
                A.push(B.top());
                B.pop();
            }
            while (!A.empty() && !B.empty() && A.top() < B.top())
            {
                int x = A.top(), y = B.top();
                A.pop(), B.pop();
                A.push(y), B.push(x);
                Asum += y - x;
            }

            int sze = (int)A.size();
            while (sze < m && !C.empty())
            {
                cur += C.top();
                C.pop();
                ++sze;
            }
            while (!A.empty() && !C.empty() && (i64)A.top() * round < C.top())
            {
                Asum -= A.top();
                B.push(A.top());
                A.pop();
                cur += C.top();
                C.pop();
            }
            cur += Asum * round;
            ans += cur;

            for (auto x : a)
                B.push(x);
        }
        cout << ans << '\n';
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


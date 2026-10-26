#include <bits/stdc++.h>
using namespace std;
struct Main
{
    int n, q;
    vector<int> a;
    vector<int> p;
    unordered_map<int, int> mp;
    auto mex()
    {
        int x = 0;
        while (mp[x])
            ++x;
        return x;
    }
    auto kmex(int k)
    {
        vector<int> cnt(n + 5);
        auto add = [&](int x)
        {
            if (0 <= x && x < (int)cnt.size())
                cnt[x]++;
        };
        auto find = [&](int x)
        {
            if (0 <= x && x < (int)cnt.size())
                return cnt[x];
            else
                return 0;
        };
        for (auto x : a)
        {
            if (find(x))
                add(k - x);
            else if (0 <= k - x && k - x < x && !find(k - x))
                add(k - x);
            else
                add(x);
        }
        int x = 0;
        while (cnt[x])
            ++x;
        return x;
    }
    Main()
    {
        cin >> n;
        p.resize(n);
        for (auto &i : p)
        {
            cin >> i;
            ++mp[i];
        }
        int x = mex();
        sort(p.begin(), p.end());
        a = p;
        p.erase(unique(p.begin(), p.end()), p.end());
        for (auto &i : p)
            i += x;
        unordered_map<int, int> answer;
        for (auto i : p)
            answer[i] = kmex(i);
        cin >> q;
        int ans = 0;
        while (q--)
        {
            int v;
            cin >> v;
            if (answer.find(v) != answer.end())
                ans ^= answer[v];
            else
                ans ^= x;
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

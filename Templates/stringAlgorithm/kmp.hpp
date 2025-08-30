#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 1e6 + 5;
constexpr int mod = 1e9 + 7;
constexpr int inv3 = (mod + 1) / 3;
namespace stringAlgorithm
{
    struct kmp
    {
        string s;
        vector<int> p;
        kmp() = default;
        kmp(const string &_s) : p(_s.size())
        {
            s = _s;
            for (int i = 1, j = 0; i < (int)p.size(); ++i)
            {
                while (j && s[i] != s[j])
                    j = p[j - 1];
                if (s[i] == s[j])
                    ++j;
                p[i] = j;
            }
        }
        auto match(const string &t)
        {
            vector<int> q(t.size());
            for (int i = 0, j = 0; i < (int)q.size(); ++i)
            {
                while (j && t[i] != s[j])
                    j = p[j - 1];
                if (t[i] == s[j])
                    ++j;
                q[i] = j;
            }
            return q;
        }
    };
}
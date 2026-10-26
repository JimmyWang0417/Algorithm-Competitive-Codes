#include <bits/stdc++.h>
using namespace std;

using LL = long long;

map<string, int> mp{
    {"WrongProblem", 100},
    {"SameProblem", 30},
    {"UnreasonableLimitForProblem", 5},
    {"WeakTestsForProblem", 3},
    {"BadProblem", 1}
};

struct Main {
    int n, P;
    string s;
    void main() {
        cin >> n >> P;
        int res = 0;
        for (int _case = 0; _case < n; ++_case) {
            res += work();
        }
        if (res <= P)
            cout << "Judger\n";
        else
            cout << "Joker\n";
    }
    int work() {
        cin >> s;
        if (s == "UnreasonableProblemArrangement") return 10;
        for (const auto &[t, x] : mp) {
            if (s.size() == t.size() + 1 && s.substr(0, t.size()) == t) {
                const char c = s.end()[-1];
                if ('A' <= c && c <= 'L') return x;
            }
        }
        return 0;
    }
};
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--)
        Main{}.main();
    return 0;
}

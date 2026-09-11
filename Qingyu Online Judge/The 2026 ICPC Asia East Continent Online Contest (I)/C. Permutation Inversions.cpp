#include <bits/stdc++.h>
using namespace std;

using ai3 = array<int, 3>;

struct Main {
    int n, m, tot = 0;
    vector<vector<int>> e;
    vector<int> in;
    vector<int> ans;
    void main() {
        cin >> n >> m;
        e.assign(n + 1, {});
        in.assign(n + 1, 0);
        for (int t = 0; t < m; ++t) {
            int l, r, u, v;
            cin >> l >> r >> u;
            for (int i = 2; i <= (r - l + 1); ++i) {
                cin >> v;
                e[u].push_back(v);
                ++in[v];
                u = v;
            }
        }
        priority_queue<int, vector<int>, greater<>> p;
        for (int u = 1; u <= n; ++u) {
            if (!in[u]) p.push(u);
        }
        ans.assign(n + 1, 0);
        while (p.size()) {
            const int u = p.top();
            p.pop();
            ans[u] = ++tot;
            for (auto v : e[u]) {
                if (!--in[v]) p.push(v);
            }
        }
        if (tot != n) {
            cout << "-1\n";
            return;
        }
        for (int i = 1; i <= n; ++i) {
            cout << ans[i] << " \n"[i == n];
        }
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) Main{}.main();
    return 0;
}
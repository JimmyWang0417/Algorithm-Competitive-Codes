#include <bits/stdc++.h>
using namespace std;

int ask(int x, int y, const vector<int> &s) {
    cout << "? " << x << ' ' << y << ' ' << s.size();
    for (int v : s) cout << ' ' << v;
    cout << endl;
    int t;
    if (!(cin >> t) || t < 0) exit(0);
    return t;
}

void solve_case(int n) {
    vector<vector<int>> comp(n + 1, vector<int>(n + 1));
    for (int z = 1; z <= n; ++z) {
        vector<int> reps;
        for (int x = 1; x <= n; ++x) {
            if (x == z) continue;
            int id = -1;
            for (int r : reps) {
                if (ask(x, r, {z})) {
                    id = r;
                    break;
                }
            }
            if (id == -1) {
                reps.push_back(x);
                comp[z][x] = x;
            } else {
                comp[z][x] = id;
            }
        }
    }

    vector<vector<char>> linked(n + 1, vector<char>(n + 1));
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) {
            bool ok = true;
            for (int w = 1; w <= n; ++w) {
                if (w != u && w != v && comp[w][u] != comp[w][v]) {
                    ok = false;
                    break;
                }
            }
            linked[u][v] = linked[v][u] = ok;
        }
    }

    set<vector<int>> blocks;
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) {
            if (!linked[u][v]) continue;
            vector<int> block{u, v};
            for (int w = 1; w <= n; ++w) {
                if (w != u && w != v && linked[w][u] && linked[w][v]) block.push_back(w);
            }
            sort(block.begin(), block.end());
            blocks.insert(std::move(block));
        }
    }

    set<pair<int, int>> edges;
    auto add_edge = [&](int a, int b) {
        if (a > b) swap(a, b);
        edges.emplace(a, b);
    };

    for (const auto &block : blocks) {
        if (block.size() == 2) {
            add_edge(block[0], block[1]);
            continue;
        }
        int v = block[0];
        vector<int> path(block.begin() + 1, block.end());
        int m = (int)path.size();
        int anchor = path[0], endpoint = path[1];
        for (int i = 2; i < m; ++i) {
            int y = path[i];
            if (ask(anchor, y, {v, endpoint}) == 0) endpoint = y;
        }
        vector<int> order;
        for (int x : path) {
            if (x != endpoint) order.push_back(x);
        }
        auto closer = [&](int a, int b) { return ask(endpoint, b, {v, a}) == 0; };
        int k = (int)order.size();
        vector<int> tmp(k);
        for (int len = 1; len < k; len <<= 1) {
            for (int i = 0; i < k; i += len << 1) {
                int left = i, mid = min(i + len, k), right = min(i + (len << 1), k);
                int p = left, q = mid, t = left;
                while (p < mid && q < right) {
                    if (closer(order[p], order[q])) tmp[t++] = order[p++];
                    else tmp[t++] = order[q++];
                }
                while (p < mid) tmp[t++] = order[p++];
                while (q < right) tmp[t++] = order[q++];
                for (int j = left; j < right; ++j) order[j] = tmp[j];
            }
        }
        add_edge(v, endpoint);
        int prev = endpoint;
        for (int x : order) {
            add_edge(prev, x);
            prev = x;
        }
        add_edge(v, prev);
    }

    cout << "! " << edges.size() << endl;
    for (auto [a, b] : edges) cout << a << ' ' << b << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tests;
    if (!(cin >> tests)) return 0;
    while (tests--) {
        int n;
        cin >> n;
        solve_case(n);
    }
    return 0;
}

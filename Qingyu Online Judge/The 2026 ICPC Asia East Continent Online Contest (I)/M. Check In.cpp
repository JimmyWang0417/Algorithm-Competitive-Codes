#include <bits/stdc++.h>
using namespace std;
map<string, int> mps;
int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        string tmp;
        cin >> tmp;
        mps[tmp] = -1;
    }
    for (int i = 1; i <= m; ++i) {
        string tmp;
        cin >> tmp;
        if (mps.find(tmp) == mps.end()) {
            puts("WRONG");
        } else {
            if (mps[tmp] == -1) {
                mps[tmp] = 1;
                puts("OK");
            } else {
                puts("REPEAT");
            }
        }
    }
}
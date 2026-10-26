#include <bits/stdc++.h>
#include <cassert>
using namespace std;

// #define LOCAL
#ifdef LOCAL
#define dbg(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define dbg(...) 42
#endif

#define all(x) (x).begin(), (x).end()
#define allr(x) (x).rbegin(), (x).rend()

using LL = long long;

/*
1 [1 2 34 5]
2 [2 34 5 6]
34 [3(1 2) 4(5 6)]
5 [1 2 34 5]
6 [2 34 5 6]
*/
const vector<int> dfa[10] = {
    {},           // 0
    {1, 2, 3, 5}, // 1
    {2, 3, 5, 6}, // 2
    {1, 2, 5, 6}, // 3
    {},           // 4
    {1, 2, 3, 5}, // 5
    {2, 3, 5, 6}  // 6
};
const string d2s[10] = {
    "",    // 0
    "001", // 1
    "010", // 2
    "011", // 3
    "100", // 4
    "101", // 5
    "110", // 6
};
const bool __check = []() -> bool
{
    auto check = [&](const int x, const int y) -> void
    {
        const string s = d2s[x] + d2s[y];
        for (int i = 2; i < int(s.size()); ++i)
        {
            if (s[i] == s[i - 1] && s[i] == s[i - 2])
            {
                dbg("x=%d y=%d s=%s Failed.\n", x, y, s.data());
                exit(-1);
            }
        }
    };
    for (int x : {1, 2, 5, 6})
    {
        vector<int> to_check = dfa[x];
        to_check.push_back(4);
        for (int y : to_check)
            check(x, y);
    }
    {
        const int x = 3;
        for (int y : {1, 2})
            check(x, y);
    }
    {
        const int x = 4;
        for (int y : {5, 6})
            check(x, y);
    }
    dbg("Check OK !!!\n");
    return 1;
}();

int dfa_inv[10][10] = {};
const bool __init_dfa_inv = []() -> bool
{
    for (auto &v : dfa_inv)
        for (auto &x : v)
            x = -1;
    for (int x : {1, 2, 5, 6})
    {
        for (int i = 0; i < 4; ++i)
        {
            const int y = dfa[x][i];
            if (y == 3)
                dfa_inv[x][4] = i;
            dfa_inv[x][y] = i;
        }
    }
    dfa_inv[3][1] = 0;
    dfa_inv[3][2] = 1;
    dfa_inv[4][5] = 2;
    dfa_inv[4][6] = 3;
    return 1;
}();
inline int inv(const int x, const int y)
{
    assert(dfa_inv[x][y] != -1);
    return dfa_inv[x][y];
}
const string s_inv[4] = {
    "00",
    "01",
    "10",
    "11"};

struct MainOne
{
    int n;
    string s = "", t = "";
    void main()
    {
        cin >> n >> s;
        if (n <= 1)
        {
            cout << "1\n"
                 << s << endl;
            return;
        }
        t = "";
        int state;
        if (s.size() % 2 && s.back() == '0')
            state = 2;
        else
            state = 1;
        dbg("state: %d", state);
        for (int i = 1; i < int(s.size()); i += 2)
        {
            const int x = (s[i - 1] - '0') * 2 + (s[i] - '0');
            const int nstate = dfa[state][x];
            dbg(" %d", nstate);
            if (state == 3)
            {
                if (x == 0 || x == 1)
                    t += d2s[3];
                else
                    t += d2s[4];
            }
            else
                t += d2s[state];
            state = nstate;
        }
        dbg("\n");
        t += d2s[state];
        dbg("cur t = %s\n", t.data());
        t = t.substr(3);
        if (s.size() & 1)
            t = string(1, s.back()) + t;
        cout << t.size() << "\n"
             << t << endl;
    }
};

struct MainTwo
{
    int n;
    string s = "", t = "";
    void main()
    {
        cin >> n >> s;
        if (n == 1)
        {
            cout << "1\n"
                 << s << endl;
            return;
        }
        int state, i;
        if (n % 3)
            i = 1;
        else
            i = 0;
        if (n % 3 && s[0] == '0')
            state = 2;
        else
            state = 1;
        dbg("state: %d", state);
        for (i += 2; i < int(s.size()); i += 3)
        {
            int nstate = (s[i - 2] - '0') * 4 + (s[i - 1] - '0') * 2 + (s[i] - '0');
            dbg(" %d", nstate);
            const int x = inv(state, nstate);
            t += s_inv[x];
            state = nstate;
        }
        dbg("\n");
        if (n % 3)
            t.push_back(s[0]);
        cout << t.size() << "\n"
             << t << endl;
    }
};

signed main()
{
// #ifndef LOCAL
//     ios::sync_with_stdio(false);
//     cin.tie(0), cout.tie(0);
// #endif
    int t, op;
    cin >> t >> op;
    if (op == 1)
        while (t--)
            MainOne{}.main();
    else
        while (t--)
            MainTwo{}.main();
    return 0;
}

/*
optimized:
1 [1 2 34 5]
2 [2 34 5 6]
34 [3(1 2) 4(5 6)]
5 [1 2 34 5]
6 [2 34 5 6]

extra bit: ?????????

python3 triplet_testing_tool.py I_sample_in.txt ./I
python3 triplet_testing_tool.py -q I_sample_in.txt ./I

python3 triplet_testing_tool.py 2.in ./I

1 1
6
010101

1 2

*/

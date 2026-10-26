#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
struct Main
{
    Main()
    {
        string s;
        cin >> s;
        stack<int> st;
        for (int i = 0; i < (int)s.length(); ++i)
        {
            if (s[i] == '(')
                st.push(i);
            else
            {
                if (!st.empty())
                    st.pop();
            }
        }
        if (!st.empty())
        {
            cout << "impossible\n";
            return;
        }
        cout << s << '\n';
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

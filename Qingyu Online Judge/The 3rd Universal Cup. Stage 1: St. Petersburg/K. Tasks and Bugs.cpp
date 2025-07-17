#include <bits/stdc++.h>
using namespace std;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    map<int, set<int>> tip;
    string s;

    while (getline(cin, s))
    {
        string x, y;
        if (s == "")
        {
            break;
        }
        int i = 0;
        for (i = 0; i < s.length(); i++)
        {
            if (s[i] == ':')
            {
                break;
            }
            x += s[i];
        }
        int xx = atoi(x.substr(3).data());
        i += 2;
        while (i < s.length())
        {
            if (s[i] == ',')
            {
                tip[atoi(y.substr(3).data())].insert(xx);
                string o;
                swap(o, y);
                i += 2;
            }
            else
            {
                y += s[i];
                i++;
            }
        }
        tip[atoi(y.substr(3).data())].insert(xx);
    }

    string forma = "CS-";
    for (auto &[a, b] : tip)
    {
        cout << forma << a << ": ";
        for (auto &x : b)
        {
            if (x != *b.rbegin())
            {
                cout << forma << x << ", ";
            }
            else
            {
                cout << forma << x;
            }
        }
        cout << "\n";
    }
}
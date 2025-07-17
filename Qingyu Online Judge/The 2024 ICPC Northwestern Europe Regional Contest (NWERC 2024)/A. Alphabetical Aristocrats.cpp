#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 1e5 + 5;
int n;
string a[N];
inline void _main()
{
	cin >> n;
	string unused;
	getline(cin, unused);
	for (int i = 1; i <= n; i++) getline(cin, a[i]);
	
	sort(a + 1, a + n + 1, [&](auto s, auto t){
		string a, b;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] >= 'A' && s[i] <= 'Z') {
				a = s.substr(i, (int)s.size() - i);
				break;
			}
		}
		for (int i = 0; i < t.size(); i++) {
			if (t[i] >= 'A' && t[i] <= 'Z') {
				b = t.substr(i, (int)t.size() - i);
				break;
			}
		}
		return a < b;
	});
	for (int i = 1; i <= n; i++) 
		cout << a[i] << '\n';
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int test = 1;
//	cin >> test;
	while (test--)
		_main();
	return 0;
}
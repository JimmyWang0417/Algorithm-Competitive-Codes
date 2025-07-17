#include <bits/stdc++.h>
using namespace std;
constexpr int N = 13;
constexpr char id[3] = {'o', 'g', 'r'};
char s[4][N], t[4][N];
vector<pair<char, int>> ans;
inline void work (int i, int x) 
{
	ans.emplace_back(id[i], x);
	for (int j = 0; j <= 9; ++j)
		t[i][(j + x) % 10] = s[i][j];
	for (int j = 0; j <= 9; ++j)
		s[i][j] = t[i][j];
	return ;
}
inline void cork(int x) 
{
	ans.emplace_back('c', x);
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			t[(i + 3 - x) % 3][j] = s[i][j];
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			s[i][j] = t[i][j];
}
inline void Swap(pair<int, int> x, pair<int, int> y) 
{
	if (x.second != 3) work (x.first, (13 - x.second) % 10);
	if (y.second) 
		work(y.first, 10 - y.second);
	int c = (y.first + 3 - x.first) % 3;
	cork(c), work(x.first, 9), cork(3 - c);
}
int main () 
{
	for (int i = 0; i < 3; ++i)
		cin >> s[i];
	while (1) 
	{
		pair<int, int> x(-1, -1), y(-1, -1);
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j <= 9; ++j)
				if (s[i][j] != id[i]) 
				{
					if (x.first == -1) 
						x = make_pair(i, j);
					else if (s[x.first][x.second] != s[i][j]) 
						y = make_pair(i, j);
				}
		if (x.first == -1) 
			break;
		Swap(x, y);
	}
	cout << ans.size() << '\n';
	for (auto [x, y] : ans) 
		cout << x << y << '\n';
	return 0;
}
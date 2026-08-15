#include<bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include<local/dbg.h>
#else
#define dbg(...) 42
#endif

using LL=long long;
#define ai(x) using ai##x=array<int,x>;
ai(2);ai(3);ai(4);ai(5);ai(6);ai(7);ai(8);ai(9);ai(10);ai(26);
#undef ai

#define all(x) (x).begin(),(x).end()
#define allr(x) (x).rbegin(),(x).rend()
template<class T>inline bool updmx(T& x,const T& y){return x<y?x=y,1:0;}
template<class T>inline bool updmn(T& x,const T& y){return y<x?x=y,1:0;}
template<class T>inline void clr(T& x){T().swap(x);}

mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());
LL rand(LL l,LL r){return rng()%(r-l+1)+l;}

int main(){
#ifndef LOCAL
	cin.tie(nullptr)->sync_with_stdio(false);
#endif
	int n; cin>>n;
	if(n&1){
		cout<<"NO\n";
		exit(0);
	}
	const int r=n%6;
	const int m=(n-r)/3;
	vector<ai2>ans;
	vector<int>top(m);
	for(int i=1;i<=m;++i){
		top[i-1]=(i*3);
		ans.push_back({i*3-2,i*3-1});
		ans.push_back({i*3-2,i*3});
		ans.push_back({i*3-1,i*3});
	}
	for(int i=2;i<=m;++i){
		ans.push_back({i*3-2,(i-1)*3-1});
	}
	ans.push_back({1,m*3-1});
	assert(top.size()%2==0);
	{
		int link=(int)(top.size()-r*3)/2;
		const int mid=(int)(top.size())/2;
		for(int i=0;i<link;++i){
			ans.push_back({top[i],top[i+mid]});
		}
		vector<int>rest; rest.reserve(m);
		for(int i=link;i<mid;++i){
			rest.emplace_back(top[i]);
			rest.emplace_back(top[i+mid]);
		}
		swap(top,rest);
	}
	for(int i=1;i<=r;++i){
		const int u=m*3+i;
		for(int j=0;j<3;++j){
			ans.push_back({u,top.back()});
			top.pop_back();
		}
	}
	cout<<ans.size()<<'\n';
	for(auto [u,v]:ans) cout<<u<<' '<<v<<'\n';
	return 0;
}

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

void solve(){
	int n; cin>>n;
	vector<int>a(n);
	for(auto& x:a) cin>>x;
	sort(all(a));
	int cnt_mx=0;
	while(a.back()==a[0]*2){
		a.pop_back();
		++cnt_mx;
	}
	map<int,int>mp;
	for(auto x:a) ++mp[x];
	vector<int>ans;
	ans.reserve(n);
	while(mp.size()){
		for(auto it=mp.begin();it!=mp.end();){
			ans.emplace_back(it->first);
			if(!--it->second){
				it=mp.erase(it);
			}
			else ++it;
		}
	}
	vector<int>nans={ans[0]}; nans.reserve(n);
	int val=0;
	for(int i=1;i<(int)(ans.size());++i){
		if(ans[i-1]>=ans[i]){
			if(ans[i]!=ans[0]){
				if(cnt_mx){
					--cnt_mx;
					nans.emplace_back(ans[0]*2);
				}
			}
			++val;
		}
		nans.emplace_back(ans[i]);
	}
	swap(ans,nans);
	if(cnt_mx) val+=cnt_mx-1;
	cout<<val<<'\n';
	for(auto x:ans) cout<<x<<' ';
	for(int i=1;i<=cnt_mx;++i){
		cout<<(ans[0]*2)<<' ';
	}
	cout<<'\n';
}
int main(){
#ifndef LOCAL
	cin.tie(nullptr)->sync_with_stdio(false);
#endif
	int t; cin>>t;
	while(t--) solve();
	return 0;
}

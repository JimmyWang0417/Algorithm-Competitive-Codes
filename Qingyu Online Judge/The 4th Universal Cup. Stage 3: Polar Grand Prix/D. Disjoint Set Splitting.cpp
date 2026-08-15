#pragma GCC optimize(3)
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC optimize("inline","fast-math","unroll-loops")
#include<bits/stdc++.h>
using namespace std;
#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

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
template<typename T>inline bool updmx(T& x,const T& y){return x<y?x=y,1:0;}
template<typename T>inline bool updmn(T& x,const T& y){return y<x?x=y,1:0;}
template<typename T>inline void clr(T& x){T().swap(x);}

mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());
LL rand(LL l,LL r){return rng()%(r-l+1)+l;}

struct DSU{
	vector<int>fa,siz;
	DSU(){}
	DSU(int n){
		init(n);
	}
	void init(int n){
		fa.resize(n);
		iota(fa.begin(),fa.end(),0);
		siz.assign(n,1);
	}
	int get(int x){
		while(x!=fa[x]){
			x=fa[x]=fa[fa[x]];
		}
		return x;
	}
	bool same(int x,int y){
		return get(x)==get(y);
	}
	bool merge(int x,int y){
		x=get(x),y=get(y);
		if(x==y) return 0;
		if(siz[y]>siz[x]) swap(x,y);
		siz[x]+=siz[y],fa[y]=x;
		return 1;
	}
	int size(int x){
		return siz[get(x)];
	}
};

struct chash{
	LL operator()(const ai2& x) const{
		return (LL)(1e9)*x[0]+x[1];
	}
};

void solve(){
	int n,m,q;
	cin>>n>>m>>q;
	vector<ai2>edge(m);
	for(auto& [u,v]:edge){
		cin>>u>>v;
		if(u>v) swap(u,v);
	}
	vector<ai2>enc(q);
	{
		int a=0,b=0;
		for(auto& [u,v]:enc){
			cin>>u>>v;
			u=(u+a)%n;
			v=(v+b)%n;
			if(u>v) swap(u,v);
			a=(a*2+1)%n;
			b=(b*3+1)%n;
		}
	}
	using SB=gp_hash_table<ai2,null_type,chash>;
	SB del;
	DSU dsu;
	auto check=[&](const int& lim)->bool{
		dbg(lim);
		SB({},{},{},{},{1<<(__lg(q)+1)}).swap(del);
		for(int i=0;i<=lim;++i){
			const auto& [u,v]=enc[i];
			del.insert(ai2{u,v});
		}
		dsu.init(n);
		for(auto& [u,v]:edge){
			if(del.find(ai2{u,v})!=del.end()){
				continue;
			}
			dsu.merge(u,v);
		}
		return dsu.size(0)==n;
	};
	int l=0,r=q-1,mid,ans=-1;
	while(l<=r){
		mid=l+r>>1;
		if(check(mid)){
			ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	if(ans==-1){
		for(int i=0;i<q;++i) cout<<"0\n";
	}
	else{
		for(int i=0;i<=ans;++i) cout<<"1\n";
		for(int i=ans+1;i<q;++i) cout<<"0\n";
	}
}
int main(){
#ifndef LOCAL
	cin.tie(nullptr)->sync_with_stdio(false);
#endif
	int t; cin>>t;
	while(t--) solve();
	return 0;
}


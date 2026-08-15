#ifdef __FUCK_GCC
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC optimize("inline","fast-math","unroll-loops")
#endif
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
template<typename T>inline bool updmx(T& x,const T& y){return x<y?x=y,1:0;}
template<typename T>inline bool updmn(T& x,const T& y){return y<x?x=y,1:0;}
template<typename T>inline void clr(T& x){T().swap(x);}

mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());
LL rand(LL l,LL r){return rng()%(r-l+1)+l;}

void solve(){
	int n; cin>>n;
	vector<set<int>>e(n+1);
	for(int i=1,u,v;i<n;++i){
		cin>>u>>v;
		e[u].insert(v);
		e[v].insert(u);
	}
	int st=-1,ed=-1;
	{
		auto dfs=[&](auto&& self,int u,int fa)->ai2{
			int d=0,r=u;
			for(auto v:e[u]){
				if(v==fa) continue;
				auto [td,tr]=self(self,v,u);
				++td;
				if(updmx(d,td)) r=tr;
			}
			return {d,r};
		};
		st=dfs(dfs,1,0)[1];
		ed=dfs(dfs,st,0)[1];
	}
	assert(st!=-1);
	assert(ed!=-1);
	vector<int>path;
	{
		auto dfs=[&](auto&& self,int u,int fa,int dest)->bool{
			if(u==dest){
				path={dest};
				return 1;
			}
			for(auto v:e[u]){
				if(v==fa) continue;
				if(self(self,v,u,dest)){
					path.emplace_back(u);
					return 1;
				}
			}
			return 0;
		};
		dfs(dfs,ed,0,st);
	}
	dbg(st,ed,path);
	bool _extra=0;
	if(path.size()&1);
	else{
		_extra=1;
		const int m=(int)(path.size());
		const int u=path[m/2-1];
		const int v=path[m/2];
		++n;
		e.emplace_back(set<int>{u,v});
		e[u].erase(v); e[v].erase(u);
		e[u].insert(n); e[v].insert(n);
		path.insert(path.begin()+m/2,n);
		dbg("\t",path);
	}
	const int radius=(int)path.size()/2;
	const int root=path[radius];
	dbg(radius,root,path);
	vector<int>dep(n+1);
	int cnt_leaf=0;
	{
		auto dfs=[&](auto&& self,int u,int fa)->bool{
			if(dep[u]==radius){
				assert(e[u].size()==1);
				assert(*e[u].begin()==fa);
				++cnt_leaf;
				return 1;
			}
			assert(dep[u]<radius);
			bool ret=0;
			for(auto it=e[u].begin();it!=e[u].end();){
				const int v=*it;
				if(v==fa){
					it=e[u].erase(it);
					continue;
				}
				dep[v]=dep[u]+1;
				if(!self(self,v,u)){
					dep[v]=-1;
					it=e[u].erase(it);
				}
				else{
					ret=1;
					++it;
				}
			}
			return ret;
		};
		dfs(dfs,root,0);
	}
	dbg(cnt_leaf);
	vector<int>ans(radius*2+1);
	// final leaf: [1,tot)
	int tot=cnt_leaf;
	ans[0]=tot;
	for(int i=1;i<=radius;++i){
		ans[i]=++tot;
	}
	dbg("partial",ans);
	vector<vector<int>>points(radius);
	for(int u=1;u<=n;++u){
		if(0<dep[u] && dep[u]<radius){
			points[dep[u]].emplace_back(u);
		}
	}
	vector<int>id(n+1,-1);
	vector<int>mn_son_id(n+1,1e9);
	for(int d=radius-1;d>0;--d){
		for(auto u:points[d]){
			for(auto v:e[u]){
				updmn(mn_son_id[u],id[v]);
			}
		}
		sort(all(points[d]),[&](const int u,const int v)->bool{
			if(e[u].size()==e[v].size()){
				return mn_son_id[u]<mn_son_id[v];
			}
			return e[u].size()<e[v].size();
		});
		for(int i=0;i<points[d].size();++i){
			id[points[d][i]]=i;
		}
	}
	{ // TODO
		int nw=radius;
		auto dfs=[&](auto&& self,int u)->void{
			if(dep[u]+1==radius){
				ans[++nw]=(int)e[u].size()-(radius==1);
				return;
			}
			tot+=(int)e[u].size()-(u==root);
			ans[++nw]=tot;
			int go=-1,id_go=1e9;
			for(auto v:e[u]){
				if(updmn(id_go,id[v])){
					go=v;
				}
			}
			assert(go!=-1);
			self(self,go);
		};
		dfs(dfs,root);
	}
	dbg(_extra,ans);
	if(_extra){
		for(int i=1;i<radius;++i){
			--ans[ans.size()-i-1];
		}
		ans.erase(ans.begin()+radius);
	}
	for(auto x:ans) cout<<x<<' ';
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

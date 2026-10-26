#include <bits/stdc++.h>
#define VI vector<int>
#define int long long
using namespace std;
inline int read(){
    int x=0,f=1;char ch=getchar();
    for(;!isdigit(ch);ch=getchar())f^=ch=='-';
    for(;isdigit(ch);ch=getchar())x=x*10+(ch^48);
    return f?x:-x;
}

template<class T>inline void chmin(T &x,T y){x>y?x=y:x;}

int n,m,ans;

VI A,B,C;
set<int> neg;

constexpr int inf=1e15;

struct SegmentTree{
    struct node{
        array<signed,2> ch{};
        array<int,2> val={0,0};
        int tag=0,l,r,lazytag=0;
        node(int x=0,int y=0,signed u=0,signed v=0){
            l=x,r=y,ch[0]=u,ch[1]=v;
        }
        signed &operator[](size_t i){return ch[i];}
    };
    vector<node> tr;
    vector<signed> rootlist;
    signed pool,root;
    SegmentTree(int l=0,int r=0){
        rootlist={root=pool=1};
        tr={node(),node(l,r)};
    }
    signed newnode(int l,int r,signed u=0,signed v=0){
        tr.push_back(node(l,r,u,v));
        return ++pool;
    }
    signed &lc(signed p){return tr[p][0];}
    signed &rc(signed p){return tr[p][1];}
    void pushup(signed p){
        auto &LL=tr[lc(p)],&RR=tr[rc(p)];
        tr[p].val=min(LL.val,RR.val);
    }
    void pushdown(signed p){
        auto &LL=tr[lc(p)],&RR=tr[rc(p)];
        LL.lazytag+=tr[p].lazytag;
        RR.lazytag+=tr[p].lazytag;
        LL.val[0]+=tr[p].lazytag;
        RR.val[0]+=tr[p].lazytag;
        tr[p].lazytag=0;
    }
    void build(signed p,int l,int r,VI &B){
        tr[p]=node(l,r);
        if(l==r){
            tr[p].val[0]=B[l];
            tr[p].val[1]=l;
            tr[p].lazytag=0;
            return;
        }
        int mid=(l+r)>>1;
        lc(p)=newnode(l,mid);
        rc(p)=newnode(mid+1,r);
        build(lc(p),l,mid,B);
        build(rc(p),mid+1,r,B);
        pushup(p);
    }
    void modify1(signed p,int L,int R,int d){
        int l=tr[p].l,r=tr[p].r;
        if(L<=l&&r<=R){
            tr[p].lazytag+=d;
            tr[p].val[0]+=d;
            return;
        }
        pushdown(p);
        int mid=(l+r)>>1;
        if(L<=mid)modify1(lc(p),L,R,d);
        if(mid<R)modify1(rc(p),L,R,d);
        pushup(p);
    }
    void modify2(signed p,int x,int d){
        int l=tr[p].l,r=tr[p].r;
        if(l==r){
            tr[p].lazytag=0;
            tr[p].val[0]=d;
            return;
        }
        pushdown(p);
        int mid=(l+r)>>1;
        if(x<=mid)modify2(lc(p),x,d);
        if(mid<x)modify2(rc(p),x,d);
        pushup(p);
    }
    array<int,2> query(signed p,int L,int R){
        int l=tr[p].l,r=tr[p].r;
        if(L<=l&&r<=R)return tr[p].val;
        array<int,2> ret={inf,-1};
        pushdown(p);
        int mid=(l+r)>>1;
        if(L<=mid)chmin(ret,query(lc(p),L,R));
        if(mid<R)chmin(ret,query(rc(p),L,R));
        return ret;
    }
}sgt;

vector<VI> a;

void solve(){
    n=read(),m=read(),ans=0;
    a.assign(n+1,VI(m+1,0));
    for(int i=1;i<=n;++i)for(int j=1;j<=m;++j)a[i][j]=read();
    A=VI(m+2,n+1),B=VI(m+1,n+1),C=VI(m+1,0);
    for(int i=1;i<=m;++i){
        for(int j=1;j<=n;++j){
            if(a[j][i]!=0){
                A[i]=j;
                B[i]=a[j][i];
                break;
            }
        }
    }
    sgt.build(1,1,m,B);
    for(int i=1;i<=m;++i){
        C[i]=A[i+1]-A[i];
        if(C[i]<0)neg.insert(i);
    }
    neg.insert(0);
    while(m){
        if(A[m]==n+1){
            neg.erase(m-1);
            C[m-1]=A[m]-A[m-1];
            --m;
            continue;
        }
        auto it=neg.end();
        int pos=*(--it)+1;
        auto [val,x]=sgt.query(1,pos,m);
        ans+=val;
        sgt.modify1(1,pos,m,-val);
        while(1){
            auto [u,v]=sgt.query(1,pos,m);
            if(u)break;
            int tag=0;
            for(int j=A[v]+1;j<=n;++j){
                if(a[j][v]){
                    A[v]=j;
                    B[v]=a[j][v];
                    tag=1;
                    break;
                }
            }
            if(!tag)A[v]=n+1,B[v]=inf;
            C[v-1]=A[v]-A[v-1];
            C[v]=A[v+1]-A[v];
            if(v>1)neg.erase(v-1);
            neg.erase(v);
            if(v>1&&C[v-1]<0)neg.insert(v-1);
            if(C[v]<0)neg.insert(v);
            sgt.modify2(1,v,B[v]);
        }
    }
    printf("%lld\n",ans);
}

signed main(){
    // for(int cas=read();cas--;)
    solve();
}

/*
4 4
1 1 1 0
1 0 2 1
1 2 1 1
0 2 1 1

*/

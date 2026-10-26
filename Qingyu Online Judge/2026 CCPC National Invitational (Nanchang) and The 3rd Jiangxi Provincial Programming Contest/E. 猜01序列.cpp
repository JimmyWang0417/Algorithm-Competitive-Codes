
#include <bits/stdc++.h>

#define int long long
#define VI vector<int>
using namespace std;
inline int read(){
    int x=0,f=1;char ch=getchar();
    for(;!isdigit(ch);ch=getchar())f^=ch=='-';
    for(;isdigit(ch);ch=getchar())x=x*10+(ch^48);
    return f?x:-x;
}

VI node;

int query(VI &cc){
    printf("? %lld ",cc.size());
    for(int x:cc)printf("%lld ",x);
    puts("");
    fflush(stdout);
    int x=read();
    return x;
}

signed main(){
    int n=read(),add=0,tag=0;
    node.resize(n);
    iota(node.begin(),node.end(),1);
    int highbit=__lg(n);
    for(int i=highbit;i>=0;--i){
        VI CC0={},CC1={};
        for(int x:node){
            if((x>>i)&1)CC1.push_back(x);
            else CC0.push_back(x);
        }
        if(CC0.size()){
            int tt=query(CC0);
            if(tt==0){
                if(tag){
                    node.swap(CC1);
                }else{
                    continue;
                }
            }else{
                tag=1;
                add=tt;
                node.swap(CC0);
            }
        }else{
            int ff=query(CC1);
            if(ff==0){
                if(tag){
                    node.swap(CC0);
                }else{
                    continue;
                }
            }else{
                tag=1;
                add=ff;
                node.swap(CC1);
            }
        }
    }
    printf("! %lld\n",1+add);
    return 0;
}
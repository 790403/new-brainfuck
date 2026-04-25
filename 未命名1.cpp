#include<bits/stdc++.h>
using namespace std;
#define int long long
struct node{
    int cnt=0,l=0,r=0;
};
node d[10000000];
class stree{
    private:
        vector<int> root;
        int n,len=0;
        int pbuild(int s,int t){
            int p=++len;
            if(s==t)return p;
            int m=(s+t)/2;
            d[p].l=pbuild(s,m);
            d[p].r=pbuild(m+1,t);
            return p;
        }
        int padd(int p,int num,int s,int t) {
            int pp=++len;
            d[pp].l=d[p].l;
            d[pp].r=d[p].r;
            d[pp].cnt=d[p].cnt+1;
            if(s==t)return pp;
            int m=(s+t)/2;
            if(num<=m)d[pp].l=padd(d[p].l,num,s,m);
            else d[pp].r=padd(d[p].r,num,m+1,t);
            return pp;
        }
        int pgetcnt(int r,int num,int s,int t){
            if(num<s)return 0;
            if(s==t)return d[r].cnt;
            int m=(s+t)/2;
            if(num<=m)return pgetcnt(d[r].l,num,s,m);
            return d[d[r].l].cnt+pgetcnt(d[r].r,num,m+1,t);
        }
    public:
        stree(int nn){
            n=nn;
            root.resize(nn+100);
            root[0]=pbuild(1,n);
        }
        int getcnt(int r,int k){
            return pgetcnt(root[r],k,1,n);
        }
        void add(int p,int num){
            root[p]=padd(root[p-1],num,1,n);
        }
};
int a[200005];
int b[500005];
signed main(){
    int t;
    cin>>t; 
    for(int _=1;_<=t;_++){
        cout<<"Case #"<<_<<':';
        int n,m;
        cin>>n>>m;
        for(int i=1;i<=n;i++)cin>>a[i];
        for(int i=1;i<=n;i++){
            int aa=a[i];
            a[i]=b[aa];
            b[aa]=i;
        }
		stree aa(n);
        for(int i=1;i<=n;i++)aa.add(i,a[i]);
        int lans=0;
        for(int i=1;i<=m;i++){
            int ll,rr;
            cin>>ll>>rr;
            int l=min((ll+lans)%n+1,(rr+lans)%n+1);
            int r=max((ll+lans)%n+1,(rr+lans)%n+1);
            int cnt=ceil((double)aa.getcnt(r,l)/2.);
            int L=l,R=r;
            while(L<=R){
                int mid=(L+R)/2;
                if(aa.getcnt(mid,l)<cnt)L=mid+1;
                else R=mid-1;
            }
            cout<<' '<<L;
            lans=L;
        }
        cout<<'\n';
    }
    return 0;
}

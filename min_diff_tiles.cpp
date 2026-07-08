#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, k;
vector<pair<ll,ll>> v;
vector<ll> H;

struct SegTree {
    vector<int> mx, lz;
    void init(int n){ mx.assign(4*n,0); lz.assign(4*n,0); }
    void push(int node){
        if(lz[node]){
            for(int c=node*2;c<=node*2+1;c++){ mx[c]+=lz[node]; lz[c]+=lz[node]; }
            lz[node]=0;
        }
    }
    void upd(int node,int l,int r,int ql,int qr,int val){
        if(qr<l||r<ql) return;
        if(ql<=l&&r<=qr){ mx[node]+=val; lz[node]+=val; return; }
        push(node);
        int m=(l+r)/2;
        upd(node*2,l,m,ql,qr,val);
        upd(node*2+1,m+1,r,ql,qr,val);
        mx[node]=max(mx[node*2],mx[node*2+1]);
    }
} seg;

bool check(ll mid){
    seg.init(n);
    int j=0; bool found=false;
    for(int i=0;i<n && !found;i++){
        int lo=lower_bound(H.begin(),H.end(), v[i].second-mid)-H.begin();
        int hi=upper_bound(H.begin(),H.end(), v[i].second)-H.begin()-1;
        if(lo<=hi) seg.upd(1,0,n-1,lo,hi,1);
        while(j<i && v[i].first-v[j].first>mid){
            int lo2=lower_bound(H.begin(),H.end(), v[j].second-mid)-H.begin();
            int hi2=upper_bound(H.begin(),H.end(), v[j].second)-H.begin()-1;
            if(lo2<=hi2) seg.upd(1,0,n-1,lo2,hi2,-1);
            j++;
        }
        if(i-j+1>=k && seg.mx[1]>=k) found=true;
    }
    return found;
}

int main(){
    cin>>n>>k;
    v.resize(n);
    for(auto &p:v) cin>>p.first>>p.second;
    sort(v.begin(),v.end());
    H.resize(n);
    for(int i=0;i<n;i++) H[i]=v[i].second;
    sort(H.begin(),H.end());

    ll lo=0, hi=1e9, ans=hi;
    while(lo<=hi){
        ll mid=lo+(hi-lo)/2;
        if(check(mid)){ ans=mid; hi=mid-1; }
        else lo=mid+1;
    }
    cout<<ans<<"\n";
}
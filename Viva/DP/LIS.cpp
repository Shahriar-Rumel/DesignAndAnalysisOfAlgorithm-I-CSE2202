#include <bits/stdc++.h>
using namespace std;

vector<int>dp;
vector<int>track;
vector<int>a;

int LIS(int n){
    dp.assign(n,0);
    track.assign(n,1);
    dp[0] = 1;
    for(int i = 1 ; i < n  ; i++){
        dp[i] = 1;
        track[i] = i;
        for(int j = 0 ; j < i  ; j++){
            if(a[i] > a[j] && dp[j]+1 > dp[i]){
              dp[i] = dp[j]+1;
              track[i] = j;
            }
        }
    }
    int res = 0;
    for(int i = 0 ; i < n ; i++) res  = max(res,dp[i]);
    return res;
}

void printLIS(int n){

    int ans = -1,last = -1 ;
    for(int i = 0 ; i < n ; i++){
        if(dp[i] > ans){
            ans = dp[i];
            last = i;
        }
    }

    vector<int>seq(n);
    seq.push_back(a[last]);

    while(track[last] < last){
        last = track[last];
        seq.push_back(a[last]);
    }
    reverse(seq.begin(),seq.end());
    for(auto it: seq) if(it !=0) cout<<it<<" ";
}

int main(){
    int n ;
    cin >> n;
    // vector<int>a(n+1);
    a.assign(n,0);
    for(int i = 0 ; i < n ; i++){
        cin>> a[i];
    }
    cout<<"\nLIS : "<<LIS(n)<<endl;
    printLIS(n);
}
#include <bits/stdc++.h>
using namespace std;

#define ll long long


ll knapsackRecursive(ll w,ll weight[],ll val[],ll n){


    if(n == -1 || w == 0 ) return 0;

    // Not considering current Element
    if(weight[n] > w) return knapsackRecursive(w,weight,val,n - 1);

    // Considering Current Element but deciding whether to include it to the result or not

    else return max(val[n] + knapsackRecursive(w - weight[n],weight,val,n - 1),knapsackRecursive(w,weight,val,n - 1));
}


ll knapsackMemoization(ll w,ll weight[],ll val[],ll n,vector<vector<int>> &dp){


    if(n < 0 ) return 0;

    if( dp[n][w] != -1 ) return dp[n][w];

    // Not considering current Element
    if( weight[n] > w ){
        dp[n][w] = knapsackMemoization(w,weight,val,n - 1,dp);
        return dp[n][w];
    } 

    // Considering Current Element but deciding whether to include it to the result or not

    else {
        dp[n][w] =  max( val[n] + knapsackMemoization(w - weight[n],weight,val,n - 1,dp),knapsackMemoization(w,weight,val,n - 1,dp) );
        return dp[n][w];
    } 
}


ll knapsackTabulation(ll w,ll weight[],ll val[],ll n){


    vector<vector<ll>> dp(n + 1,vector<ll>(w + 1));
   
    for(ll i = 0 ; i <= n ; i++)
        for(ll j = 0 ; j <= w  ; j++) {
            if(i == 0 || j == 0 ) dp[i][j] = 0;

            // Considering Current Element but deciding whether to include it to the result or not
            else if(weight[i] <= w) dp[i][j] = val[i-1] + dp[i-1][w - weight[i-1]] >  dp[i-1][j] ?  val[i-1] + dp[i-1][w - weight[i-1]]: dp[i-1][j] ;

            // Not considering current Element
            else dp[i][j] = dp[i-1][j];

        }

        return dp[n][w];
}
int main(){
    ll n,w;
    cin >> n >> w;
    ll val[n], weight[n];
    for(ll i = 0 ; i < n ; i++) cin >> val[i];
    for(ll i = 0 ; i < n ; i++) cin >> weight[i];

    cout<<"Maximum Value with Recursive Implementation : "<<knapsackRecursive(w,weight,val,n - 1)<<endl;

    vector<vector<int>> dp(n,vector<int>(w,-1));

    for(ll i = 0 ; i < n ; i++)
        for(ll j = 0 ; j < w + 1 ; j++) dp[i].push_back(-1) ;

    cout<<"Maximum Value with Memoization Implementation : "<<knapsackMemoization(w,weight,val,n - 1,dp)<<endl;


    cout<<"Maximum Value with Tabulation Implementation : "<<knapsackTabulation(w,weight,val,n - 1)<<endl;

}
#include <bits/stdc++.h>
using namespace std;

#define ll long long

vector<pair<ll,ll>>parent;


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


ll knapsackTabulation(vector<vector<ll>> &dp,ll w,ll weight[],ll val[],ll n){

    // parent.assign(n+1,{});
    
    for(ll i = 0 ; i <= n ; i++) {
        // cout<<endl;
        for(ll j = 0 ; j <= w  ; j++) {
            if(i == 0 || j == 0 ){
                dp[i][j] = 0;
                // cout<<dp[i][j]<<" ";
            } 

            // Considering Current Element but deciding whether to include it to the result or not
            else if(weight[i-1] <= j) {

                if(val[i-1] + dp[i-1][j - weight[i-1]] >  dp[i-1][j]){
                    dp[i][j] = val[i-1] + dp[i-1][j - weight[i-1]];
                    parent.push_back({i-1,j - weight[i-1]});
                }else{
                    dp[i][j] = dp[i-1][j];
                    parent.push_back({i-1,j});
                }
                // dp[i][j] = val[i-1] + dp[i-1][j - weight[i-1]] >  dp[i-1][j] ?  val[i-1] + dp[i-1][j - weight[i-1]]: dp[i-1][j] ;
                // cout<<dp[i][j]<<" ";
            }

            // Not considering current Element
            else{
              dp[i][j] = dp[i-1][j];
            //   cout<<dp[i][j]<<" ";
            } 

        }
    }
    parent.push_back({n,w});
    return dp[n][w];
}

void printPath(vector<vector<ll>> &dp,ll n , ll w,ll weight[]){

    ll i = n , j = w;

    vector<ll>res;

    while( i > 0 && j > 0){
            if(dp[i][j] == dp[i][j-1]){
                j--;
                // cout<<dp[i][j]<<" ";
                // flag = true;
            } else if(dp[i-1][j] == dp[i][j]){
                i--;
            }
            else {
                // cout<<dp[i-1][j-weight[i-1]]<<" ";
                // cout <<dp[i][j]<<" ";
                res.push_back(dp[i][j]);
                j = j - weight[i-1];
                i--;
            }
    }

    reverse(res.begin(),res.end());
    for(auto it: res) cout<<it<<" ";
}
int main(){
    ll n,w;
    cin >> n >> w;
    ll val[n], weight[n];
    for(ll i = 0 ; i < n ; i++) cin >> val[i];
    for(ll i = 0 ; i < n ; i++) cin >> weight[i];

    // cout<<"Maximum Value with Recursive Implementation : "<<knapsackRecursive(w,weight,val,n - 1)<<endl;

    // vector<vector<int>> dp(n + 1,vector<int>(w + 1,-1));

    // for(ll i = 0 ; i <= n ; i++)
    //     for(ll j = 0 ; j <= w + 1 ; j++) dp[i].push_back(-1) ;

    // cout<<"Maximum Value with Memoization Implementation : "<<knapsackMemoization(w,weight,val,n - 1,dp)<<endl;


    vector<vector<ll>> dp(n + 1,vector<ll>(w + 1));
    cout<<"Maximum Value with Tabulation Implementation : "<<knapsackTabulation(dp,w,weight,val,n)<<endl;

    printPath(dp,n,w,weight);

}
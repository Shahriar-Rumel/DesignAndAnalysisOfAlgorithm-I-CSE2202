#include <bits/stdc++.h>

#include <chrono>

using namespace std;
using namespace std::chrono;

#define ll long long


ll MCMRecursive(ll arr[],ll i , ll j){
    if(i  == j) return 0;
    ll minEl = INT_MAX;

    ll count;

    for(ll k = i  ; k < j ; k++) {
      count = MCMRecursive(arr,i,k)+ MCMRecursive(arr, k + 1 ,j) + (arr[i-1] * arr[j] * arr[k]);
      if(count < minEl ) minEl = count;
    }
    return minEl;
    
}


ll MCMDP(ll arr[],ll n){

    ll dp[n+1][n+1];

    for(ll i = 0 ; i < n ; i++ ) dp[i][i+1] = 0;

    for( ll gap = 2 ; gap < n ; gap++){
        for( ll i = 0 ; i + gap < n ; i++){
            ll j = i + gap;

            dp[i][j] = INT_MAX;

            for( ll k = i + 1 ; k < j ; k++)
                dp[i][j]= min(dp[i][j],dp[i][k]+ dp[k][j]+ arr[i]* arr[j]* arr[k]);
            
        }
    }

    return dp[0][n - 1];
}

int main(){
    ll n;

    FILE* fileRead;
    FILE* fileWrite;
    auto start = high_resolution_clock::now();

    fileRead = fopen("in.txt","r");
    fileWrite = fopen("out.txt","w");

    fscanf(fileRead,"%lld",&n);

    ll arr[n];

    for(ll i = 0; i < n ; i++) fscanf(fileRead,"%lld",&arr[i]);


    // fprintf(fileWrite,"Min Number of Multiplication : %lld\n",MCMRecursive(arr,1, n - 1));
    fprintf(fileWrite,"Min Number of Multiplication : %lld\n",MCMDP(arr,n));

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    fprintf(fileWrite,"Time Taken : %ld ms",duration.count());

    fclose(fileRead);
    fclose(fileWrite);
}
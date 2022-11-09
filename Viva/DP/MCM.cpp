#include <bits/stdc++.h>
#include <limits.h>
using namespace std;

void printMCMOrder(vector<vector<int>>&bracket,int i , int j , int n,char &name){
    if(i == j ) {
        cout<<name;
        name++;
    }
    else{
        cout<<"(";
        printMCMOrder(bracket,i,bracket[i][j],n,name);
        printMCMOrder(bracket,bracket[i][j]+1,j,n,name);
        cout<<")";
    }
    
    // cout<<bracket[i][j];
}
int MCM(vector<int>&a,int n){
    vector<vector<int>>dp(n,vector<int> (n));

    vector<vector<int>>bracket(n,vector<int>(n,0));

    for(int i = 0 ; i < n - 1  ; i++)dp[i][i+1] = 0;

    for(int gap = 2; gap < n ; gap++){
        for(int i = 0 ; i + gap < n ; i++){
            int j = i + gap;
            dp[i][j] = INT_MAX;
            for(int k = i+1 ; k < j; k++){
                int q = dp[i][k] + dp[k][j] + a[i] * a[k] * a[j];
                if(q < dp[i][j]){
                    dp[i][j]= q;
                    bracket[i][j] = k;
                    // cout<<bracket[i][j];
                }
            }
        }
    }
    cout<<endl;
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            cout<<dp[i][j]<<" ";
        }
        cout<<endl;
    }
    char name = 'A';
    printMCMOrder(bracket,0,n-2 , n, name);
    return dp[0][n-1];
}

int main(){
    int n;
    cin >> n;

    vector<int>a(n,0);
    for(int i = 0 ; i < n ; i++)cin >> a[i];
    cout<<MCM(a,n);
}
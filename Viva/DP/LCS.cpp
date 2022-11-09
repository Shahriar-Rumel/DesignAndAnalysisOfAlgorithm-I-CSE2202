#include <bits/stdc++.h>
using namespace std;

int LCS(vector<vector<int>>&dp, string s1,string s2){

    int n = s1.size();
    int m = s2.size();
    
    for(int i = 0 ; i < n + 1  ; i++ ){

        for(int j = 0 ; j < m + 1; j++){

            if(i == 0 || j == 0 ) dp[i][j] = 0;

            else if(s1[i] == s2[j]){
                dp[i][j] = 1 + dp[i-1][j-1];
            }
            else{
                dp[i][j]= max(dp[i-1][j],dp[i][j-1]);
            }
        }
    }
    return dp[n][m];
}

void printLCS(vector<vector<int>>&dp,string s1,string s2){
    int i = s1.size() ; 
    int j = s2.size() ;

    vector<char>res;
    // res.assign(i,'$');

    while( i > 0 && j > 0){
      if(s1[i-1] == s2[j-1]){
        // cout<<s1[i-1];
        res.push_back(s1[i-1]);
        i--; j--;
      }
      else if(dp[i-1][j] > dp[i][j-1]) i--;
      else j--;
    }

    reverse(res.begin(),res.end());
    for(auto it: res){
        if(it =='$')break;
        cout<<it;
    }
}

int main(){
    string s1,s2;
    cin >> s1>> s2;
    int n = s1.size();
    int m = s2.size();
    vector<vector<int>>dp(n + 1,vector<int>(m + 1));
    cout<<"Longest Common Subsequence : "<<LCS(dp,s1,s2)<<endl;

    for(int i = 0 ; i <= n ; i++){
        for(int j = 0 ; j <= m ; j++) cout<<dp[i][j]<<" ";
        cout<<endl;
    }
    printLCS(dp,s1,s2);
}
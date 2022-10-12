#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

#define ll long long
const int INF = 100000;

ll dp[1000][1000];


ll LCSRecursive( char *X, char *Y, ll m, ll n ){

	if ( m == 0 || n == 0 ) return 0;

	if ( X[m-1] == Y[n-1] ) return 1 + LCSRecursive(X, Y, m - 1, n - 1);

	else return max(LCSRecursive(X, Y, m, n - 1), LCSRecursive(X, Y, m - 1, n));
}

ll LCSMemoization(char* X, char* Y, int m, int n){

	if (m == 0 || n == 0) return 0;

	if (X[m - 1] == Y[n - 1]) return dp[m][n] = 1 + LCSMemoization(X, Y, m - 1, n - 1);

	if (dp[m][n] != -1) return dp[m][n];
	
	return dp[m][n] = max(LCSMemoization(X, Y, m, n - 1),
						LCSMemoization(X, Y, m - 1, n));
}


ll LCSTabulation(char* X, char* Y, ll m, ll n){

	ll L[m + 1][n + 1];
	
	for (ll i = 0; i <= m; i++){
		for (ll j = 0; j <= n; j++){

			if (i == 0 || j == 0)L[i][j] = 0;

			else if (X[i - 1] == Y[j - 1])L[i][j] = L[i - 1][j - 1] + 1;

			else L[i][j] = max(L[i - 1][j], L[i][j - 1]);
		}
	}

	return L[m][n];
}


int main(){
    
    FILE* fileRead;
    FILE* fileWrite;
    char X[1000], Y[1000];

    auto start = high_resolution_clock::now();

    fileRead = fopen("in.txt","r");
    fileWrite = fopen("out.txt","w");
      

    fscanf(fileRead,"%s",&X);
    fscanf(fileRead,"%s",&Y);


    ll m = strlen(X);
	ll n = strlen(Y);

    // fprintf(fileWrite,"Max Length : %lld\n",LCSRecursive( X, Y, m, n ));

    
    // for(ll i = 0 ; i < m + 1 ; i++)
    //   for(ll j = 0; j < n + 1 ; j ++)  dp[i][j] = -1;

    // fprintf(fileWrite,"Max Length : %lld\n",LCSMemoization( X, Y, m, n ));


    fprintf(fileWrite,"Max Length : %lld\n",LCSTabulation( X, Y, m, n ));


    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    fprintf(fileWrite,"Time Taken : %ld ms",duration.count());

    fclose(fileRead);
    fclose(fileWrite);
}
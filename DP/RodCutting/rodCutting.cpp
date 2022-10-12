#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

#define ll long long
const int INF = 100000;

ll rodCuttingRecursive(ll price[], ll index, ll size){
	
    // Base
	if (index == 0) return  price[0] * size;
	
	ll cut = INT_MIN;
	ll notCut = rodCuttingRecursive(price,index - 1,size);
	ll rodLen = index + 1;

	if (rodLen <= size) cut = price[index] + rodCuttingRecursive(price,index,size - rodLen);

	return max(notCut, cut);
}



void init_r(ll r[],ll size) {
  ll i;
  r[0] = 0;
  for(i = 1; i <= size ; i++) r[i] = -1*INF;
}

ll rodCuttingMemoization(ll price[], ll size, ll r[]) {

  if (r[size] >= 0) return r[size];

  ll max_revenue = -1*INF;

  for(ll i = 1; i <= size; i++) max_revenue = max(max_revenue, price[i] + rodCuttingMemoization(price, size - i,r));

  r[size] = max_revenue;

  return r[size];
}


ll rodCuttingTabulation(ll price[], ll size) {

  ll r[size + 1];
  r[0] = 0;

  for(ll j = 1; j <= size; j++) {

    ll maximum_revenue = -1 * INF;

    for(ll i = 1; i <= j; i++) maximum_revenue = max(maximum_revenue, price[i] + r[j-i]);
    
    r[j] = maximum_revenue;
  }
  return r[size];
}

int main(){
    

    ll n ;
    FILE* fileRead;
    FILE* fileWrite;

    auto start = high_resolution_clock::now();

    fileRead = fopen("Lin.txt","r");
    fileWrite = fopen("out.txt","w");
      

    fscanf(fileRead,"%lld",&n);



    ll price[n + 1];
    ll rod[n + 1];

    // for(ll i = 0 ; i < n ; i++) fscanf(fileRead,"%lld",&price[i]);
    // fprintf(fileWrite,"Max Value : %lld\n",rodCuttingRecursive(price,n - 1,n));


    // price[0] = 0;

    // for(ll i = 1 ; i <= n ; i++) fscanf(fileRead,"%lld",&price[i]);

    // init_r(rod,n);

    // fprintf(fileWrite,"Max Value : %lld\n",rodCuttingMemoization(price,n ,rod));



    price[0] = 0;
    for(ll i = 1 ; i <= n ; i++) fscanf(fileRead,"%lld",&price[i]);
    fprintf(fileWrite,"Max Value : %lld\n",rodCuttingTabulation(price,n));






    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);


    fprintf(fileWrite,"Time Taken : %ld ms",duration.count());


    fclose(fileRead);
    fclose(fileWrite);
   
}
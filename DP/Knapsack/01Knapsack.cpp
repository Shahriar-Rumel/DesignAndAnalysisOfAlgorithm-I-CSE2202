#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace std::chrono;


// 01Knapsack with Recursion(No Optimization),Tabulation(Bottom Up) & Memoization(Top Down)

int dp[1001][100001];


int knapSackRecursive(int weightList[],int valueList[],int capacity,int size) {

    //Base Case
    
    if(size == 0 || capacity == 0) return 0;

    //Current Item weight is greater than capacity

    if( weightList[size-1] > capacity) return knapSackRecursive(weightList, valueList ,capacity, size-1);

    //Current Item weight is smaller than capacity and now check if adding it makes the result maximum or not

    else  return max(
        knapSackRecursive(weightList, valueList ,capacity - weightList[size - 1], size - 1) + valueList[ size - 1],
        knapSackRecursive(weightList, valueList , capacity, size - 1)) ;

    
}




int knapSackMemoization(int weightList[],int valueList[],int capacity,int size) {

    //Base Case
    
    if(size < 0 ) return 0;

    if( dp[size][capacity] != -1 ) return dp[size][capacity] ;
     

    //Current Item weight is greater than capacity

    if( weightList[size] > capacity ){

        dp[size][capacity] = knapSackMemoization(weightList, valueList ,capacity, size-1);
        return dp[size][capacity] ;

    } 

    //Current Item weight is smaller than capacity and now check if adding it makes the result maximum or not

    else  {

        dp[size][capacity]= max( knapSackMemoization(weightList, valueList ,capacity - weightList[size - 1], size - 1) + valueList[ size ],
        knapSackMemoization(weightList, valueList , capacity, size - 1)) ;

        return dp[size][capacity];
    }
    
}


int knapSackTabulation(int weightList[],int valueList[],int capacity,int size) {

    //initialization
    
    int ans[size + 1][capacity + 1]; 

    //Current Item weight is greater than capacity

    for(int i  = 0 ; i <= size ; i++){

        for(int j = 0 ; j <= capacity ; j++){

            if(i == 0 || j == 0) ans[i][j] = 0;

            else if (weightList[i-1] <= j) ans[i][j] = max( ans[i-1][j- weightList[i-1]]  + valueList[ i - 1 ], ans[i-1][j]) ;

            else ans[i][j] = ans[i-1][j];
        }
       
    }

    return ans[size][capacity];
    
}

int main(){

    
    int W ;
    int n ;
    FILE* fileRead;
    FILE* fileWrite;

    auto start = high_resolution_clock::now();

    fileRead = fopen("input.txt","r");
    fileWrite = fopen("output.txt","w");
      

    fscanf(fileRead,"%d %d",&n,&W);



    int value[1005];
    int weight[1005];

    for(int i = 0 ; i < n ; i++) fscanf(fileRead,"%d",&weight[i]);
    for(int i = 0 ; i < n ; i++) fscanf(fileRead,"%d",&value[i]);



    // fprintf(fileWrite,"Max Value : %d\n",knapSackRecursive(weight,value,W,n));


    //   for(int i = 0 ; i < n ; i++)
    //     for(int j = 0; j < W + 1 ; j++)  dp[i][j] = -1;

    // fprintf(fileWrite,"Max Value : %d\n",knapSackMemoization(weight,value,W,n-1));


    fprintf(fileWrite,"Max Value : %d\n",knapSackTabulation(weight,value,W,n));


    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);


    fprintf(fileWrite,"Time Taken : %ld ms",duration.count());


    fclose(fileRead);
    fclose(fileWrite);
   
}
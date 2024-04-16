#include <bits/stdc++.h>
using namespace std;
//All pair shortest paths
#define max 10
int infi = 999;
void allpairshort(int a[max][max], int n){
    int i, j, k;
    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (a[i][k] + a[k][j] < a[i][j])
                {
                    a[i][j] = a[i][k] + a[k][j];
                }
            }
        }
    }
    cout<<"All Pair Shortest Paths:-\n";
    int maxi = 0;
    for(i=0; i<n; i++){
    for(j=0; j<n; j++){
    cout<<a[i][j]<<" ";
    if(a[i][j] > maxi && a[i][j] < infi)
    maxi = a[i][j];
    }
    cout<<"\n";
    }
    cout<<"----------------------\nDiameter of Graph is:- "<<maxi<<endl;
    
}
int main()

{
    int i, j, n =5;
    int a[][10] =  {{0, 30, infi, 5, 100},
                    {30, 0 , 50, infi, infi},
                    {infi, 50 , 0, 5, 10},
                    {5, infi , 5, 0, 60},
                    {100, infi , 10, 60, 0},
                };
    cout<<"Original Graph:-\n";
    for(i=0; i<n; i++){
    for(j=0; j<n; j++){
    cout<<a[i][j]<<" ";
    }
    cout<<"\n";
    }
    allpairshort(a, 5);
    cout<<"Let's introduce a wormhole in the graph and check whether the shortest paths change!!!";
    a[4][1] = 5;
    a[1][4] = 5;
    allpairshort(a, 5);
    return 0;
}

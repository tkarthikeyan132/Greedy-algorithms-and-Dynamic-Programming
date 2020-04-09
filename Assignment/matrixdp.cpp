#include<iostream>
#include<bits/stdc++.h>
using namespace std;
void printi(int x,int y,vector<vector<int>> sarr);
int main()
{
    int n,x,y,j,q;
    cout << "Enter the number of matrices : ";
    cin >> n;
    int p[n+1];
    for(int i = 1; i <= n; i++)
    {
        cout << "Enter the order of matrix "<<i<<" : ";
        cin >> x >> y;
        if(i == 1)
        {
            p[i-1] = x;
        }
        p[i] = y;
    }
    int arr[n+1][n+1];
    vector<vector<int>>sarr(n+1);
    //initialising array
    for(int i = 0; i < n+1; i++)
    {
        sarr[i].resize(n+1);
        for(int j = 0; j < n+1; j++)
        {
            arr[i][j] = 0;
            sarr[i][j] = -1;
        }
    }
    for(int l = 2; l <= n; l++)
    {
        for(int i = 1; i <= (n-l+1); i++)
        {
            j = i + l - 1;
            arr[i][j] = INT32_MAX;
            for(int k = i; k <= (j-1); k++)
            {
                q = arr[i][k] + arr[k+1][j] + p[i-1]*p[k]*p[j];
                if(q < arr[i][j])
                {
                    arr[i][j] = q;
                    sarr[i][j] = k;
                }
            }
        }
    }
    cout << "result" << endl;
    /* final matrix 
    for(int i = 0; i < n+1; i++)
    {
        for(int j = 0; j < n+1; j++)
            cout << arr[i][j] << "(" << sarr[i][j] <<") ";
        cout << endl;
    } */
    cout << "Total multiplications : "<< arr[1][n] << endl;  
    cout << "chain order ( bottom to top ): "<<endl; 
    printi(1,n,sarr);
    return 0;
}
void printi(int x,int y,vector<vector<int>>sarr)
{
    int k = sarr[x][y];
    if(x != y)
    {
        for(int i = x; i <=y; i++ )
            cout << i <<",";
        cout << endl;
        printi(x,k,sarr);
        printi(k+1,y,sarr);
    }
}
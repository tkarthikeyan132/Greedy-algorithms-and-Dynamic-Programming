#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class object
{
    public:
    int weight;
    int profit;
};
class extra
{
    public:
    int indicator;
    int xp;
    int yp;
};
int main()
{
    int W,n;
    cout << "Enter the number of objects : ";
    cin >> n;
    object obj[n+1];
    for(int w = 1; w <= n; w++)
    {
        int x,y;
        cout << "Enter the weight and profit of object "<<w<<" : ";
        cin >> x >> y;
        obj[w].weight = x;
        obj[w].profit = y;
    }
    cout << "Enter the weight capacity of knapsack : ";
    cin >> W;
    int arr[n+1][W+1]; // actual matrix
    extra ext[n+1][W+1];
    //initialising extra matrix
    for(int e = 0 ; e < n+1; e++)
        for(int f = 0; f < W+1; f++)
        {
            ext[e][f].xp = -1;
            ext[e][f].yp = -1;
            ext[e][f].indicator = -1;
        }    
    set<int>objlist;
    for(int i = 0; i<W+1; i++)
        arr[0][i] = 0;
    for(int i = 1; i <= n; i++)
    {
        int wei = obj[i].weight;
        for(int w = 0; w <= W; w++)
        {
            if( w < wei)
            {
                arr[i][w] = arr[i-1][w];
                ext[i][w].xp = i-1;
                ext[i][w].yp = w;
            } 
            else
            {
                int t1 = arr[i-1][w];
                int t2 = obj[i].profit + arr[i-1][w-wei];
                if(t1 < t2)
                {
                    arr[i][w] = t2;
                    ext[i][w].indicator = i;
                    ext[i][w].xp = i-1;
                    ext[i][w].yp = w-wei;
                }
                else
                {
                    arr[i][w] = t1;
                    ext[i][w].xp = i-1;
                    ext[i][w].yp = w;
                }
            }
        }
    }
    cout << "result "<<endl;
    /* final matrix 
    for(int i = 0; i < n+1; i++)
    {
        for(int j = 0; j < W+1; j++)
            cout << arr[i][j] <<" ";
        cout << endl;
    }
    */
    extra tempo=ext[n][W];
    while(!(tempo.xp==-1&&tempo.yp==-1))
    {
        int s,d;
        s = tempo.xp;
        d = tempo.yp;
        if(tempo.indicator>0)
            objlist.insert(tempo.indicator);
        tempo=ext[s][d];
    }
    cout << "objects taken : ";
    for(auto i = objlist.begin(); i != objlist.end(); i++)
        cout << *i << " ";
    cout << "profit earned : "<<arr[n][W]<<endl;
    return 0;
}
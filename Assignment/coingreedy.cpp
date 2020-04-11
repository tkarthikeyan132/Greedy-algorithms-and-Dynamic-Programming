#include<iostream>
#include<bits/stdc++.h>
using namespace std;
set<int> merge(set<int> s1,set<int> s2);
int main()
{
    int n,x;
    cout << "Enter the number of denominations : ";
    cin >> n;
    int denomination[n];
    cout << "Enter the denominations : ";
    for(int i = 0; i < n; i++)
    {
        cin >> denomination[i];
    }
    cout << "Enter the value : ";
    cin >> x;
    set<int>useddenom[x+1];
    int D[x+1];
    int C[x+1];
    // D[i] = 0 implies i cannot be obtained using given denominations
    // D[i] = 1 implies i can be obtained using given denominations
    // C[i] denotes number of minimum denominations to obtain i
    D[0] = 1;
    int flag = 0;
    for( int s = 1; s <= x; s++)
        D[s] = 0;
    sort(denomination,denomination+n);
    for(int i = 0; i < n; i++)
    {
        int curd = denomination[i];
        for( int j = curd; j <= x; j++)
        {
            if(D[j]==0)
            {
                D[j] = D[j-curd];
                if(D[j] == 1)
                {
                    useddenom[j] = merge( useddenom[j], useddenom[j-curd]);
                    useddenom[j].insert(curd);
                }
            }
            if( D[x] == 1)
            {
                flag = 1;
                break;
            }
        }
        if(flag == 1)
            break;
    }
    cout << "Minimum number of denominations used to obtain " << x << " is " <<useddenom[x].size() << endl;
    cout << "Denominations used are ";
    for(auto k = useddenom[x].begin(); k != useddenom[x].end(); k++)
    {
        cout << *k << ", ";
    } 
    return 0;
}
set<int> merge(set<int> s1,set<int> s2)
{
    set<int>temp;
    int x,y;
    for(auto i = s1.begin(); i != s1.end(); i++)
        temp.insert(*i);
    for(auto i = s2.begin(); i != s2.end(); i++)
        temp.insert(*i);
    return temp;    
}
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int Count(vector<int> v,int u);
int distinct(vector<int> v);
int main()
{
    int n,x;
    cout << "Enter the number of denominations : ";
    cin >> n;
    int denomination[n];
    int restriction[n];
    cout << "Enter the denomination di and corresponding li : ";
    for(int i = 0; i < n; i++)
    {
        cin >> denomination[i] >> restriction[i];
    }
    cout << "Enter the value : ";
    cin >> x;
    vector<int>denomlist[x+1];
    int D[x+1];
    // D[i] = 0 implies i cannot be obtained using given denominations
    // D[i] = 1 implies i can be obtained using given denominations
    D[0] = 1;
    int flag = 0;
    for( int s = 1; s <= x; s++)
        D[s] = 0;
    for(int i = 0; i < n; i++)
    {
        int d = denomination[i];
        if(Count(denomlist[d],d) < restriction[i] && d <= x)
        {
            denomlist[d].push_back(d);
            D[d] = 1;
        }
    }
    for(int i = n-1; i > 0; i--)
    {
        for(int j = 0; j < i; j++ )
        {
            if(denomination[j] > denomination[j+1])
            {
                denomination[j] = denomination[j] ^ denomination[j+1];
                denomination[j+1] = denomination[j] ^ denomination[j+1];
                denomination[j] = denomination[j] ^ denomination[j+1];
                restriction[j] = restriction[j] ^ restriction[j+1];
                restriction[j+1] = restriction[j] ^ restriction[j+1];
                restriction[j] = restriction[j] ^ restriction[j+1];
            }
        }
    }
    for(int i = n-1; i >= 0; i--)
    {
        int curd = denomination[i];
        if(curd > x)
            break;
        for( int j = curd; j <= x; j++)
        {
            if(D[j]==0 && Count(denomlist[j-curd],curd) < restriction[i])
            {
                D[j] = D[j-curd];
                if(D[j] == 1)
                {
                    denomlist[j] = denomlist[j-curd];
                    denomlist[j].push_back(curd);
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
    if(flag == 0)
        cout << "Amount cannot be paid" << endl;
    else
    {
        cout << "Minimum number of denominations used to obtain " << x << " is " <<distinct(denomlist[x]) << endl;
        cout << "Denominations used are ";
        for(auto k = denomlist[x].begin(); k != denomlist[x].end(); k++)
        {
            cout << *k << ", ";
        }
    }
    return 0;
}
int Count(vector<int> v,int u)
{
    int sum = 0;
    for(int i = 0; i < v.size(); i++)
    {
        if(v[i] == u)
            sum++;
    }
    return sum;
}
int distinct(vector<int> v)
{
    set<int> s;
    for(int i=0;i<v.size();i++)
        s.insert(v[i]);
    return s.size();
}
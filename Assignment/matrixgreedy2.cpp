#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class matrix
{
    public:
    string name;
    int id;
    int m;
    int n;
};
class bmatrix
{
    public:
    string name;
    int id;
    string arrayname1;
    int arrayid1;
    string arrayname2;
    int arrayid2;
    int m;
    int n;
};
int main()
{
    int n;
    cout << "Enter the number of matrices : ";
    cin >> n;
    matrix A[n];
    bmatrix B[n-1];
    for(int i=0; i<(n-1); i++)
    {
        A[i].id=i;
        A[i].name="A";
        B[i].name="B";
        B[i].id=i;
    }
    A[n-1].id=n-1;
    A[n-1].name="A";
    for(int i = 0; i<n ; i++)
    {
        int x,y;
        cout << "Enter the order of matrix "<<i<<" : ";
        cin >> x >> y;
        A[i].m = x;
        A[i].n = y;
    }
    vector<matrix>temp(n);
    for(int i=0; i<n; i++)
        temp[i] = A[i];
    for(int u=n-1;u>0;u--) // n-1 stages
    {
        int un=n-1-u; //negated u (u goes from n-1 to 1 and un goes from 0 to n-2)
        int max=(temp[0].n);
        int maxsec=(temp[0].m)*(temp[1].n);
        int maxi=0;
        for(int i=0;i<u;i++)
        {
            int w,ws;
            w=(temp[i].n);
            ws=(temp[i].m)*(temp[i+1].n);
            if(w>=max&&ws<maxsec)
            {
                max = w;
                maxsec = ws;
                maxi = i;
            }
        }
        B[un].arrayid1=temp[maxi].id;
        B[un].arrayname1=temp[maxi].name;
        B[un].arrayid2=temp[maxi+1].id;
        B[un].arrayname2=temp[maxi+1].name;
        B[un].m=temp[maxi].m;
        B[un].n=temp[maxi+1].n;
        //--------------------
        temp[maxi].name=B[un].name;
        temp[maxi].id=B[un].id;
        temp[maxi].m=B[un].m;
        temp[maxi].n=B[un].n;
        temp.erase(temp.begin()+maxi+1);
    }
    cout <<"result"<<endl;
    for(int i=0;i<n-1;i++)
    {
        cout << B[i].name<<B[i].id<<" : "<<B[i].arrayname1<<B[i].arrayid1<<" x "<<B[i].arrayname2<<B[i].arrayid2<<"   ";
        cout << B[i].m <<" x "<< B[i].n<<endl;
    }
    return 0;
}
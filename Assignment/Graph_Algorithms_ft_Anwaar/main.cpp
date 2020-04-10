#include"graph.h"
#include<iostream>
#include <bits/stdc++.h> 
using namespace std;

int main()
{
    Graph G;
    int s;
    cout << "For Flyod_Warshall(All pairs spath using DP) Enter 1\nFor All pairs spath Greedy approach(using Dijkstras) Enter 2\nFor Bellmanford Enter 3\n";
    cin >> s;
    switch (s)
    {
        case 1:
            Flyod_Warshall(G);
            break;
        case 2:
            all_pair_shortest(G);
            break;
        case 3:{
            int r;
            cout << "Enter the source vertex to run Bellmanford: ";
            cin >> r;
            BellmanFord(G, r);
            break;}
        
        default:
            cout << "INVALID INPUT, TRY AGAIN." << endl;
            break;
    }
}
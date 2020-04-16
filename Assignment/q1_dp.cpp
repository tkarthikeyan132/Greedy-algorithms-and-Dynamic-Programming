#include<iostream>
#include<vector>
#include <bits/stdc++.h>
using namespace std;
int Extract(vector<vector<int>>M ,int row, int column, vector<int>*result, int deno[]);

int main()
{

    //prompt for denominations
    cout<<"Enter no. of denominations : ";
    int k,i,x,j;
    cin>>k;
    int deno[k];
    cout<<"Enter the denominations"<<endl;
    for(i=0; i<k ; i++)
    {
        cout<<"Enter "<<i<<"th denomination:";
        cin>>deno[i];

    }
     cout<<"Enter the value of x: ";
     cin>>x;

     //algo start
     //create matrix of dimesions k x (x+1)
       vector<vector<int>> M;
    M.resize(k, vector<int>(x+1,0));

     //initilize first row
     M[0][0]= 0;
     for(i=1; i<x+1 ; i++)
     {
         if(i>=deno[0])
         M[0][i] = 1 + M[0][i-deno[0]];
         else
         M[0][i] = INT16_MAX;
     }

     //start filling the matrxi
     for(i=1; i<k; i++)
     for(j=0; j<x+1 ; j++)
     {
         if(j==0)
         M[i][0] = 0; //first column is all zeros
         else
         {
             if(j-deno[i]>=0)
             M[i][j] = min (1+M[i][j-deno[i]], M[i-1][j]);
             else
             M[i][j]=  M[i-1][j];
         }

     }

     //now , extract all the solutions
     ///from the last column
     vector<int> result; ///contains current solution
    vector< pair <int, vector <int>>>solutions[k]; //contains all solutions possible along with no. of denominaations used
     for(i=0; i<k ; i++)
     {
     if( Extract(M,i,x,&result,deno) != INT16_MAX)
    {
        int sum = 0;
        int temp; vector <int> tempo; int index=0,  counter=0;
        while(!result.empty())
        {
            temp = result.back(); result.pop_back();
            if(index ==0)
            {
             tempo.push_back(temp);
             index++;
             counter++;
            }
             else
             {
                 if(tempo[index-1]==temp)
                 {
                     tempo.push_back(temp);
                     index++;
                 }
                 else
                 {
                     tempo.push_back(temp);
                     index++; counter++;
                 }
                 
             }
            sum+= temp;
            if(sum ==x) //current solution is ready
            {
                sum =0;  index=0;
                solutions->push_back(make_pair(counter,tempo));
                counter=0;
                tempo.clear();

            }
         }
    }
     }


     int min= INT16_MAX;
     for( auto it= solutions->begin();it!= solutions->end(); it++ )
     {
         if(min>it->first)
         min = it->first;

     }


//now print all solutions using min denominations
     vector<int> temp;
     for( auto it= solutions->begin();it!= solutions->end(); it++ )
     {
         if(it->first==min)
         {
             cout<<"Denomination used = "<<min<<endl;
             cout<<"Give change as: ";
             temp= it->second;
             while(!temp.empty())
        {
          cout<<temp.back()<<"+"; temp.pop_back();
        }
        cout<<endl;

         }

     }






while(1)
{
    ;
}


}

int Extract(vector<vector<int>>M ,int row, int column, vector<int>*result, int deno[])
{
    if(M[row][column]== INT16_MAX)
    return INT16_MAX;
    if(column<0)
    return INT16_MAX;
    if(M[row][column]==0)
    return 0;

    else
    {
        if(row==0)
        {
            if(Extract(M,row,column-deno[row],result,deno)!= INT16_MAX)
            {
            result->push_back(deno[row]);
            return 0;
            }
        }
        else
        {

        if(M[row][column]==M[row-1][column]) ///multiple solutions may be possible
        {
            if(Extract(M,row,column-deno[row],result,deno)!= INT16_MAX) //check if it's possible to include current
            result->push_back(deno[row]);
            return(Extract(M,row-1,column,result,deno));
        }
        else
        {
            if(Extract(M,row,column-deno[row],result,deno)!= INT16_MAX)
            {
                result->push_back(deno[row]);
                return 0;
            }
        }
        return INT16_MAX;

        }

    }
    return INT16_MAX;


}

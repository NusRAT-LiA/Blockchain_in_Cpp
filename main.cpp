#include<bits/stdc++.h>
#include "Sha256_Algorithm/Sha256.h"
#include "Eliptic_Curve_Cryptography/GeneratePoint.h"
using namespace std;

int main()
{  
    cout<<"\n The hash -\n ";
    cout<<Hash("Nursat jahan Lia")<<endl;
   pair<long long int , long long int > result ;
   
   result=generateKey("Alice");
   cout<<"PublicKey :  "<<result.first<<"\t"<<result.second<<endl;
}
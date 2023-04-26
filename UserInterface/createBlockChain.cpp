#include<bits/stdc++.h>
#include"../structure/BlockChain.h"
using namespace std ;

int main()
{   
    string chainName;
    int chainDifficulty;

    cout<<"\t\t\t\tEnter the name of your BlockChain\t\t\t\t"<<endl;
    cin>>chainName;
    chainName=chainName+"Chain";

    cout<<"\t\t\t"<<"Set the mining difficulty (eg. 4) of "<<chainName<<"\t\t\t"<<endl;
    cin>>chainDifficulty;
    


    Blockchain newChain(chainDifficulty,chainName);
    cout<<"\t\t\t\t"<<newChain.chainName<<" initiated !! "<<"\t\t\t\t"<<endl;

}

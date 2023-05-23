
#include<bits/stdc++.h>
#include"../structure/BlockChain.h"
#include"attackBlockChain.h"
#include"createBlockChain.h"
#include"inspectBlockChain.h"
using namespace std ;

Blockchain myBlockChain ;
bool isBlockCreated=false;
// Function type definition
typedef function<void()> VoidFunction;
map<int, VoidFunction> functionMap;

void createChain()
{
  myBlockChain=createBlockChain();
  isBlockCreated=true;
}

void attackchain()
{ 
  if(!isBlockCreated)
  {
    cout<<"You did not create any Blockchain yet ! Try creating first !"<<endl;
    createChain();
    return;
  }
  attackChain(myBlockChain);
}

void inspectChain()
{
 if(!isBlockCreated)
  {
    cout<<"You did not create any Blockchain yet ! Try creating first !"<<endl;
    createChain();
    return;
  }

  inspectMyChain(myBlockChain); 
}
int main()
{  

  
  cout<<"\n\t\t\tWelcome to BlockChainEd!\t\t\t\n"<<endl;

   functionMap[1]=createChain;
   functionMap[2]=inspectChain;
   functionMap[3]=attackchain;
   

  while(true)
  {
    int choice ;
      cout<<"\n*************************"<<endl;
      cout<<"Choose from options : \n"<<endl;
      cout<<"1 . Create  BlockChain \n"<<endl;
      cout<<"2 . Inspect BlockChain \n"<<endl;
      cout<<"3 . Attack BlockChain\n"<<endl;
      cout<<"4 . Exit \n"<<endl;
      cout<<"*************************"<<endl;
      cin>>choice;

       if(choice>4 || choice<1)
      {
         cout<<"Invalid Option choice ! Try again !\n"<<endl;
         continue;
      }
      
      if(choice==4)break;

      functionMap[choice]();


  }   
}
#include<bits/stdc++.h>
#include"../structure/BlockChain.h"
#include <unistd.h>
#include"../structure/Block.h"
#include"../structure/Wallet.h"
#include"../structure/Transaction.h"
#include"../structure/Miner.h"
#include"Printings.h"
using namespace std ;

Block attackedBlock;
Transaction attackedTransaction ;
bool doExit = false ;

// Function type definition
typedef std::function<void()> VoidFunction;
map<int, VoidFunction> functionMap;



void ChangeSenderPublicKey()
{
   cout<<"X : "<<endl;
   cin>>attackedTransaction.PublicKeyOfSenderWallet.first;
   cout<<"Y : "<<endl;
   cin>>attackedTransaction.PublicKeyOfSenderWallet.second;
}

void ChangeRecieverPublicKey()
{
   cout<<"X : "<<endl;
   cin>>attackedTransaction.PublicKeyOfRecieverWallet.first;
   cout<<"Y : "<<endl;
   cin>>attackedTransaction.PublicKeyOfRecieverWallet.second;
}

void ChangeSenderPrivateKey()
{
   cout<<"Enter new signature : "<<endl;
   cin>>attackedTransaction.Signature;
}

void ChangeSentAmout()
{
   cout<<"Amount : "<<endl;
   cin>>attackedTransaction.AmountSent;
}

void Exit()
{
   doExit=true;
}


void attackChain(Blockchain myChain)
{  
   int TxIndex;
   int blockIndex;

   while(true)
   {
    
    try
    {

     cout<<"Enter the index of valid Block you want access to : "<<endl;
     cin>>blockIndex;
     
     attackedBlock = myChain.getBlock(blockIndex);

     break;
    }
    catch(const out_of_range& e)
    {
      cout<<"No Block Found ! Try again !"<<endl;
    }

   }
    
     
     cout<<"The block : \n"<<endl;
     printBlock(attackedBlock);

     
  while(true)
   {
    
    try
    {

     cout<<"Enter the index(starting from 1) of valid Transaction in the block you want access to : "<<endl;
     cin>>TxIndex;

     attackedTransaction=attackedBlock.getTransaction(TxIndex);

     break;
    }
    catch(const out_of_range& e)
    {
      cout<<"No Transaction Found ! Try again !"<<endl;
    }
    
   }
   
   functionMap[1]=ChangeSenderPublicKey;
   functionMap[2]=ChangeRecieverPublicKey;
   functionMap[3]=ChangeSenderPrivateKey;
   functionMap[4]=ChangeSentAmout;


   while(!doExit)
   {  
      int choice ;
      cout<<"Choose from options : "<<endl;
      cout<<"1 . Change Sender's   Public Key "<<endl;
      cout<<"2 . Change Reciever's Public Key "<<endl;
      cout<<"3 . Change Sender's   Private Key"<<endl;
      cout<<"4 . Change sentAmout"<<endl;
      cout<<"5 . Exit "<<endl;
      cin>>choice;

      if(choice>5 || choice<1)
      {
         cout<<"Invalid Option choice ! Try again !"<<endl;
         continue;
      }
      
      functionMap[choice]();
   }

   myChain.setBlock(blockIndex,attackedBlock,TxIndex,attackedTransaction);

   printBlockChain(myChain);


}
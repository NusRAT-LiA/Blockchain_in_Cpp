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
   cout<<"X : \n"<<endl;
   cin>>attackedTransaction.PublicKeyOfSenderWallet.first;
   cout<<"Y : \n"<<endl;
   cin>>attackedTransaction.PublicKeyOfSenderWallet.second;
}

void ChangeRecieverPublicKey()
{
   cout<<"X : \n"<<endl;
   cin>>attackedTransaction.PublicKeyOfRecieverWallet.first;
   cout<<"Y : \n"<<endl;
   cin>>attackedTransaction.PublicKeyOfRecieverWallet.second;
}

void ChangeSenderPrivateKey()
{
   cout<<"Enter new signature : \n"<<endl;
   cin>>attackedTransaction.Signature;
}

void ChangeSentAmout()
{
   cout<<"Amount : \n"<<endl;
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

     cout<<"Enter the index of valid Block you want access to : \n"<<endl;
     cin>>blockIndex;
     
     attackedBlock = myChain.getBlock(blockIndex);

     break;
    }
    catch(const out_of_range& e)
    {
      cout<<"No Block Found ! Try again !\n"<<endl;
    }

   }
    
     
     cout<<"The block : \n\n"<<endl;
     printBlock(attackedBlock);

     
  while(true)
   {
    
    try
    {

     cout<<"Enter the index(starting from 1) of valid Transaction in the block you want access to : \n"<<endl;
     cin>>TxIndex;

     attackedTransaction=attackedBlock.getTransaction(TxIndex);

     break;
    }
    catch(const out_of_range& e)
    {
      cout<<"No Transaction Found ! Try again !\n"<<endl;
    }
    
   }
   
   functionMap[1]=ChangeSenderPublicKey;
   functionMap[2]=ChangeRecieverPublicKey;
   functionMap[3]=ChangeSenderPrivateKey;
   functionMap[4]=ChangeSentAmout;


   while(!doExit)
   {  
      int choice ;
      cout<<"Choose from options : \n"<<endl;
      cout<<"1 . Change Sender's   Public Key \n"<<endl;
      cout<<"2 . Change Reciever's Public Key \n"<<endl;
      cout<<"3 . Change Sender's   Private Key\n"<<endl;
      cout<<"4 . Change sentAmout\n"<<endl;
      cout<<"5 . Exit \n"<<endl;
      cin>>choice;

      if(choice>5 || choice<1)
      {
         cout<<"Invalid Option choice ! Try again !\n"<<endl;
         continue;
      }
      
      if(choice==5)break;

      functionMap[choice]();
   }

   myChain.setBlock(blockIndex,attackedBlock,TxIndex,attackedTransaction);

   printBlockChain(myChain);


}
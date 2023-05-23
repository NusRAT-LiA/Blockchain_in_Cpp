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


// Function type definition
typedef function<void()> VoidFunction;
map<int, VoidFunction> attackingFunctionMap;



void ChangeSenderPublicKey()
{
   cout<<"X : ";
   cin>>attackedTransaction.PublicKeyOfSenderWallet.first;
   cout<<"\n";
   cout<<"Y : ";
   cin>>attackedTransaction.PublicKeyOfSenderWallet.second;
   cout<<"\n";

}

void ChangeRecieverPublicKey()
{
   cout<<"X : ";
   cin>>attackedTransaction.PublicKeyOfRecieverWallet.first;
   cout<<"\n";

   cout<<"Y : ";
   cin>>attackedTransaction.PublicKeyOfRecieverWallet.second;
   cout<<"\n";

}

void ChangeSenderPrivateKey()
{
   cout<<"Enter new signature : ";
   cin>>attackedTransaction.Signature;
   cout<<"\n";

}

void ChangeSentAmout()
{
   cout<<"Amount : ";
   cin>>attackedTransaction.AmountSent;
   cout<<"\n";

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

     cout<<"Enter the index(starting from 1) of valid Transaction in the block you want access to : ";
     cin>>TxIndex;
     cout<<"\n";


     attackedTransaction=attackedBlock.getTransaction(TxIndex);

     break;
    }
    catch(const out_of_range& e)
    {
      cout<<"No Transaction Found ! Try again !\n"<<endl;
    }
    
   }
   
   attackingFunctionMap[1]=ChangeSenderPublicKey;
   attackingFunctionMap[2]=ChangeRecieverPublicKey;
   attackingFunctionMap[3]=ChangeSenderPrivateKey;
   attackingFunctionMap[4]=ChangeSentAmout;


   while(true)
   {  
      int choice ;
      cout<<"Choose from options : \n"<<endl;
      cout<<"1 . Change Sender's   Public Key \n"<<endl;
      cout<<"2 . Change Reciever's Public Key \n"<<endl;
      cout<<"3 . Change Sender's   Private Key\n"<<endl;
      cout<<"4 . Change sentAmout\n"<<endl;
      cout<<"5 . Exit \n"<<endl;
      cin>>choice;
      
      if(choice==5)break;

      if(choice>5 || choice<1)
      {
         cout<<"Invalid Option choice ! Try again !\n"<<endl;
         continue;
      }
      
      
      attackingFunctionMap[choice]();
   }

   myChain.setBlock(blockIndex,attackedBlock,TxIndex,attackedTransaction);

   printBlockChain(myChain);

   cout<<"\n***Exiting from Attack Mode***\n"<<endl;


}
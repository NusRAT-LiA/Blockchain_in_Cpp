#include<bits/stdc++.h>
#include"../structure/BlockChain.h"
#include <unistd.h>
#include"../structure/Block.h"
#include"../structure/Wallet.h"
#include"../structure/Transaction.h"
#include"../structure/Miner.h"
#include"Printings.h"
using namespace std ;

Blockchain BlockChain;
// Function type definition
typedef function<void()> VoidFunction;
map<int, VoidFunction> inspectingFunctionMap;
int inspectBlockInIndex;


void getWallets()
{
  for(auto i : BlockChain.Wallets)
  {
    cout<<"Wallet's  Address     : "<<i.WalletAdress<<endl;
    cout<<"Wallet's  Public  Key : "<<i.WalletOwner.PublicKey.getX()<<" "<<i.WalletOwner.PublicKey.getY()<<endl;
    cout<<"Wallet's  Balance     : "<<i.Balance<<endl;
    sleep(2);
  }
}

void getTransactions()
{
   for(auto i : BlockChain.addedTransactions)
    { 
      cout<<"| TransactionHash   -> "<<i.TxHash<<endl;
      cout<<"| SenderKeyPair     -> "<<i.PublicKeyOfSenderWallet.first<<" "<<i.PublicKeyOfSenderWallet.second<<endl;
      cout<<"| RecieverrKeyPair  -> "<<i.PublicKeyOfRecieverWallet.first<<" "<<i.PublicKeyOfRecieverWallet.second<<endl;
      cout<<"| Sent Amount       -> "<<i.AmountSent<<endl;
      cout<<"|\n";
      sleep(2);
    }
}

void getABlock()
{  
   cout<<"Enter the Block's Index : "<<endl;
   cin>>inspectBlockInIndex;
   try{
   printBlock(BlockChain.getBlock(inspectBlockInIndex));
   }
   catch(const out_of_range& e)
   {
      cout<<"No Block exists in that Index !"<<endl;
   }
    
}

void getChain()
{
  printBlockChain(BlockChain);
}

void inspectMyChain(Blockchain myChain)
{
    inspectingFunctionMap[1]=getWallets;
    inspectingFunctionMap[2]=getTransactions;
    inspectingFunctionMap[3]=getABlock;
    inspectingFunctionMap[4]=getChain;

    BlockChain=myChain;

    while(true)
   {  
      int choice ;
      cout<<"Choose from options : "<<endl;
      cout<<"1 . Check Wallets of My Chain "<<endl;
      cout<<"2 . Check Transactions in My Chain "<<endl;
      cout<<"3 . Check for a Block"<<endl;
      cout<<"4 . Check Full chain"<<endl;
      cout<<"5 . Exit "<<endl;
      cin>>choice;
    

      if(choice>5 || choice<1)
      {
         cout<<"Invalid Option choice ! Try again !"<<endl;
         continue;
      }

      if(choice==5)break;
      
      inspectingFunctionMap[choice]();
   }

   cout<<"***Exiting from Inspection Mode***"<<endl;

 
}
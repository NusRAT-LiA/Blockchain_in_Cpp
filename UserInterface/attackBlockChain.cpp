#include<bits/stdc++.h>
#include"../structure/BlockChain.h"
#include <unistd.h>
#include"../structure/Block.h"
#include"../structure/Wallet.h"
#include"../structure/Transaction.h"
#include"../structure/Miner.h"
using namespace std ;

Block attackedBlock;
Transaction attackedTransaction ;
bool doExit = false ;

// Function type definition
typedef std::function<void()> VoidFunction;
map<int, VoidFunction> functionMap;

void printBlock(Block block)
{   
    cout<<"----------------------------------------------------------------------------------------"<<endl;
    cout<<"| Index              : "<<block.index<<endl;
    cout<<"| Previous BlockHash : "<<block.previousHash<<endl;
    cout<<"| BlockHash          : "<<block.hash<<endl;
    cout<<"| Nonce              : "<<block.nonce<<endl;
    cout<<"| Difficulty         : "<<block.difficulty<<endl;
    cout<<"| MerkleRoot         : "<<block.merkleRoot<<endl;
    cout<<"| Timestamp          : \n"<<to_string(block.timestamp)<<endl;
    cout<<"|\n|\n";
    cout<<"| Transactions       : "<<endl;
    cout<<"|\n";
    for(auto i : block.transactions)
    { 
      cout<<"| Transaction Index -> "<<i.TxIndexInBlock<<endl;
      cout<<"| TransactionHash   -> "<<i.TxHash<<endl;
      cout<<"| SenderKeyPair     -> "<<i.PublicKeyOfSenderWallet.first<<" "<<i.PublicKeyOfSenderWallet.second<<endl;
      cout<<"| RecieverrKeyPair  -> "<<i.PublicKeyOfRecieverWallet.first<<" "<<i.PublicKeyOfRecieverWallet.second<<endl;
      cout<<"| Sent Amount       -> "<<i.AmountSent<<endl;
      cout<<"|\n";

    }
    cout<<"---------------------------------------------------------------------------------------"<<endl;


}

void printBlockChain(Blockchain myChain)
{  
   string validPrefix="";
   for(int i=0;i<myChain.difficulty;i++)
   {
       validPrefix+="0";
   }
   for( auto block : myChain.blocks)
   {
      printBlock(block);
      if(block.hash.substr(0,myChain.difficulty)!=validPrefix)
      cout<<"^\n|\nX\n|\nInvalid block detected ! Connection broke !\n|\nX\n|\n"<<endl;
      else
      cout<<"^\n|\n|\n";
   }

}


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
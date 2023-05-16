#include<bits/stdc++.h>
#include"../structure/BlockChain.h"
#include <unistd.h>
#include"../structure/Block.h"
#include"../structure/Wallet.h"
#include"../structure/Transaction.h"
#include"../structure/Miner.h"
using namespace std ;

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
      cout<<"| TransactionHash -> "<<i.TxHash<<endl;
      cout<<"| SenderKeyPair   -> "<<i.PublicKeyOfSenderWallet.first<<" "<<i.PublicKeyOfSenderWallet.second<<endl;
      cout<<"| RecieverrKeyPair-> "<<i.PublicKeyOfRecieverWallet.first<<" "<<i.PublicKeyOfRecieverWallet.second<<endl;
      cout<<"| Sent Amount     -> "<<i.AmountSent<<endl;
      cout<<"|\n";

    }
    cout<<"---------------------------------------------------------------------------------------"<<endl;


}

void printBlockChain(Blockchain myChain)
{
   for( auto block : myChain.blocks)
   {
      printBlock(block);
      cout<<"^\n|\n|\n";
   }

}

void changeWalletInfo(Block block)
{     
     string TxHash;
     cout<<"Enter the Transaction Hash : "<<endl;
     cin>>TxHash;

     string answerInput;

     cout<<"Do you want to change Sender Public Key ?"<<endl;
     cin>>answerInput;

     if(answerInput=="yes" || answerInput=="YES" || answerInput=="Yes")
     {
        cout<<"Enter desired pubic Key : "<<endl;
        cout<<"X : ";
     }

}


void attackChain(Blockchain myChain)
{
     cout<<"Enter the index of valid Block you want access to : "<<endl;
     int blockIndex;
     cin>>blockIndex;
     
     cout<<"The block : \n"<<endl;
     printBlock(myChain.getBlock(blockIndex));

     


}
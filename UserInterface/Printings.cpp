#include<bits/stdc++.h>
#include"../structure/BlockChain.h"
#include"../structure/Block.h"
#include"../structure/Transaction.h"
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
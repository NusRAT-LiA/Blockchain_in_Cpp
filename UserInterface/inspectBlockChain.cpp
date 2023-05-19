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
map<int, VoidFunction> functionMap;

void getWallets()
{
  for(auto i : BlockChain.Wallets)
  {
    cout<<"Wallet's  Address     : "<<i.WalletAdress<<endl;
    cout<<"Wallet's  Public  Key : "<<i.WalletOwner.PublicKey.getX()<<" "<<i.WalletOwner.PublicKey.getY()<<endl;
    cout<<"Wallet's  Balance     : "<<i.Balance<<endl;
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

    }
}

void getABlock(int index)
{
   printBlock(BlockChain.getBlock(index));
}

void getChain()
{
  printBlockChain(BlockChain);
}

void inspectMyChain(Blockchain myChain)
{
  
 
}
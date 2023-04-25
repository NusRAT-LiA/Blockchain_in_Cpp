#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <list>
#include "Block.h"
#include "Transaction.h"
#include "Wallet.h"
#include "miner.h"
using namespace std;


class Blockchain {

private:
    list<Block> blocks;
    int difficulty;
    // float miningReward;
    list<Transaction> pendingTransactions;
    list<Wallet> Wallets;
    map<pair<long long int , long long int> , Wallet > KeyMap;
    Block genesisBlock;

public:
    Blockchain(int difficulty, float miningReward);
    void createGenesisBlock();
    Block& getLatestBlock();
    void minePendingTransactions();
    float getBalanceOfAddress(std::string address);

    void addWallet(string Name)
    {
        Wallet NewWallet=Wallet(Name);
        KeyMap[make_pair( NewWallet.WalletOwner.PublicKey.getX(),NewWallet.WalletOwner.PublicKey.getY())]=NewWallet;
        Wallets.push_back(NewWallet);
    }

    void addTransaction(pair<long long int,long long int> SenderKey , pair<long long int,long long int> RecieverKey , int Amount, long long int Sign)
    {
        Transaction Tx = Transaction(SenderKey,RecieverKey,Amount,Sign);
        pendingTransactions.push_back(Tx);
    
    }

    void mineBlock(Miner miner)
    { 
      bool isInvalidTxDetected=false;  

      Block Newblock = miner.createBlock(pendingTransactions,blocks.back().hash,this->difficulty);
      this->pendingTransactions.clear();
      Newblock.index=this->blocks.size();
      if(!miner.verifyTransactions(Newblock,this->KeyMap)){isInvalidTxDetected=true;}
      miner.mineBlock(Newblock);
      this->blocks.push_back(Newblock);

    }
    
    void addBlock()
    {
        
    }
    
};

#endif /* BLOCKCHAIN_H */

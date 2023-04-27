#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include <unistd.h>

#include <list>
#include "Block.h"
#include "Transaction.h"
#include "Wallet.h"
#include "Miner.h"
using namespace std;


class Blockchain {

private:
    int difficulty;
    int miningReward;
    list<Transaction> pendingTransactions;
    list<Wallet> Wallets;
    map<pair<long long int , long long int> , Wallet > KeyMap;
    map<int,Miner> minerMap;
    Miner defaultMiner ;

public:
    list<Block> blocks;
    Block genesisBlock;

    string chainName;
    Blockchain(int difficulty, string Name)
    {
        this->difficulty=difficulty;
        this->chainName=Name;
    }
   
    Block& getLatestBlock();
    void minePendingTransactions();
    float getBalanceOfAddress(std::string address);

    void addWallet(string Name)
    {
        Wallet NewWallet(Name);
        this->KeyMap[make_pair( NewWallet.WalletOwner.PublicKey.getX(),NewWallet.WalletOwner.PublicKey.getY())]=NewWallet;
        this->Wallets.push_back(NewWallet);
    }

    void addTransaction(pair<long long int,long long int> SenderKey , pair<long long int,long long int> RecieverKey , int Amount, long long int Sign)
    {
        Transaction Tx = Transaction(SenderKey,RecieverKey,Amount,Sign);
        this->pendingTransactions.push_back(Tx);
    
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

    void createGenesisBlock()
    {   
        cout<<"Creating GenesisBlock(The first block of a blockchain)....."<<endl;sleep(2);
        cout<<"Adding a null Transaction..."<<endl;sleep(1);
        this->addTransaction(pair<long long , long long >(),pair<long long ,long  long >(),0,0);
        
        cout<<"Adding Default Miner in the chain with MinerId-0..."<<endl;sleep(1);
        this->defaultMiner=Miner(0);
        this->minerMap[0]=defaultMiner;
        cout<<"DefaultMiner adding null Transaction to a block..."<<endl;sleep(1);
        Block Newblock = defaultMiner.createBlock(pendingTransactions,"0",this->difficulty);
        this->pendingTransactions.clear();
        Newblock.index=this->blocks.size();
    
        this->genesisBlock=defaultMiner.mineBlock(Newblock);
        this->blocks.push_back(this->genesisBlock);
        cout<<"DefaultMiner Mined the Genesis Block..."<<endl;

    }
    
    void addBlock()
    {
        
    }
    
};

#endif /* BLOCKCHAIN_H */

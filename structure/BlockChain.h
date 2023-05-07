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

    Blockchain(){}
    Blockchain(int difficulty, string Name)
    {
        this->difficulty=difficulty;
        this->chainName=Name;
    }
   
    Block& getLatestBlock();
    void minePendingTransactions();
    float getBalanceOfAddress(std::string address);

    Wallet addWallet(string Name)
    {
        Wallet NewWallet=Wallet(Name);
        this->KeyMap[make_pair( NewWallet.WalletOwner.PublicKey.getX(),NewWallet.WalletOwner.PublicKey.getY())]=NewWallet;
        this->Wallets.push_back(NewWallet);
        return NewWallet;
    }
    
    void addMiner(int minerId)
    {
      Miner newMiner(minerId);
      cout<<"Miner ID "<<newMiner.getId()<<" created"<<endl;
      this->minerMap[minerId]=newMiner;
    }

    Miner getMiner(int ID)
    {
        return this->minerMap[ID];
    }

    void addTransaction(pair<long long int,long long int> SenderKey , pair<long long int,long long int> RecieverKey , int Amount, long long int Sign,int offeredFee)
    {
        Transaction Tx = Transaction(SenderKey,RecieverKey,Amount,Sign,offeredFee);
        cout<<"Transaction hash : "<<Tx.TxHash<<endl;sleep(1);
        if(this->pendingTransactions.size()>1 && this->pendingTransactions.back().TxFee>Tx.TxFee)
        {
            Transaction prevTx = this->pendingTransactions.back();
            this->pendingTransactions.pop_back();
            this->pendingTransactions.push_back(Tx);
            this->pendingTransactions.push_back(prevTx);
        }
        else
        this->pendingTransactions.push_back(Tx);
        
        //sort(this->pendingTransactions.begin(),this->pendingTransactions.end(),cmp);
    }

    void mineBlock(Miner miner)
    { 
      if(this->pendingTransactions.size()==0)
      {
        cout<<"No transaction is pending on the chain "<<endl;sleep(1);
        cout<<"Block Creation unsuccessful !"<<endl;
        return;
      }
      list<Transaction> CollecttedTx;
      int numOfCollectedTx=3;

      cout<<"Miner ID"<<miner.getId()<<" Collecting Transactions from the network with higher fees "<<endl;
      while(numOfCollectedTx--)
      {
        Transaction tx = this->pendingTransactions.back();
        CollecttedTx.push_back(tx);
        this->pendingTransactions.pop_back();
      }
      cout<<"Block being created with .."<<endl;
      for(auto i :CollecttedTx)
      {
        cout<<"Tx hash          : "<<i.TxHash<<endl;sleep(1);
      }
      cout<<"Network difficulty : "<<this->difficulty<<endl;sleep(1);
      cout<<"Previous blockhash : "<<this->blocks.back().hash<<endl;sleep(1);
      Block Newblock = miner.createBlock(CollecttedTx,this->blocks.back().hash,this->difficulty);
      Newblock.index=this->blocks.size();
      
      cout<<"Miner ID"<<miner.getId()<<"  started verifying block's transactions..."<<endl;sleep(1);
      Newblock = miner.verifyTransactions(Newblock,this->KeyMap);
      cout<<"Miner ID"<<miner.getId()<<" started mining block"<<endl;sleep(1);
      miner.mineBlock(Newblock);
      cout<<"Block mined with nonce "<<Newblock.nonce<<endl;sleep(1);

      this->blocks.push_back(Newblock);

      for(auto i :Newblock.transactions)
      { 
        cout<<"Transaction "<<i.TxHash<<"successful !"<<endl;
        this->KeyMap[i.PublicKeyOfSenderWallet].removeBalance(i.AmountSent+i.TxFee);
        cout<<"New balance of sender wallet"<<this->KeyMap[i.PublicKeyOfSenderWallet].WalletAdress<<" : "<<this->KeyMap[i.PublicKeyOfSenderWallet].getBalance();
        this->KeyMap[i.PublicKeyOfRecieverWallet].addBalance(i.AmountSent);
        cout<<"New balance of reciever wallet"<<this->KeyMap[i.PublicKeyOfRecieverWallet].WalletAdress<<" : "<<this->KeyMap[i.PublicKeyOfRecieverWallet].getBalance();
        miner.minerBalance+=i.TxFee;
        cout<<"Transaction fee "<<i.TxFee<<" added to Miner ID "<<miner.getId()<<"'s balance"<<endl;
      }

      cout<<"Block added to the chain successfully !"<<endl;    

    }

    void createGenesisBlock()
    {   
        cout<<"Creating GenesisBlock(The first block of a blockchain)....."<<endl;sleep(2);
        cout<<"Adding a null Transaction..."<<endl;sleep(1);
        this->addTransaction(pair<long long , long long >(),pair<long long ,long  long >(),0,0,10);
        
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
    
     
    
};

#endif /* BLOCKCHAIN_H */

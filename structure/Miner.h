#ifndef MINER_H
#define MINER_H

#include <bits/stdc++.h>
#include "Transaction.h"
#include "Block.h"
#include "Wallet.h"
#include "BlockChain.h"
#include "../Sha256_Algorithm/Sha256.h"
using namespace std;

class Miner {
    
 private:
       int id;

       bool validateNonce(string hash, int target) {
        for(int i = 0; i < target; i++) {
            if(hash[i] != '0') {
                return false;
            }
        }
        return true;
    }
 public:
    int minerBalance;
    Miner(){}
    Miner(int id){this->id=id;this->minerBalance=0;}
    int getId(){return this->id;}

    Block createBlock(list<Transaction> transactions,string previousHash, int difficulty)
    {
       Block newBlock = Block(transactions,previousHash,difficulty);
       return newBlock;
    }
    Block verifyTransactions(Block block,map<pair<long long int , long long int> , Wallet > KeyMap){
      for(auto i : block.transactions)
      {
        if(!(KeyMap[i.PublicKeyOfSenderWallet].isPrivKeyValid(i.Signature)))
        {
          cout<<"\nSecret Key mismatch detected in transaction ID : "<<i.TxHash<<endl;sleep(1);
          cout<<"Miner removing "<<i.TxHash<<" from the chain"<<endl;sleep(1);
          block.transactions.remove(i);
          continue;
        }
        if(!KeyMap[i.PublicKeyOfSenderWallet].isBalanceValid(i.AmountSent))
        {
          cout<<"Wallet "<<KeyMap[i.PublicKeyOfSenderWallet].WalletAdress<<" does not have sufficient balance"<<endl;sleep(1);
          cout<<"Miner removing "<<i.TxHash<<" from the chain"<<endl;sleep(1);
          block.transactions.remove(i);
          continue;
        }
        
        cout<<"Transaction : "<<i.TxHash<<" verified ! "<<endl;sleep(1);
      }

      return block;
    }

    Block mineBlock(Block block)
    { 
      cout<<"Valid block hash has to have "<<block.difficulty<<" 0s on front"<<endl;sleep(1);
      cout<<"Nonce(Number used only once) combined with blokc's information , is used to generate valid block hash"<<endl;sleep(2);

      cout<<"Miner performing computational work to find out the for the block nonce"<<endl;sleep(2);
      int target=block.difficulty;
      unsigned int nonce=0;

      while(true)
      {
        string noncestr=to_string(nonce);
        auto now = chrono::system_clock::now();
    
         // Convert to a time_t object
         time_t time =chrono::system_clock::to_time_t(now);
         string timestr=to_string(time);
         string Blockhash=block.calculateHash();
         string CandidateHash=Hash(Blockhash+noncestr+timestr);
         

         if(validateNonce(CandidateHash,block.difficulty))
         { 
          cout<<"Nonce found !"<<endl;
          block.nonce=nonce;
          block.timestamp=time;
          block.hash=CandidateHash;
          return block;
         }

         nonce++;
      }
    }
    bool isValidChain(std::vector<Block> chain);


};

#endif

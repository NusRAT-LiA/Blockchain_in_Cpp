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
       int minerBalance;

       bool validateNonce(string hash, int target) {
        for(int i = 0; i < target; i++) {
            if(hash[i] != '0') {
                return false;
            }
        }
        return true;
    }
 public:
 
    Miner(int id);
    int getId(){return this->id;}

    Block createBlock(list<Transaction> transactions,string previousHash, int difficulty)
    {
       Block newBlock = Block(transactions,previousHash,difficulty);

       return newBlock;
    }
    bool verifyTransactions(Block block,map<pair<long long int , long long int> , Wallet > KeyMap){
      for(auto i : block.transactions)
      {
        if(!(KeyMap[i.PublicKeyOfSenderWallet].isPrivKeyValid(i.Signature))){block.transactions.remove(i); return false;}
        if(!KeyMap[i.PublicKeyOfSenderWallet].isBalanceValid(i.AmountSent)){block.transactions.remove(i); return false;}
      }

      return true;
    }

    void mineBlock(Block block)
    { 
      int target=block.difficulty;
      int nonce=0;

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
          block.nonce=nonce;
          block.timestamp=time;
          block.hash=CandidateHash;
          break;
         }

         nonce++;
      }
    }
    bool isValidChain(std::vector<Block> chain);


};

#endif

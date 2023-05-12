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
    Block verifyTransactions(Block block, map<pair<long long int, long long int>, Wallet> KeyMap) {
    for (auto it = block.transactions.begin(); it != block.transactions.end();) {
        Transaction& transaction = *it; // Get a reference to the current transaction
        
        try
        {
            KeyMap.at(transaction.PublicKeyOfSenderWallet);
        }
        catch(std::out_of_range&  e)
        {   
             cout<<"In Transaction : "<<transaction.TxHash<<endl;
             cout<<"Error in finding Sender";
             cout <<"Miner removing " << transaction.TxHash << " from the chain" << endl;
             it = block.transactions.erase(it); // Remove the transaction and update the iterator
             continue;

        }

         try
        {
            KeyMap.at(transaction.PublicKeyOfRecieverWallet);
        }
        catch(std::out_of_range&  e)
        {   
             cout<<"In Transaction : "<<transaction.TxHash<<endl;
             cout<<"Error in finding Reciever"<<endl;
             cout <<"Miner removing " << transaction.TxHash << " from the chain" << endl;
             it = block.transactions.erase(it); // Remove the transaction and update the iterator
             continue;

        }
        if (!(KeyMap[transaction.PublicKeyOfSenderWallet].isPrivKeyValid(transaction.Signature))) {
            cout << "\nSecret Key mismatch detected in transaction ID: " << transaction.TxHash << endl;
            sleep(1);
            cout << "Miner removing " << transaction.TxHash << " from the chain" << endl;
            it = block.transactions.erase(it); // Remove the transaction and update the iterator
            continue;
        }

        if (!KeyMap[transaction.PublicKeyOfSenderWallet].isBalanceValid(transaction.AmountSent)) {
            cout << "Wallet " << KeyMap[transaction.PublicKeyOfSenderWallet].WalletAdress<< " does not have sufficient balance" << endl;
            sleep(1);
            cout << "Miner removing " << transaction.TxHash << " from the chain" << endl;
            it = block.transactions.erase(it); // Remove the transaction and update the iterator
            continue;
        }

        cout << "Transaction: " << transaction.TxHash << " verified!" << endl;
        sleep(1);
        ++it; // Move to the next transaction
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

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
       
       
       // Function to validate the nonce in the block hash
       bool validateNonce(string hash, int target) {
        // valid hash has to have target number of leading 0s 
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

    // Function to create a new block
    Block createBlock(vector<Transaction> transactions,string previousHash, int difficulty)
    {
       Block newBlock = Block(transactions,previousHash,difficulty);
       return newBlock;
    }
    
    // Function to verify transactions in a block
    Block verifyTransactions(Block block, map<pair<long long int, long long int>, Wallet> KeyMap)
     {

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
      unsigned int nonce=0;// initialize nonce with 0

      while(true)
      {
        string noncestr=to_string(nonce); // turn integer nonce value into string
        auto now = chrono::system_clock::now();
    
         // Convert to a time_t object
         time_t time =chrono::system_clock::to_time_t(now);
         string timestr=to_string(time);  // convert time value into string
         string Blockhash=block.calculateHash(); // Calculate block's hash without nonce and timestamp
         string CandidateHash=Hash(Blockhash+noncestr+timestr);// add nonce and respective timestamp and hash again 
         

         if(validateNonce(CandidateHash,block.difficulty)) // verify whether hash with choosen nonce and timestamp is valid
         { 
          cout<<"Nonce found !"<<endl;
          // update block with valid nonce and timestamp
          block.nonce=nonce;
          block.timestamp=time;
          block.hash=CandidateHash;
          return block;
         }

         nonce++;
      }
    }


};

#endif

#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <list>
#include <ctime>
#include<exception>
#include "Transaction.h"
#include "../Sha256_Algorithm/Sha256.h"
using namespace std;

class Block {

private:

   string calculateMerkleRoot() {
    vector<string> transactionHashes;
    
    // Push the hash of each transaction into the vector
    for (Transaction tx : this->transactions) {
        transactionHashes.push_back(tx.TxHash);
    }
    
    // Continue until only one hash remains (the Merkle root)
    while (transactionHashes.size() > 1) {
        // If the number of hashes is odd, duplicate the last hash
        if (transactionHashes.size() % 2 != 0) {
            transactionHashes.push_back(transactionHashes.back());
        }
        
        vector<string> levelHashes;
        
        // Pair up each pair of adjacent hashes and hash them together
        for (int i = 0; i < transactionHashes.size(); i += 2) {
            string concatenated = transactionHashes[i] + transactionHashes[i+1];
            string hashed = Hash(concatenated);
            levelHashes.push_back(hashed);
        }
        
        transactionHashes = levelHashes;
    }
    
    // Return the final Merkle root hash
    return transactionHashes[0];
}    
  


public:
    string previousHash;            // the hash of the previous block in the
    time_t timestamp;               // the time when the block was mined
    vector<Transaction> transactions; // Stores the list of transactions included in the block
    string hash;                    // hash of the block information
    int nonce;                      // a random value used in mining
    int index;                      // index of the block in  blockchain
    int difficulty;                 // the mining difficulty of the block(the number of 0s needed to be present in a valid block)
    string merkleRoot;              // merkle tree root hash of all the transactions done in a block

    Block() { }

    Block(vector<Transaction> transactions, string previousHash, int difficulty){
        this->transactions=transactions;
        this->previousHash=previousHash;
        this->difficulty=difficulty;
    }

    string calculateHash(){
        this->merkleRoot=calculateMerkleRoot(); // calculate merkle tree root of the block's transations
        string blockStr=this->merkleRoot+this->previousHash+to_string(this->index)+to_string(this->difficulty);//turn all the block data into string 
        return Hash(blockStr);// return hash value of block data string 
    }

    Transaction getTransaction(int index)
    {
      if(this->transactions.size()<index)
       throw out_of_range("");
       
      return this->transactions[index-1];
    }

    void setTransaction(int index , Transaction newTransaction)
    {  
       newTransaction.CalculateHash();
       this->transactions[index-1]=newTransaction;
       
       this->calculateHash();
    }


  
};

#endif /* BLOCK_H */

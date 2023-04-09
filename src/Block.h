#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <list>
#include <ctime>
#include "Transaction.h"
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
    string previousHash;
    time_t timestamp;
    list<Transaction> transactions;
    string hash;
    int nonce;
    int index;
    int difficulty;
    string merkleRoot;

    Block(list<Transaction> transactions, string previousHash, int difficulty){
        
    }

    string calculateHash(){
        this->merkleRoot=calculateMerkleRoot();
        string blockStr=this->merkleRoot+this->previousHash+to_string(this->index)+to_string(this->difficulty);
        return Hash(blockStr);
    }
    void mineBlock(int difficulty);
    bool isValid();


  
};

#endif /* BLOCK_H */

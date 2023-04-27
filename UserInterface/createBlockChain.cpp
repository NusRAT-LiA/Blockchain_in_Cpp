#include<bits/stdc++.h>
#include"../structure/BlockChain.h"
#include <unistd.h>
#include"../structure/Block.h"
using namespace std ;

void printBlock(Block block)
{   
    cout<<"----------------------------------------------------------------------------------------"<<endl;
    cout<<"| Index              : "<<block.index<<endl;
    cout<<"| Previous BlockHash : "<<block.previousHash<<endl;
    cout<<"| BlockHash          : "<<block.hash<<endl;
    cout<<"| Nonce              : "<<block.nonce<<endl;
    cout<<"| Difficulty         : "<<block.difficulty<<endl;
    cout<<"| MerkleRoot         : "<<block.merkleRoot<<endl;
    cout<<"| Timestamp          : \n"<<to_string(block.timestamp)<<endl;
    cout<<"|\n|\n";
    cout<<"| Transactions       : "<<endl;
    cout<<"|\n";
    for(auto i : block.transactions)
    { 
      cout<<"| TransactionHash -> "<<i.TxHash<<endl;
      cout<<"| SenderKeyPair   -> "<<i.PublicKeyOfSenderWallet.first<<" "<<i.PublicKeyOfSenderWallet.second<<endl;
      cout<<"| RecieverrKeyPair-> "<<i.PublicKeyOfRecieverWallet.first<<" "<<i.PublicKeyOfRecieverWallet.second<<endl;
      cout<<"| Sent Amount     -> "<<i.AmountSent<<endl;
      cout<<"|\n";

    }
    cout<<"---------------------------------------------------------------------------------------"<<endl;


}

int main()
{   
    string chainName;
    int chainDifficulty;

    cout<<"\t\t\t\tEnter the name of your BlockChain\t\t\t\t\n\n"<<endl;
    cin>>chainName;
    chainName=chainName+"Chain";

    cout<<"A block in a blockchain has to be mined in order to be added to the chain"<<endl;sleep(2);
    cout<<"[Miner] is an entity in a blockchain who solves mathmatical puzzle to meet difficulty level of a block "<<endl;sleep(2);
    cout<<"[Difficulty] of a block is the number of 0's that has to be at first of a valid block's hash"<<endl;sleep(2);
    cout<<"A [hash] of a block is is a fixed-length alphanumeric string that is calculated using the data inside the block and a hashing algorithm"<<endl;sleep(2);
    cout<<"eg . For a difficulty of 10  hash of a valid block could be 000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f"<<endl;sleep(2);

    cout<<"\t\t\t"<<"Set the mining difficulty (eg. 4) of "<<chainName<<"\t\t\t\n\n"<<endl;
    cin>>chainDifficulty;
    


    Blockchain newChain(chainDifficulty,chainName);
    cout<<"\t\t\t\t"<<newChain.chainName<<" initiated !! "<<"\t\t\t\t"<<endl;sleep(2);
    newChain.createGenesisBlock();
    printBlock(newChain.genesisBlock);


}

#include<bits/stdc++.h>
#include"../structure/BlockChain.h"
#include <unistd.h>
#include"../structure/Block.h"
#include"../structure/Wallet.h"
#include"../structure/Transaction.h"
using namespace std ;
Blockchain myChain=Blockchain();
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

void addWallet(string name)
{
   Wallet newWallet = myChain.addWallet(name);
   cout<<"Account address : "<<newWallet.WalletAdress<<" created!"<<endl;
   cout<<"Public Key is  : "<<newWallet.WalletOwner.PublicKey.getX()<<" "<<newWallet.WalletOwner.PublicKey.getY()<<endl;

}

void addTransaction()
{
   pair<long long , long long> SenderPublicKey , RecieverPublicKey;
   int AmountToBeSent;
   long long   SenderPrivateKey;
   int TxFee;

   cout<<"Sender Public Key   : ";
   cin>>SenderPublicKey.first>>SenderPublicKey.second;
   cout<<"\n";
   cout<<"Reciever Public Key : ";
   cin>>RecieverPublicKey.first>>RecieverPublicKey.second;
   cout<<"\n";
   cout<<"Amount to be sent   : ";
   cin>>AmountToBeSent;
   cout<<"\n";
   cout<<"Private Key of the Sender will work as the Digital Signature of a Transaction"<<endl;sleep(1);
   cout<<"Digital Signature   : ";
   cin>>SenderPrivateKey;
   cout<<"Offered Transaction fee : ";
   cin>>TxFee;

   myChain.addTransaction(SenderPublicKey,RecieverPublicKey,AmountToBeSent,SenderPrivateKey,TxFee);
  
}

void addMiner()
{  
   int numOfMiners;
   cout<<"How many miners do you want to add ?"<<endl;
   cin>>numOfMiners;
   while (numOfMiners)
   {
     myChain.addMiner(numOfMiners);
     numOfMiners--;
   }
   

}

int main()
{   
    string chainName;
    int chainDifficulty;

    cout<<"\t\t\t\tEnter the name of your BlockChain\t\t\t\t\n\n"<<endl;
    cin>>chainName;
    chainName=chainName+"Chain";

    // cout<<"A block in a blockchain has to be mined in order to be added to the chain"<<endl;sleep(2);
    // cout<<"[Miner] is an entity in a blockchain who solves mathmatical puzzle to meet difficulty level of a block "<<endl;sleep(2);
    // cout<<"[Difficulty] of a block is the number of 0's that has to be at first of a valid block's hash"<<endl;sleep(2);
    // cout<<"A [hash] of a block is is a fixed-length alphanumeric string that is calculated using the data inside the block and a hashing algorithm"<<endl;sleep(2);
    // cout<<"eg . For a difficulty of 10  hash of a valid block could be 000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f"<<endl;sleep(2);

    cout<<"\t\t\t"<<"Set the mining difficulty (eg. 4) of "<<chainName<<"\t\t\t\n\n"<<endl;
    cin>>chainDifficulty;
    


    myChain=Blockchain(chainDifficulty,chainName);
    cout<<"\t\t\t\t"<<myChain.chainName<<" initiated !! "<<"\t\t\t\t"<<endl;sleep(2);
    // myChain.createGenesisBlock();

    // cout<<" <---Genesis Block--->  "<<endl;
    // printBlock(myChain.genesisBlock);
    bool addUser=true;
    int userCount=0;

    // cout<<"Add UserWallets to your Blockchain ......"<<endl;sleep(2);
    // cout<<"When a user creates a wallet in a blockchain network, the wallet generates a pair of cryptographic keys: a public key and a private key."<<endl;sleep(2);
    // cout<<"Private Key : A secret code used to access and manage the funds stored in wallet."<<endl;sleep(2);
    // cout<<"Public Key  : Derived from the private key using complex Cryptographic function \n\t\t that Represants a wallet in open transactions in blockchain without revealing sensitive information about wallet"<<endl;sleep(3);

    // while(addUser)
    // {  
    //    string newUserName;
    //   // cout<<"Enter UserName(type \"n/a\" if you want stop adding users) : ";
    //    cin >>newUserName;

    //    if(newUserName=="n/a"){
    //     if(userCount<2){cout<<"You must add atleast two users"<<endl;sleep(1);continue;}
    //     else {addUser=false;}
    //    }
    //    addWallet(newUserName);
    //    userCount++;
    // }

    // addTransaction();

    

}
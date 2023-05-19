#include<bits/stdc++.h>
#include"../structure/BlockChain.h"
#include <unistd.h>
#include"../structure/Block.h"
#include"../structure/Wallet.h"
#include"../structure/Transaction.h"
#include"../structure/Miner.h"
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
      cout<<"| Transaction Index -> "<<i.TxIndexInBlock<<endl;
      cout<<"| TransactionHash   -> "<<i.TxHash<<endl;
      cout<<"| SenderKeyPair     -> "<<i.PublicKeyOfSenderWallet.first<<" "<<i.PublicKeyOfSenderWallet.second<<endl;
      cout<<"| RecieverrKeyPair  -> "<<i.PublicKeyOfRecieverWallet.first<<" "<<i.PublicKeyOfRecieverWallet.second<<endl;
      cout<<"| Sent Amount       -> "<<i.AmountSent<<endl;
      cout<<"|\n";

    }
    cout<<"---------------------------------------------------------------------------------------"<<endl;


}

void printBlockChain()
{
   for( auto block : myChain.blocks)
   {
      printBlock(block);
      cout<<"^\n|\n|\n";
   }

}

void addWallet()
{
   string newUserName;
   int AllocatedBalance;
   int numOfWallets;
   cout<<"How many wallets do you want do add ?"<<endl;
   cin>>numOfWallets;
   while (numOfWallets--)
   {
   cout<<"Enter UserName   : ";
   cin >>newUserName;
   cout<<"Allocate Balance :";
   cin>>AllocatedBalance;
   Wallet newWallet = myChain.addWallet(newUserName,AllocatedBalance);
   cout<<"Account address :  "<<newWallet.WalletAdress<<" created!"<<endl;
   cout<<"Public Key is   : "<<newWallet.WalletOwner.PublicKey.getX()<<" "<<newWallet.WalletOwner.PublicKey.getY()<<endl;
   }
}

void addTransaction()
{ 
   int numOfTx;
   cout<<"How many Transactions do you want to make ?"<<endl;
   cin>>numOfTx;
   while(numOfTx--)
   {
   pair<long long , long long> SenderPublicKey , RecieverPublicKey;
   int AmountToBeSent;
   long long   SenderPrivateKey;
   int TxFee;
 
   cout<<"Sender Public Key                        : ";
   cin>>SenderPublicKey.first>>SenderPublicKey.second;
   cout<<"\n";
   cout<<"Reciever Public Key                      : ";
   cin>>RecieverPublicKey.first>>RecieverPublicKey.second;
   cout<<"\n";
   cout<<"Amount to be sent                        : ";
   cin>>AmountToBeSent;
   cout<<"\n";
   cout<<"Digital Signature(Sender's PrivateKey)   : ";
   cin>>SenderPrivateKey;
   cout<<"Offered Transaction fee                  : ";
   cin>>TxFee;

   myChain.addTransaction(SenderPublicKey,RecieverPublicKey,AmountToBeSent,SenderPrivateKey,TxFee);
   }
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

void mineBlock()
{
   bool minerIdNotFound = true;
   Miner myMiner;

    while (minerIdNotFound)
    { 
      int minerId;
      cout<<"Enter Miner ID to appoint miner for mining block   :"<<endl;
      cin>>minerId;
      
      try
      {
         myMiner = myChain.getMiner(minerId);
      }
      catch (std::out_of_range&  e)
      { 
         cout<<"Minder ID not Found in your Chain ! Try again !"<<endl;
         continue;
      }

      minerIdNotFound=false;
    } 

    myChain.mineBlock(myMiner);

}

   
int main()
{   
    string chainName;
    int chainDifficulty;

    cout<<"\t\t\t\tEnter the name of your BlockChain\t\t\t\t\n"<<endl;
    cin>>chainName;
    chainName=chainName+"Chain";

   //  cout<<"A block in a blockchain has to be mined in order to be added to the chain"<<endl;sleep(2);
   //  cout<<"[Miner] is an entity in a blockchain who solves mathmatical puzzle to meet difficulty level of a block "<<endl;sleep(2);
    cout<<"[Difficulty] of a block is the number of 0's that has to be at first of a valid block's hash"<<endl;sleep(2);
   //  cout<<"A [hash] of a block is is a fixed-length alphanumeric string that is calculated using the data inside the block and a hashing algorithm"<<endl;sleep(2);
   //  cout<<"eg . For a difficulty of 10  hash of a valid block could be 000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f"<<endl;sleep(2);

    cout<<"\t\t\t"<<"Set the mining difficulty (eg. 4) of "<<chainName<<"\t\t\t\n\n"<<endl;
    cin>>chainDifficulty;
    


    myChain=Blockchain(chainDifficulty,chainName);
    cout<<"\t\t\t\t"<<myChain.chainName<<" initiated !! "<<"\t\t\t\t"<<endl;sleep(2);
    myChain.createGenesisBlock();

    cout<<" <---Genesis Block--->  "<<endl;
    printBlock(myChain.genesisBlock);
   

    cout<<"Let's star adding UserWallets to your Blockchain ......"<<endl;sleep(2);
   //  cout<<"When a user creates a wallet in a blockchain network, the wallet generates a pair of cryptographic keys: a public key and a private key."<<endl;sleep(2);
   //  cout<<"Private Key : A secret code used to access and manage the funds stored in wallet."<<endl;sleep(2);
   //  cout<<"Private Key of the Sender will work as the Digital Signature of a Transaction"<<endl;sleep(1);
   //  cout<<"Public Key  : Derived from the private key using complex Cryptographic function \n\t\t that Represants a wallet in open transactions in blockchain without revealing sensitive information about wallet"<<endl;sleep(3);
     addWallet();
  
    cout<<"Let's make Transactions !!..."<<endl;sleep(1);
    addTransaction();
    
    string ToAddMiner;
    cout<<"You already have a default miner with MinerID 0"<<endl;sleep(1);
    cout<<"Do you want to add more miners ?(YES or NO)"<<endl;
    cin>>ToAddMiner;
    if(ToAddMiner=="YES" || ToAddMiner=="yes" || ToAddMiner=="Yes")
    addMiner();

    cout<<"Let's start mining Blocks !"<<endl;
    cout<<".";sleep(1);cout<<" .";sleep(1);cout<<" ."<<endl;sleep(1);
    
    mineBlock();
   
   cout<<"Here's your chain !";
   printBlockChain();


    

}
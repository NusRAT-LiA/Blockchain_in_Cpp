#include<bits/stdc++.h>
#include"../structure/BlockChain.h"
#include <unistd.h>
#include"../structure/Block.h"
#include"../structure/Wallet.h"
#include"../structure/Transaction.h"
#include"../structure/Miner.h"
#include"Printings.h"
using namespace std ;
Blockchain myChain=Blockchain();
typedef std::function<void()> VoidFunction;
map<int, VoidFunction> CreationfunctionMap;

void addWallet()
{
   string newUserName;
   int AllocatedBalance;
   int numOfWallets;
   cout<<"How many wallets do you want do add ?"<<endl;
   cin>>numOfWallets;
   while (numOfWallets--)
   {
   cout<<"\nEnter UserName   : ";
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
   cout<<"How many Transactions do you want to make ?\n"<<endl;
   cin>>numOfTx;
   while(numOfTx--)
   {
   pair<long long , long long> SenderPublicKey , RecieverPublicKey;
   int AmountToBeSent;
   long long   SenderPrivateKey;
   int TxFee;
 
   cout<<"\nSender Public Key                        : ";
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
   cout<<"\n";
   cout<<"Offered Transaction fee                  : ";
   cin>>TxFee;
   cout<<"\n";

   myChain.addTransaction(SenderPublicKey,RecieverPublicKey,AmountToBeSent,SenderPrivateKey,TxFee);
   }
}

void addMiner()
{  
   int numOfMiners;
   cout<<"\nHow many miners do you want to add ?\n"<<endl;
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
      cout<<"Enter Miner ID to appoint miner for mining block   :\n"<<endl;
      cin>>minerId;
      
      try
      {
         myMiner = myChain.getMiner(minerId);
      }
      catch (std::out_of_range&  e)
      { 
         cout<<"Minder ID not Found in your Chain ! Try again !\n"<<endl;
         continue;
      }

      minerIdNotFound=false;
    } 

    myChain.mineBlock(myMiner);
    
    cout<<"********************"<<endl;
    cout<<"Here's your chain !\n";
    cout<<"********************"<<endl;

    printBlockChain(myChain);

}

   
Blockchain createBlockChain()
{   
    string chainName;
    int chainDifficulty;
    
    cout<<"\n\t\t\tA blockchain is a chain of connected blocks of data\t\t\n"<<endl;sleep(2);
    cout<<"\n\t\t\t\tEnter the name of your BlockChain\t\t\t\t\n\n"<<endl;
    cin>>chainName;
    chainName=chainName+"Chain";

   cout<<"\n**A block in a blockchain has to be mined in order to be added to the chain**\n"<<endl;sleep(2);
   cout<<"**[Miner] is an entity in a blockchain who solves mathmatical puzzle to meet difficulty level of a block** \n"<<endl;sleep(2);
   cout<<"**[Difficulty] of a block is the number of 0's that has to be at first of a valid block's hash**\n"<<endl;sleep(2);
   cout<<"**A [hash] of a block is is a fixed-length alphanumeric string that is calculated using the data inside the block and a hashing algorithm**\n"<<endl;sleep(3);
   cout<<"**eg . For a difficulty of 10  hash of a valid block could be 000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f**\n"<<endl;sleep(2);

    cout<<"\t\t\t"<<"Set the mining difficulty (eg. 4) of "<<chainName<<"\t\t\t\n\n"<<endl;
    cin>>chainDifficulty;
    


    myChain=Blockchain(chainDifficulty,chainName);
    cout<<"\t\t\t\t"<<myChain.chainName<<" initiated !! "<<"\t\t\t\t\n"<<endl;sleep(2);
    myChain.createGenesisBlock();

    cout<<"*************************"<<endl;
    cout<<" <---Genesis Block--->  \n"<<endl;
    cout<<"*************************"<<endl;
   
    printBlock(myChain.genesisBlock);
    sleep(3);
   
    cout<<"\n*************************************************************"<<endl;
    cout<<"\tLet's star adding UserWallets to your Blockchain"<<endl;
    cout<<"*************************************************************\n"<<endl;

    cout<<"When a user creates a wallet in a blockchain network, the wallet generates a pair of cryptographic keys: a public key and a private key.\n"<<endl;sleep(2);
    cout<<"Private Key : A secret code used to access and manage the funds stored in wallet.\n"<<endl;sleep(2);
    cout<<"Private Key of the Sender will work as the Digital Signature of a Transaction\n"<<endl;sleep(2);
    cout<<"Public Key  : Derived from the private key using complex Cryptographic function \n\t\t that Represants a wallet in open transactions in blockchain without revealing sensitive information about wallet\n"<<endl;sleep(3);
    addWallet();
    
    cout<<"\n*******************************"<<endl;
    cout<<"Let's make Transactions !!..."<<endl;sleep(1);
    cout<<"*******************************\n"<<endl;
    addTransaction();
    
    string ToAddMiner;
    cout<<"\nYou already have a default miner with MinerID - 0"<<endl;sleep(1);
    cout<<"Do you want to add more miners ?(YES or NO)"<<endl;
    cin>>ToAddMiner;
    if(ToAddMiner=="YES" || ToAddMiner=="yes" || ToAddMiner=="Yes")
    addMiner();
    
    cout<<"\n***************************"<<endl;
    cout<<"Let's start mining Blocks !"<<endl;
    cout<<"***************************"<<endl;
    cout<<".";sleep(2);cout<<" .";sleep(2);cout<<" .\n"<<endl;sleep(1);
    mineBlock();
   
   
   
   
   CreationfunctionMap[1]=addWallet;
   CreationfunctionMap[2]=addTransaction;
   CreationfunctionMap[3]=addMiner;
   CreationfunctionMap[4]=mineBlock;

   int choice  ;
   while(choice!=5)
   {  
      int choice ;
      cout<<"\nChoose from options : \n"<<endl;
      cout<<"1 . Add more Wallets \n"<<endl;
      cout<<"2 . Add more Transactions \n"<<endl;
      cout<<"3 . Add more Miners\n"<<endl;
      cout<<"4 . Mine more Blocks\n"<<endl;
      cout<<"5 . Exit \n"<<endl;
      cin>>choice;

      if(choice>5 || choice<1)
      {
         cout<<"Invalid Option choice ! Try again !\n"<<endl;
         continue;
      }
      
      if(choice==5)break;
      

      CreationfunctionMap[choice]();
   }
    
   
   cout<<"***Exiting from BlockChain Creation Mode***"<<endl;sleep(1);
   return myChain;

}
#include<bits/stdc++.h>
#ifndef WALLET_h
#define WALLET_h
#include "Transaction.h"
#include "../Eliptic_Curve_Cryptography/ElipticCurve.h"
#include "../Eliptic_Curve_Cryptography/Entity.h"
#include "../Eliptic_Curve_Cryptography/Point.h"
#include "../Eliptic_Curve_Cryptography/GeneratePoint.h"

using namespace std;

class Wallet{

    public :
       Entity WalletOwner;
       string WalletAdress;
       int Balance;
       
       Wallet(){}
       Wallet(string name , int balance )
       {
         // Create an elliptic curve
         ElipticCurve EC=CreateCurve();
         // Create a new entity for the wallet owner
         Entity WalletOwner=Entity(name,EC);
         
         pair<long long int , long long int > WalletPublicKey ;
         
         // Generate a public-private key pair for the wallet
         this->WalletOwner=generateKey(WalletOwner,EC);
         // set the wallet address to the entity address
         WalletAdress=WalletOwner.EntityAdress();

         // Set the initial balance of the wallet
         this->Balance=balance;

       }

      // Function to get the balance of the wallet
      int getBalance()
      {
         return this->Balance;
      }

      // Function to check if a given private key is valid for the wallet
      bool isPrivKeyValid(long long int SecretKey)
      {
         return this->WalletOwner.isEnityValid(SecretKey);
      }
      
      // Function to check if the wallet has sufficient balance for a transaction
      bool isBalanceValid(int TransactionAmount)
      {
         return this->Balance>=TransactionAmount;
      }

      // Function to add an amount to the wallet balance 
      void addBalance(int amount)
      {
         this->Balance+=amount;
      }
      
      // Function to subtract an amount from the wallet balance
      void removeBalance(int amount)
      {
         this->Balance-=amount;
      }
      
};

#endif
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

    private :
       int Balance ;

    public :
       Entity WalletOwner;
       string WalletAdress;
       
       Wallet(){}
       Wallet(string name , int balance )
       {
         //result=generateKey(name);
         ElipticCurve EC=CreateCurve();
         Entity WalletOwner=Entity(name,EC);
         
         pair<long long int , long long int > WalletPublicKey ;

         this->WalletOwner=generateKey(WalletOwner,EC);

         WalletAdress=WalletOwner.EntityAdress();
         this->Balance=balance;

       }
      int getBalance()
      {
         return this->Balance;
      }
      bool isPrivKeyValid(long long int SecretKey)
      {
         return this->WalletOwner.isEnityValid(SecretKey);
      }

      bool isBalanceValid(int TransactionAmount)
      {
         return this->Balance>=TransactionAmount;
      }

      void addBalance(int amount)
      {
         this->Balance+=amount;
      }

      void removeBalance(int amount)
      {
         this->Balance-=amount;
      }
      
};

#endif